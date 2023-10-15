/****************************************************************************
 ****************************************************************************
 **
 ** MODULE:         $Workfile: nand.h  $
 **
 ** VERSION:        $Revision: 1.12 $
 **
 ** AUTHOR:         CYLiu
 **
 ** DESCRIPTION:    nand header file
 **
 ** LAST MODIFIED BY:
 **
 ****************************************************************************
 *
 *  (c) Copyright 2007, JMicron
 * 
 ****************************************************************************/
#ifndef _NAND_H_
#define _NAND_H_

#define A19_CMD_END				0x00

/* Basic NAND Flash Commands */
#define NAND_READ						0x00
#define NAND_READ_PAGE					0x30
#define NAND_COPY_READ					0x35	//not support in MLC
#define NAND_COPY_PROG					0x85	//

#define NAND_READ_ID					0x90
#define NAND_CMD_RESET					0xFF

#define NAND_RANDOM_DATA_INPUT			0x85
#define NAND_RANDOM_DATA_OUTPUT			0x05
#define NAND_RANDOM_READ_CONFIRM		0xE0	// 0x05 0xE0

#define NAND_READ_STATUS				0x70

#define NAND_BLOCK_ERASE				0x60
#define NAND_ERASE_CONFIRM				0xD0	// 0x60 0xD0

#define NAND_PAGE_PROGRAM				0x80
#define NAND_PAGE_PROGRAM_CONFIRM		0x10

/* MICRON NAND Flash Commands */
#define MI_2PL_READ						0x00	// 00h -<><>- 00h -<><>- 30h
#define MI_2PL_READ_CNF					0x30
#define MI_2PL_RANDOM_READ_1			0x05	// 00h-<addr0>-00h-<addr1>-30h-<data0>-05h-<addr1>-E0h-<data1>-
#define MI_2PL_RANDOM_READ_2			0x06	
#define MI_2PL_RANDOM_READ_CNF			0xE0
#define MI_2PL_PROG						0x80	// 80h -<><>- 11h-80h -<><>- 10h
#define MI_2PL_PROG_CNF_1				0x11
#define MI_2PL_PROG_CNF_2				0x10
#define MI_2PL_COPY_READ				0x00	// 00h -<><>- 00h -<><>- 35h
#define MI_2PL_COPY_READ_CNF			0x35
#define MI_2PL_COPY_PROG_1				0x85	// 85h -<><>- 11h-80h -<><>- 10h
#define MI_2PL_COPY_PROG_CNF_1			0x11
#define MI_2PL_COPY_PROG_2				0x80
#define MI_2PL_COPY_PROG_CNF_2			0x10
#define MI_2PL_ERASE					0x60	// 60h -<>- 60h -<>- D0h
#define MI_2PL_ERASE_CNF				0xD0

//#define MI_2PL_READ             0x00
#define MI_2PL_READ_CFM         0x30 //0x00 -<column address> <row address>- 0x00 -<column address> <row address>- 0x30 [tR]
#define MI_2PL_READ_P2          0x06 //[tR] -<data>- 0x06 -<column address> <row address>- 0xE0 -<data>-
#define MI_2PL_PROG_P1          0x80
#define MI_2PL_PROG_CFM_P1      0x11
#define MI_2PL_PROG_P2          0x80
#define MI_2PL_PROG_CFM_P2      0x10 //0x80 -<column address> <row address> <data>- 0x11 [tDBSY] 0x80 -<column address> <row address> <data>- 0x10
//#define MI_2PL_COPY_READ        0x00
#define MI_2PL_COPY_READ_CFM    0x35 //0x00 -<column address> <row address>- 0x00 -<column address> <row address>- 0x35 [tR]
#define MI_2PL_COPY_PROG_P1     0x85
#define MI_2PL_COPY_PROG_CFM_P1 0x11
#define MI_2PL_COPY_PROG_P2     0x85
#define MI_2PL_COPY_PROG_CFM_P2 0x10 //0x85 -<column address> <row address> <data>- 0x11 [tDBSY] 0x85 -<column address> <row address> <data>- 0x10
#define MI_READ_STATUS          0x78



/* SAMSUNG NAND Flash Commands */
#define SA_2PL_READ						0x60	// 60h -<><>- 60h -<><>- 30h
#define SA_2PL_READ_CNF					0x30
#define SA_2PL_RANDOM_READ_1			0x00	// 00h -<><>- 05h -<><>- E0h
#define SA_2PL_RANDOM_READ_2			0x05
#define SA_2PL_RANDOM_READ_CNF			0xE0
#define SA_2PL_PROG_1					0x80	// 80h -<><>- 11h-81h -<><>- 10h
#define SA_2PL_PROG_CNF_1				0x11
#define SA_2PL_PROG_2					0x81
#define SA_2PL_PROG_CNF_2				0x10
#define SA_2PL_COPY_READ				0x60	// 60h -<><>- 60h -<><>- 35h
#define SA_2PL_COPY_READ_CNF			0x35
#define SA_2PL_COPY_PROG_1				0x85	// 85h -<><>- 11h-81h -<><>- 10h
#define SA_2PL_COPY_PROG_CNF_1			0x11
#define SA_2PL_COPY_PROG_2				0x81
#define SA_2PL_COPY_PROG_CNF_2			0x10
#define SA_2PL_ERASE					0x60	// 60h -<>- 60h -<>- D0h
#define SA_2PL_ERASE_CNF				0xD0

//#define SA_2PL_READ             0x60
#define SA_2PL_READ_CFM         0x30 //0x60 -<row address>- 0x60 -<row address>- 0x30 [tR]
#define SA_2PL_READ_P1          0x00 //[tR] 0x00 -<column address> <row address> <data>- 0x00 -<column address> <row address> <data>-
#define SA_2PL_PROG_P1          0x80
#define SA_2PL_PROG_CFM_P1      0x11
#define SA_2PL_PROG_P2          0x81
#define SA_2PL_PROG_CFM_P2      0x10 //0x80 -<column address> <row address> <data>- 0x11 [tDBSY] 0x80 -<column address> <row address> <data>- 0x10
//#define SA_2PL_COPY_READ        0x60
#define SA_2PL_COPY_READ_CFM    0x35 //0x60 -<row address>- 0x60 -<row address>- 0x35 [tR]
#define SA_2PL_COPY_PROG_P1     0x85
#define SA_2PL_COPY_PROG_CFM_P1 0x11
#define SA_2PL_COPY_PROG_P2     0x81
#define SA_2PL_COPY_PROG_CFM_P2 0x10 //0x85 -<column address> <row address> <data>- 0x11 [tDBSY] 0x81 -<column address> <row address> <data>- 0x10
#define SA_READ_STATUS_D0       0xF1
#define SA_READ_STATUS_D1       0xF2



/* TOSHIBA NAND Flash Commands */
#define TS_COPY_PROG					0x8C
#define TS_2PL_READ						0x60	// 60h -<><>- 60h -<><>- 30h
#define TS_2PL_READ_CNF					0x30
#define TS_2PL_RANDOM_READ_1			0x00	// 00h -<><>- 05h -<><>- E0h
#define TS_2PL_RANDOM_READ_2			0x05
#define TS_2PL_RANDOM_READ_CNF			0xE0
#define TS_2PL_PROG						0x80	// 80h -<><>- 11h-80h -<><>- 10h
#define TS_2PL_PROG_CNF_1				0x11
#define TS_2PL_PROG_CNF_2				0x10
#define TS_2PL_COPY_READ				0x60	// 60h -<><>- 60h -<><>- 30h
#define TS_2PL_COPY_READ_CNF			0x30
#define TS_2PL_COPY_PROG_1				0x8C	// 8Ch -<><>- 11h-8Ch -<><>- 10h
#define TS_2PL_COPY_PROG_CNF_1			0x11
#define TS_2PL_COPY_PROG_2				0x8C
#define TS_2PL_COPY_PROG_CNF_2			0x10
#define TS_2PL_ERASE					0x60	// 60h -<>- 60h -<>- D0h
#define TS_2PL_ERASE_CNF				0xD0

//#define TS_2PL_READ             0x60
#define TS_2PL_READ_CFM         0x30 //0x60 -<row address>- 0x60 -<row address>- 0x30 [tR]
#define TS_2PL_READ_P1          0x00 //[tR] 0x00 -<column address> <row address> <data>- 0x00 -<column address> <row address> <data>-
#define TS_2PL_PROG_P1          0x80
#define TS_2PL_PROG_CFM_P1      0x11
#define TS_2PL_PROG_P2          0x81
#define TS_2PL_PROG_CFM_P2      0x10 //0x80 -<column address> <row address> <data>- 0x11 [tDBSY] 0x80 -<column address> <row address> <data>- 0x10
//#define TS_2PL_COPY_READ        0x60
#define TS_2PL_COPY_READ_CFM    0x35 //0x60 -<row address>- 0x60 -<row address>- 0x30 [tR]
#define TS_2PL_COPY_PROG_P1     0x85
#define TS_2PL_COPY_PROG_CFM_P1 0x11
#define TS_2PL_COPY_PROG_P2     0x81
#define TS_2PL_COPY_PROG_CFM_P2 0x10 //0x8C -<column address> <row address> <data>- 0x11 [tDBSY] 0x8C -<column address> <row address> <data>- 0x10
#define TS_READ_STATUS_D0       0xF1
#define TS_READ_STATUS_D1       0xF2



// Status
#define NAND_RDY                0x40
#define NAND_FAIL               0x01

/* Sector Buffer Select */
#define SECTOR_BUF_START 	0x00

#define FDMA_00_SEL		(0x00+SECTOR_BUF_START)
#define FDMA_01_SEL		(0x08+SECTOR_BUF_START)
#define FDMA_02_SEL		(0x10+SECTOR_BUF_START)
#define FDMA_03_SEL		(0x18+SECTOR_BUF_START)
#define FDMA_04_SEL		(0x20+SECTOR_BUF_START)
#define FDMA_05_SEL		(0x28+SECTOR_BUF_START)
#define FDMA_06_SEL		(0x30+SECTOR_BUF_START)
#define FDMA_07_SEL		(0x38+SECTOR_BUF_START)
#define FDMA_08_SEL		(0x40+SECTOR_BUF_START)
#define FDMA_09_SEL		(0x48+SECTOR_BUF_START)
#define FDMA_10_SEL		(0x50+SECTOR_BUF_START)
#define FDMA_11_SEL		(0x58+SECTOR_BUF_START)
#define FDMA_12_SEL		(0x60+SECTOR_BUF_START)
#define FDMA_13_SEL		(0x68+SECTOR_BUF_START)
#define FDMA_14_SEL		(0x70+SECTOR_BUF_START)
#define FDMA_15_SEL		(0x78+SECTOR_BUF_START)
#define FDMA_16_SEL		(0x80+SECTOR_BUF_START)
#define FDMA_17_SEL		(0x88+SECTOR_BUF_START)
#define FDMA_18_SEL		(0x90+SECTOR_BUF_START)
#define FDMA_19_SEL		(0x98+SECTOR_BUF_START)
#define FDMA_20_SEL		(0xA0+SECTOR_BUF_START)
#define FDMA_21_SEL		(0xA8+SECTOR_BUF_START)
#define FDMA_22_SEL		(0xB0+SECTOR_BUF_START)
#define FDMA_23_SEL		(0xB8+SECTOR_BUF_START)	
#define FDMA_24_SEL		(0xC0+SECTOR_BUF_START)
#define FDMA_25_SEL		(0xC8+SECTOR_BUF_START)	
#define FDMA_26_SEL		(0xD0+SECTOR_BUF_START)
#define FDMA_27_SEL		(0xD8+SECTOR_BUF_START)	
#define FDMA_28_SEL		(0xE0+SECTOR_BUF_START)
#define FDMA_29_SEL		(0xE8+SECTOR_BUF_START)	
#define FDMA_30_SEL		(0xF0+SECTOR_BUF_START)
#define FDMA_31_SEL		(0xF8+SECTOR_BUF_START)	

#define MAX_FDMA_SEL		FDMA_16_SEL

#define BUF_00  		(0x00)
#define BUF_01  		(0x01)
#define BUF_02  		(0x02)
#define BUF_03  		(0x03)
#define BUF_04  		(0x04)
#define BUF_05  		(0x05)
#define BUF_06  		(0x06)
#define BUF_07  		(0x07)
#define BUF_08  		(0x08)
#define BUF_09  		(0x09)
#define BUF_10  		(0x0A)
#define BUF_11  		(0x0B)
#define BUF_12  		(0x0C)
#define BUF_13  		(0x0D)
#define BUF_14  		(0x0E)
#define BUF_15  		(0x0F)
#define BUF_16  		(0x10)
#define BUF_17  		(0x11)
#define BUF_18  		(0x12)
#define BUF_19  		(0x13)
#define BUF_20  		(0x14)
#define BUF_21  		(0x15)
#define BUF_22  		(0x16)
#define BUF_23  		(0x17)


/* NAND Flash Status */
#define PROG_OK				(1)
#define WRITE_PROTECT		(2)
#define PROG_ERROR			(3)
#define TIMEOUT_FAIL		(4)
#define PROG_NOTREADY		(5)

/* NAND Flash Bank Select */
#define FLASH_BANK_00		(0x00)
#define FLASH_BANK_01		(0x01)
#define FLASH_BANK_02		(0x02)
#define FLASH_BANK_03		(0x03)
#define FLASH_BANK_04		(0x04)
#define FLASH_BANK_05		(0x05)
#define FLASH_BANK_06		(0x06)
#define FLASH_BANK_07		(0x07)
#define FLASH_BANK_08		(0x08)
#define FLASH_BANK_09		(0x09)
#define FLASH_BANK_10		(0x0A)
#define FLASH_BANK_11		(0x0B)
#define FLASH_BANK_12		(0x0C)
#define FLASH_BANK_13		(0x0D)
#define FLASH_BANK_14		(0x0E)
#define FLASH_BANK_15		(0x0F)

/* NAND Flash Channel Select */
#define CHAN_00				(0x00)
#define CHAN_01				(0x01)
#define CHAN_02				(0x02)
#define CHAN_03				(0x03)
#define CHAN_04				(0x04)
#define CHAN_05				(0x05)
#define CHAN_06				(0x06)
#define CHAN_07				(0x07)


/* NAND Macros */
#define MULTI_CHAN_CTRL_ALL_ON			(0x00)
#define MULTI_CHAN_CTRL_OFF				(0xFF)

#define NAND_OPEN_NB(bank_sel)			(rF_MULTI_CHAN_CTRL&=MULTI_CHAN_CTRL_ON);(rFBS_0) = (bank_sel)
#define NAND_OPEN(ce)					rF_INDEX = ALL_CHANNEL; rF0_BANK_SEL = abBNK[ce];
//#define NAND_OPEN(ce)					rF_INDEX = ALL_CHANNEL; rF0_BANK_SEL = abBNK_[(ce & BANK_MASK)]; // fywei temperory set for toshiba 2ce 4ch using ce0 ce2
//#define NAND_OPEN(bank_sel)				(rFBS_0) = (bank_sel)
//#define NAND_CLOSE()					(rFBS_0) = 0xFF
#define NAND_CLOSE()            		(rF_BANK_SEL03) = 0x0f0f0f0f; (rF_BANK_SEL47) = 0x0f0f0f0f; rF_NAND_PAD = POWER_DOWN

#define NAND_RESET()					(rF0_FMPCP) = NAND_CMD_RESET
#define NAND_INDEX_SEL(index)			(rF_INDEX) = (index)

#define NAND_CMD_IN(cmd)				(rF0_FMPCP) = (cmd)
#define NAND_ADDR_IN(addr)				(rF0_FMPAP) = (addr)
#define NAND_DATA_IN(dat)				(rF0_FMPDP) = (dat)
#define NAND_DATA_OUT(dat)				(dat) = (rF0_FMPDP)

#define PAGE_BYTES						(word)(PAGE_SECTOR << 9)
#define PAGE_KBYTE						(PAGE_SECTOR >> 1)
#define FDMA_PAGE_OFFSET				(PAGE_SECTOR << 1)

/* NAND Flash ID */
typedef struct _NAND_ID
{
	byte MarkCode;
	byte DeviceCode;
	byte ID3rd;
	byte ID4th;
	byte ID5th;
    byte ID6th;
    byte ID7th;
} NAND_ID;

/* NAND Flash Address */
typedef struct _NAND_ADDR
{
	byte ColAddr1;
	byte ColAddr2;
//	byte RowAddr1;
	byte RowAddr2;
	byte RowAddr3;
	byte RowAddr1;
} NAND_ADDR; 

/* Extern variables */
extern NAND_ADDR sNand;

extern byte FLASH_VENDER;
extern byte bFlashType;
extern word IC_BLOCKS;
extern word BLOCK_PAGE;
extern byte PAGE_SECTOR;
extern byte MAX_DIES;
//extern byte LOW_PAGE_MODE;
extern byte IS_4XNM_MODE;
extern word wDistrictRegion;
extern byte bDistrictRegionBit;
extern word DIE_OFFSET_UNIT;

extern byte MULTI_CHAN_CTRL_ON;
extern byte iSLC_MODE;

#endif	//_NAND_H_
