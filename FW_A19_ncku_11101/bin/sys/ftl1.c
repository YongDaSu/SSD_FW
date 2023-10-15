// ****************************************************************************
// ****************************************************************************
// **
// ** MODULE:      $RCSfile: FTL1.C $
// **
// ** VERSION:     $Revision: 1.0 $
// **
// ** AUTHOR:
// **
// ** DESCRIPTION: Flash Translation Layer Task
// **
// ****************************************************************************
// *
// *
// *
// ****************************************************************************/

#include <global.h>
//#include "wbm.h"
#include <defreg.h>
#include <uart.h>
#include <ataopt.h>
#include <nand_sys.h>
#include <ftl.h>
#include <stdlib.h>


#define 	DEF_HEADS_NUMBER					16
#define 	DEF_SECTS_PER_TRACK					63
// ***********************************************************
// *          Define value
// **********************************************************
byte			CHANNEL_NUM;
word			PAGE_BYTE;
qword			BMP_ALL_INVERT;
qword			BMP_PLANE0_MASK;
qword			BMP_PLANE1_MASK;
word			MAX_PHY_BLK_NUM;
word			MAX_FREE_BLK_NUM;
word			MAX_LOG_BLK_NUM;
dword 		 	NATIVE_MAX_LBA;
byte			PHY_PAGE_MASK;
byte			REFLASH_THRESHOLD;
word			DIE_BLOCK_UNIT;
dword 			TOTAL_LBA_SECTORS;
word			ADMA_FDMA_MASK;
word			LBA_PER_ROW;
word			HALF_LBA_PER_ROW;
word			PING_PONG_BUF_1;
word			PING_PONG_BUF_1_SHIFT;
byte			bBLOCK_SHIFT;
byte			bPAGE_SHIFT;
byte			bSECTOR_SHIFT;

word			BLOCK_PAGE_FTL;
// ***********************************************************
// *          Variable
// **********************************************************
BLOCKL2PTABLE 	gBlkL2PTable;

__align(8)	word	gBlkMapTablePool_0[8192];	// [PhyAddr]    16k
__align(8)	word	gFreeBlkTablePool[2048];	//
__align(8)	dword	gFreeBlkEraseCntPool[1024];	// 4K


// For DMARead() & DMAWrite()
STATIC word		gwRWBufAddr;

// Logic address information declaration
word    		gLogAddrInfo_bDstLBAInRow;


extern void ata_initialize_device_parameters(void);
    
void vFTL_DumpBufData(void);

// ***********************************************************
// ***********************************************************
// * 
// ***********************************************************
//**************************************************************
//
// 設定Flash參數，如Block大小/Page大小...
//
//**************************************************************
void vFTL_InitDefineValue(void)
{
	word	   wTmpValue;
	
	BLOCK_PAGE_FTL = 16;
	
	CHANNEL_NUM = 1;
	DCO_LBA48_ENABLE = SUPPORT_ATA_LBA48_MODE;
	REFLASH_THRESHOLD = sParam.D.SYS.bECCErrorCopyThreshold;
	DIE_BLOCK_UNIT = ((IC_BLOCKS / MAX_DIES ) >> 1);	// Two plane
	
	LBA_PER_ROW				= 2 * PAGE_SECTOR * CHANNEL_NUM;	// LBA per row (2 plane)
	HALF_LBA_PER_ROW 		= LBA_PER_ROW >> 1;					// LBA per 1/2 row : for ping-pong buffer
	PING_PONG_BUF_1	 		= HALF_LBA_PER_ROW;					// Address of ping-pong buffer 1
	PING_PONG_BUF_1_SHIFT 	= PAGE_SECTOR * (8 - CHANNEL_NUM);	// Shift LBA of ping-pong buffer 1
	
	PHY_PAGE_MASK = BLOCK_PAGE - 1;
	PAGE_BYTE = PAGE_SECTOR * 512;
	
	
	// Get Block/Page/Sector Shift info
	bBLOCK_SHIFT = 0;
	wTmpValue = DIE_BLOCK_UNIT;
	do
	{
		bBLOCK_SHIFT++;
		wTmpValue = wTmpValue >> 1;
	}while(wTmpValue > 1);
	
	bPAGE_SHIFT = 0;
	wTmpValue = BLOCK_PAGE;
	do
	{
		bPAGE_SHIFT++;
		wTmpValue = wTmpValue >> 1;
	}while(wTmpValue > 1);
	
	bSECTOR_SHIFT = 0;
	wTmpValue = PAGE_SECTOR;
	do
	{
		bSECTOR_SHIFT++;
		wTmpValue = wTmpValue >> 1;
	}while(wTmpValue > 1);
	
	
	if(PAGE_SECTOR == 32)
	{
		BMP_ALL_INVERT   = 0x0000000000000000;
		BMP_PLANE0_MASK  = 0x00000000FFFFFFFF;
		BMP_PLANE1_MASK  = 0xFFFFFFFF00000000;
	   
		// Get ADMA/FDMA Mask
		ADMA_FDMA_MASK = 0xFF;
	}
	if(PAGE_SECTOR == 16)
	{
		BMP_ALL_INVERT 	= 0xFFFFFFFF00000000;
		BMP_PLANE0_MASK   = 0x000000000000FFFF;
		BMP_PLANE1_MASK   = 0x00000000FFFF0000;
		
		// Get ADMA/FDMA Mask
		ADMA_FDMA_MASK = 0x0F;
	}
	else if(PAGE_SECTOR == 8)
	{
		BMP_ALL_INVERT 	= 0xFFFFFFFFFFFF0000;
		BMP_PLANE0_MASK   = 0x00000000000000FF;
		BMP_PLANE1_MASK   = 0x000000000000FF00;
		
		// Get ADMA/FDMA Mask
		ADMA_FDMA_MASK = 0x03;
	}
	else if(PAGE_SECTOR == 4)
	{
		BMP_ALL_INVERT 	= 0xFFFFFFFFFFFFFF00;
		BMP_PLANE0_MASK   = 0x000000000000000F;
		BMP_PLANE1_MASK   = 0x00000000000000F0;
		
		// Get ADMA/FDMA Mask
		ADMA_FDMA_MASK = 0x01;
	}
	
	MAX_PHY_BLK_NUM = IC_BLOCKS >> 1;
	MAX_PHY_BLK_NUM = 200;
	MAX_FREE_BLK_NUM = ((dword)sParam.bReservedRatio * MAX_PHY_BLK_NUM) / 1000;
	MAX_LOG_BLK_NUM = (MAX_PHY_BLK_NUM - MAX_FREE_BLK_NUM);
	
	TOTAL_LBA_SECTORS = ((dword)(MAX_LOG_BLK_NUM) * BLOCK_PAGE_FTL * PAGE_SECTOR * 2);
	NATIVE_MAX_LBA = TOTAL_LBA_SECTORS;
	
	
	UARTprintf("\rPAGE_SECTOR %d\r", PAGE_SECTOR);
	UARTprintf("BLOCK_PAGE %d\r", BLOCK_PAGE);
	UARTprintf("BLOCK_PAGE_FTL %d\r", BLOCK_PAGE_FTL);
	UARTprintf("IC_BLOCKS %d\r", IC_BLOCKS);
	UARTprintf("MAX_PHY_BLK_NUM %d\r", MAX_PHY_BLK_NUM);
	UARTprintf("MAX_LOG_BLK_NUM %d\r", MAX_LOG_BLK_NUM);
	UARTprintf("TOTAL_LBA_SECTORS %d\r", TOTAL_LBA_SECTORS);
}


//****************************************************************************
//*
//****************************************************************************
void nand_delay(void)
{
	__asm
	{
		nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;
    	nop;    
	}
}


//**************************************************************
//
// 將指定的Blcok Erase
//
//**************************************************************
byte bFTL_BlockErase(word wBlkNo)
{
	vNAND_GetAddress2(0, wBlkNo);
	
	NAND_OPEN(0);
	NAND_INDEX_SEL(0);
	// wait previous DMA done
	vNAND_WaitDMAdone();
	bNAND_WaitReady();
	vTwoPlaneBlockErase();
	nand_delay();
	
	if(bNAND_WaitReady() != PROG_OK)
		return 1;
		
	return 0;
}


//**************************************************************
//  
//  將指定Blcok的Page資料讀到SRAM Buffer
//  
//**************************************************************
void vFTL_PageRead(byte bPageNo, word wBlkNo)
{
	dword 	dwRowAddr;
	
	//UARTprintf("vFTL_PageRead Page:%x Block:%x\r", bPageNo, wBlkNo);
	
	dwRowAddr = vNAND_GetRowAddress(bPageNo, wBlkNo);
	dwRowAddr = dwRowAddr | 0x0100;
	
	NAND_OPEN(0);
	NAND_INDEX_SEL(0);
	vNAND_WaitDMAdone();
	//rF_DRAM_MAP(0) = BMP_ALL_INVERT | BMP_PLANE1_MASK;
	rF_DRAM_MAP(0) = BMP_ALL_INVERT;
	
	//clear ROW address queue
	//rF0_ROW_QUEUE = ROW_CLR0 | ROW_CLR1;
	//set FDMA ROW addr
	rF0_FLASH_ADDR = dwRowAddr << 8;
	rF0_FSBP = gFDMABufSel[0];
	//rF0_FDSZ = PAGE_SECTOR;
	rF0_FDSZ = PAGE_BYTE << 1;

	//wait Flash ready
    bNAND_WaitReady();
	
	//turn on FDMA read
	rF0_FDMA_SET = 0;//FDMA_FRC_WAIT | FDMA_WAIT_MODE;
	//rF0_FDMA_CTL = FEXE_ENABLE | FEXE_F2B | FEXE_COL_AUTO | FDMA_OVERLAP_EN | FDMA_BITMAP_EN | FDMA_BITMAP_INVERT;
	rF0_FDMA_CTL = FEXE_ENABLE | FEXE_F2B | FEXE_COL_AUTO | FEXE_FRC_2PL | FDMA_PROG_CONFIRM | FDMA_OVERLAP_EN | 
				   FDMA_2PLANE_CMD_EN | FDMA_BITMAP_EN | FDMA_BITMAP_INVERT;
	
	nand_delay();
	vNAND_WaitDMAdone();
}


//**************************************************************
//
//  將SRAM Buffer資料謝入指定Blcok的Page
//  
//**************************************************************
void vFTL_PageProgram(byte bPageNo, word wBlkNo)
{
	dword 	dwRowAddr;
	
	UARTprintf("vFTL_PageProgram Page:%x Block:%x\r", bPageNo, wBlkNo);
	
	dwRowAddr = vNAND_GetRowAddress(bPageNo, wBlkNo);
	dwRowAddr = dwRowAddr | 0x0100;
	
	NAND_OPEN(0);
	NAND_INDEX_SEL(0);
	vNAND_WaitDMAdone();
	//rF_DRAM_MAP(0) = BMP_ALL_INVERT | BMP_PLANE1_MASK;
	rF_DRAM_MAP(0) = BMP_ALL_INVERT;
	
	//clear ROW address queue
	//rF0_ROW_QUEUE = ROW_CLR0 | ROW_CLR1;
	//set FDMA ROW addr
	rF0_FLASH_ADDR = dwRowAddr << 8;
	rF0_FSBP = gFDMABufSel[0];
	rF0_FDSZ = PAGE_BYTE << 1;
	
	//wait Flash ready
    bNAND_WaitReady();
	
	//turn on FDMA write
	rF0_FDMA_SET = 0;//FDMA_FRC_WAIT | FDMA_WAIT_MODE;
	//rF0_FDMA_CTL = FEXE_ENABLE | FEXE_COL_AUTO | FDMA_PROG_CONFIRM | FDMA_BITMAP_EN | FDMA_BITMAP_INVERT;
	rF0_FDMA_CTL = FEXE_ENABLE | FEXE_COL_AUTO | FEXE_FRC_2PL | FDMA_PROG_CONFIRM | FDMA_OVERLAP_EN | 
				   FDMA_2PLANE_CMD_EN | FDMA_BITMAP_EN | FDMA_BITMAP_INVERT;
	
	vNAND_WaitDMAdone();
	bNAND_WaitReady();
	//UARTprintf("ready\r");
}


// **************************************************************
//  
//  將Buffer資料設為0xFF
//  
// **************************************************************
void vFTL_SetBufferEmpty(byte tag)
{
	xmemset((void *)FLASH_MEM_BASE , tag, 128 * 1024);	// 128K
}


// **************************************************************
// *
// **************************************************************
void vFTL_InitTable(void)
{
	dword 	i;
	
	gBlkL2PTable.wpL2PTab = gBlkMapTablePool_0;		// Max 8K LogBlock
	gBlkL2PTable.wpFreeTab = gFreeBlkTablePool;		// Max 2K Free Block
	gBlkL2PTable.wpBadBlkTab = (word *)gFreeBlkEraseCntPool;//gBadBlkPool;
	
	
	// Init free pool info
	gBlkL2PTable.wCycleIdx = 0;
	gBlkL2PTable.wFreeBlkIdx = 0;
	gBlkL2PTable.wFreeBlkNum = 0;
	
	// Init bad block pool info
	gBlkL2PTable.wBadBlkNum = 0;
	
	for( i = 0 ; i < MAX_PHY_BLK_NUM ; i++ )
	{
		gBlkL2PTable.wpL2PTab[i] = 0xFFFF;
	}
}


// **************************************************************
// *
// **************************************************************
void vFTL_BuildFakeL2PTable(void)
{
	word 	wPhyBlkNo, wTotalBadBlkNo;
	word	wTotalZoneLogBlkNo, i;
	
	UARTprintf("vFTL_BuildFakeL2PTable\r");
	
	vFTL_InitTable();
	
	wTotalBadBlkNo = 0;
	wTotalZoneLogBlkNo = 0;
	gBlkL2PTable.wFreeBlkNum = 0;
	
	for( wPhyBlkNo = 5 ; wPhyBlkNo < MAX_PHY_BLK_NUM ; wPhyBlkNo++ )
	{
//		UARTprintf("===== %d\r", wPhyBlkNo);
		
		if(bFTL_BlockErase(wPhyBlkNo))	// Erase fail, mark bad block
	    {
	    	// For debug...
	    	UARTprintf("Bad %d\r", wPhyBlkNo);
	    	wTotalBadBlkNo++;
	    	continue;
	    }
	    
	    if(wTotalZoneLogBlkNo < MAX_LOG_BLK_NUM)
	    {
	    	// Set user
	    	gBlkL2PTable.wpL2PTab[wTotalZoneLogBlkNo] = wPhyBlkNo;
	    }
	    else
	    {
			// Set free
		  	gBlkL2PTable.wpFreeTab[gBlkL2PTable.wFreeBlkIdx] = wPhyBlkNo;
		   	gBlkL2PTable.wFreeBlkIdx++;
			gBlkL2PTable.wCycleIdx++;
			gBlkL2PTable.wFreeBlkNum++;
	    }
	    
	    wTotalZoneLogBlkNo++;
	}
	
	
	// Set wActFreeBlkNum
	gBlkL2PTable.wActFreeBlkNum = gBlkL2PTable.wFreeBlkNum;
	
	UARTprintf("U:%d F:%d B1:%d\r", wTotalZoneLogBlkNo, 
									 gBlkL2PTable.wFreeBlkNum, 
									 wTotalBadBlkNo);
	
}


// **************************************************************
// *
// **************************************************************
void vFTL_Init(void)
{
	// For test    
	vFTL_BuildFakeL2PTable();
}


// **************************************************************
//
// 回傳dwLBA對應到的邏輯Block位址 
//  
// **************************************************************
STATIC word wFTL_GetLogBlockAddr(dword dwLBA)
{
	dword	wLogBlock;
	
	// a page has 32 LBA
	wLogBlock = dwLBA / (PAGE_SECTOR * 2);		// 32K page
	
	// Logic block number
	wLogBlock = wLogBlock / BLOCK_PAGE_FTL;	// 1 block = 256 page
	
	//UARTprintf("LogBlk:%4.4x\r", wLogBlock);
	
	return ((word) wLogBlock);
}

// **************************************************************
// 
// 回傳dwLBA對應到邏輯Block的Page位址
// 
// **************************************************************
STATIC word wFTL_GetLogPageAddr(dword dwLBA)
{
	dword	wLogPage;
	
	// a page has 8 LBA
	wLogPage = dwLBA / (PAGE_SECTOR * 2);		// 2 plane page
	
	// Destination LBA in row
	gLogAddrInfo_bDstLBAInRow = dwLBA % (PAGE_SECTOR * 2);
	
	// Logic row page number
	wLogPage = wLogPage % BLOCK_PAGE_FTL;	// 1 block = 256 page
	
	//UARTprintf("wLogPage:%4.4x\r", wLogPage);
	
	return ((word) wLogPage);
}


// **************************************************************
// 
// 從管理的表中取得一個Block並將其Erase, 給資料寫入使用
// 
// **************************************************************
word wFTL_GetFreeBlock(void)
{
	word		wPhyBlkNo = 0xFFFF;
	
	gBlkL2PTable.wCycleIdx++;
	if(gBlkL2PTable.wCycleIdx >= gBlkL2PTable.wFreeBlkNum)
		gBlkL2PTable.wCycleIdx = 0;
		
	wPhyBlkNo = gBlkL2PTable.wpFreeTab[ gBlkL2PTable.wCycleIdx ];
	
	gBlkL2PTable.wFreeBlkIdx = gBlkL2PTable.wCycleIdx;
	
	bFTL_BlockErase(wPhyBlkNo);
	
	return (wPhyBlkNo);
}


// **************************************************************
// 
// 將不需要在使用的wPhyBlkNo放回管理的表中, 方便下次使用可以取得
// 
// **************************************************************
void vFTL_UpDateFreeBlock(word wPhyBlkNo)
{
	gBlkL2PTable.wpFreeTab[gBlkL2PTable.wFreeBlkIdx] = wPhyBlkNo & LOG_BLOCK_NUM_MASK;
}


// **************************************************************
// 
// 將SRAM Buffer資料傳到SATA Bus, 即將資料從SRAM Buffer傳到SATA端在傳至PC端
// 
// **************************************************************
void vFTL_DMARead_TXferBusData(void)
{
	// Wait bus DMA transfer done
	vADMA_EnableADMA(BUF_TO_SATA, gwRWBufAddr);
}


// **************************************************************
// 
// 計算SRAM Buffer此次傳輸可以處理的資料量並回傳
// 
// **************************************************************
STATIC word wFTL_CalTxferLen(dword dwDataSectorCount)
{
	word	wRWTXferLen;
	
	gwRWBufAddr = gLogAddrInfo_bDstLBAInRow;
	if(gwRWBufAddr >= HALF_LBA_PER_ROW)
		gwRWBufAddr = gwRWBufAddr + PING_PONG_BUF_1_SHIFT;
	
	// Calculate bus transfer length
	wRWTXferLen = (PAGE_SECTOR * 2) - gLogAddrInfo_bDstLBAInRow;
	
	if( wRWTXferLen > dwDataSectorCount )
		wRWTXferLen = dwDataSectorCount;
		
	return wRWTXferLen;
}


// **************************************************************
// 
// 將資料從SATA Bus傳到SRAM Buffer, 即將資料從PC端傳到Controller的SATA端在寫入至SRAM Buffer
// 
// **************************************************************
void vFTL_DMAWrite_TXferBusData(void)
{
	// Wait bus DMA transfer done
	vADMA_EnableADMA(SATA_TO_BUF, gwRWBufAddr);
}










//*****************************************************************************************
//  FTL Read code write here....
// 
//  gBlkL2PTable.wpL2PTab[] : Logical block to Physical block mapping table
// 
//*****************************************************************************************
PUBLIC byte bFTL_DMARead(dword dwLBA, dword dwSectCnt)
{
	word	wUserBlockNo;
	word	wReadTXferLen;
	word	wLogPage, wLogBlock;
	
	UARTprintf("R %4.4x %4.4x\r", dwLBA, dwSectCnt);
	
	do{
		// Always decode log block info
		wLogBlock = wFTL_GetLogBlockAddr(dwLBA);
		wLogPage = wFTL_GetLogPageAddr(dwLBA);
		wUserBlockNo = gBlkL2PTable.wpL2PTab[wLogBlock];
		
		//UARTprintf("BB %4.4x %4.4x\r", wUserBlockNo, wLogPage);
		
		// Get next transfer length
		wReadTXferLen = wFTL_CalTxferLen(dwSectCnt);
		
		// Read page data
		vFTL_PageRead(wLogPage, wUserBlockNo);
		
		//vFTL_DumpBufData();
		
		// Transfer data from SRAM buffer to bus
		vFTL_DMARead_TXferBusData();
		
		// Modify dwSectCnt
		dwSectCnt = dwSectCnt - wReadTXferLen;
		dwLBA = dwLBA + wReadTXferLen;
		
	}while(dwSectCnt);
	
	//UARTprintf("End\r");
	
	return 0;
}


// *****************************************************************************************
//  FTL Write code write here....
// 
//  gBlkL2PTable.wpL2PTab[] : Logical block to Physical block mapping table
// 
// *****************************************************************************************
PUBLIC byte bFTL_DMAWrite(dword dwLBA, dword dwSectCnt)
{
	word	wUserBlockNo;
	word	wFreeBlockNo, i;
	word	wWriteTXferLen;
	word	wLogPage, wLogBlock;
	
	UARTprintf("W %4.4x %4.4x\r", dwLBA, dwSectCnt);
	
	// Get new free block
	wFreeBlockNo = wFTL_GetFreeBlock();
	
	// Decode log block info
	wLogBlock = wFTL_GetLogBlockAddr(dwLBA);
	wLogPage = wFTL_GetLogPageAddr(dwLBA);
	
	wUserBlockNo = gBlkL2PTable.wpL2PTab[wLogBlock];
	// Copy back head page data
	for(i = 0 ; i < wLogPage ; i++)
	{
		vFTL_PageRead(i, wUserBlockNo);
		vFTL_PageProgram(i, wFreeBlockNo);
		
		//UARTprintf("Read %4.4x %4.4x %4.4x\r", wUserBlockNo, wFreeBlockNo, i);
		//vFTL_DumpBufData();
	}
	
	// Program write command data
	do{
		// Always decode log block info
		wLogBlock = wFTL_GetLogBlockAddr(dwLBA);
		wLogPage = wFTL_GetLogPageAddr(dwLBA);
		
		// Cross User block, update table and get new free block
		if(wUserBlockNo != gBlkL2PTable.wpL2PTab[wLogBlock])
		{
			// update table
			gBlkL2PTable.wpL2PTab[wLogBlock - 1] = wFreeBlockNo;
			vFTL_UpDateFreeBlock(wUserBlockNo);
			
			// Get new free block
			wFreeBlockNo = wFTL_GetFreeBlock();
		}
		
		wUserBlockNo = gBlkL2PTable.wpL2PTab[wLogBlock];
		
		//UARTprintf("AA %4.4x %4.4x\r", dwLBA, dwSectCnt);
		//UARTprintf("BB %4.4x %4.4x\r", wFreeBlockNo, wLogPage);
		
		// Get next transfer length
		wWriteTXferLen = wFTL_CalTxferLen(dwSectCnt);
		
		// Read page data
		vFTL_PageRead(wLogPage, wUserBlockNo);
		
		// Transfer data from bus to SRAM buffer
		vFTL_DMAWrite_TXferBusData();


		
		//vFTL_DumpBufData();
		
		// Program page data
		vFTL_PageProgram(wLogPage, wFreeBlockNo);
		
		// Modify dwSectCnt
		dwSectCnt = dwSectCnt - wWriteTXferLen;
		dwLBA = dwLBA + wWriteTXferLen;
		
	}while(dwSectCnt);

	// Copy back tail page data
	for(i = wLogPage + 1 ; i < BLOCK_PAGE_FTL ; i++)
	{
		vFTL_PageRead(i, wUserBlockNo);
		vFTL_PageProgram(i, wFreeBlockNo);
	}
	
	// Update table
	gBlkL2PTable.wpL2PTab[wLogBlock] = wFreeBlockNo;
	vFTL_UpDateFreeBlock(wUserBlockNo);
	
	//UARTprintf("End\r");
	
	return 0;
}







// **************************************************************
// *  Nand Flash test code write here....
// 
// 
// 
// 
// **************************************************************
void vFTL_DumpBufData(void)
{
	byte	i, j, k;
	byte	*ptr;
	
	for(i = 0 ; i < 1 ; i++)
	{
		UARTprintf("CH %d\r", i);
		
		//for(k = 0 ; k < PAGE_SECTOR ; k++)
		for(k = 0 ; k < 2 ; k++)
		{
			ptr = (byte *)(FLASH_MEM_BASE + (k*512));
			
			for(j = 0 ; j < 16 ; j++)
			{
				putHEX(ptr[j]);
				UARTprintf(" ");
			}
			UARTprintf("\r");
		}
		UARTprintf("\r");
	}
}
// **************************************************************
// * 
// **************************************************************
void vFTL_SetBufData(void)
{
	word	i, j, k;
	byte	*ptr;
	
	i = 0;
	
	for(k = 0 ; k < PAGE_SECTOR ; k++)
	{
		ptr = (byte *)(FLASH_MEM_BASE + (k * 512));
		
		for(j = 0 ; j < 512 ; j++)
		{
			ptr[j] = k + (i++);
		}
	}
}


//**************************************************************
//
//**************************************************************
void Sam_test(void)
{
	vFTL_SetBufData();
	vFTL_SetBufferEmpty(0x00);
	vFTL_DumpBufData();
}

