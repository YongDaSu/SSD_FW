/****************************************************************************
 ****************************************************************************
 **
 ** MODULE:         $Workfile: ftl.h  $
 **
 ** VERSION:        $Revision: 1.0 $
 **
 ** AUTHOR:         CYLiu
 **
 ** DESCRIPTION:    ftl header file
 **
 ** LAST MODIFIED BY:
 **
 ****************************************************************************
 *
 *  (c) Copyright 2007, JMicron
 * 
 ****************************************************************************/
#ifndef _FTL_H_
#define _FTL_H_

#define		xdata
#define		XDATA
//****************************************
//  Sam Define
//****************************************
// DMA TXfer Direction
#define		BUF_TO_SATA			0x0
#define		SATA_TO_BUF			0x1

#define		PING_PONG_BUF_0				0x0000	// Address of ping-pong buffer 0 : 0x0000
#define     LOG_BLOCK_NUM_MASK      	0x3FFF	// --->0x7FFF : logic address arange to 0x8000 (8192 * 4)
#define     PHY_BLOCK_HIGHBYTE_MASK 	0x3F	// one flash max have 8192 block unit

#define ADMA_EXEC_ENABLE()      (rF_ADMA_CTL & ADMA_CTL_EN)
#define ADMA_EXEC_CHECK()       (rF_ADMA_FLAG & ADMA_CTL_FLAG)
#define ADMA_EXEC_RESET()       rF_ADMA_CTL &=~ ADMA_CTL_EN;

/*
 *	L2P Table Struct
 */
typedef struct _BLOCKL2PTABLE
{
	// Table exist label
	word	wTableExistLabel;
	// Table
	word    *wpL2PTab;
	word    *wpFreeTab;
	word	*wpBadBlkTab;
	
	// Free Pool Info
	word    wCycleIdx;
	word    wFreeBlkIdx;
	word    wFreeBlkNum;
	word    wActFreeBlkNum;
	dword   *dwpFreeBlkEraseCnt;
	// Bad Pool Info
	word	wBadBlkNum;
	word	wLaterBadBlkNum;
} BLOCKL2PTABLE, *PBLOCKL2PTABLE;


// 3 2 1 0
#define BYTE0(arg)		(*(byte*)&(arg))
#define BYTE1(arg)		(*((byte*)&(arg)+1))
#define BYTE2(arg)		(*((byte*)&(arg)+2))
#define BYTE3(arg)		(*((byte*)&(arg)+3))

// HI LO
#define LOBYTE(arg)		(*(byte *)&(arg))
#define HIBYTE(arg)		(*((byte *)&(arg)+1))

#define xmemset		memset



// Define value extern
extern byte				CHANNEL_NUM;
extern word				PAGE_BYTE;
extern qword			BMP_ALL_INVERT;
extern qword			BMP_PLANE0_MASK;
extern qword			BMP_PLANE1_MASK;
extern word				MAX_PHY_BLK_NUM;
extern word				MAX_FREE_BLK_NUM;
extern word				MAX_LOG_BLK_NUM;
extern dword 		 	NATIVE_MAX_LBA;
extern byte				PHY_PAGE_MASK;
extern byte				REFLASH_THRESHOLD;
extern word				DIE_BLOCK_UNIT;
extern void 		vFTL_InitDefineValue(void);


extern	byte			bBLOCK_SHIFT;
extern	byte			bPAGE_SHIFT;
extern	byte			bSECTOR_SHIFT;
extern	word			ADMA_FDMA_MASK;


// L2P Info
extern	BLOCKL2PTABLE	xdata	gBlkL2PTable;

// System timer
extern dword 			gdwSystemTimer; //record the time tick since booting


extern void vFTL_Init(void);

// ftl_access extern function
extern void vFTL_DecodeZoneLogBlkInfo(void);
extern void vFTL_SetBufferEmpty(byte tag);

//
extern byte bFTL_DMARead(dword dwLBA, dword dwSectCnt);
extern byte bFTL_DMAWrite(dword dwLBA, dword dwSectCnt);



extern void _NOP(void);
extern void vWBM_SetStartTime(void);
extern byte vWBM_CheckTimeOut(byte tag);

// ADMA
extern void vADMA_EnableADMA(byte XferDir, word bBufSel);
extern void vADMA_WaitDMADone(void);
extern void vADMA_WaitDMAFlagDone(void);
extern void nand_delay(void);


extern byte bFTL_BlockErase(word wBlkNo);
extern void vFTL_PageRead(byte bPageNo, word wBlkNo);
extern void vFTL_PageProgram(byte bPageNo, word wBlkNo);

#endif //_JM60XFTL_H_

