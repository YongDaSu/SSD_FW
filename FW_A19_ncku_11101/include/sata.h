#ifndef _SATA_H_
#define _SATA_H_

#include <global.h>
#include <defreg.h>
#include <uart.h>

// SATA_DBG_ON ranged in 3~0(default value = 1)
// 0: no any UART message
// 1: print error messages
// 2: error & warning message
// 3: error, warning & debug message
#define SATA_DBG_ON		(GLOBAL_DBG_LEVEL)
//#define SATA_DBG_ON		2

#if (SATA_DBG_ON > 2)
#define SATAprintf		UARTprintf
#else
#define SATAprintf(...) 	
#endif

#if (SATA_DBG_ON > 1)
#define SATAwarn		UARTprintf
#else
#define SATAwarn(...) 		
#endif

#if (SATA_DBG_ON > 0)
// debug message
#define SATAerror		UARTprintf
#else
#define SATAerror(...)
#endif




//====================================================
//#define CONFIG_WD
#define CONFIG_TSB_32 // current define

//====================================================

#ifdef CONFIG_WD
#define ATA_WD_REQUEST
#define ATA_FEATURE_NCQ
#define ATA_FEATURE_NOP
//#define ATA_FEATURE_WORDWIDENAME
#define ATA_DOWNLOAD_MICROCODE

//#define ATA_TRIM_IDNF
//#define PCB_IC_45_DEGREE
#endif

#ifdef CONFIG_TSB_32
//#define ATA_WD_REQUEST
#define ATA_FEATURE_NCQ
#define ATA_FEATURE_NOP
//#define ATA_FEATURE_WORDWIDENAME
#define ATA_DOWNLOAD_MICROCODE

#define PCB_IC_45_DEGREE

#endif


//IPM relative define
#define SATA_HIPM
#define SATA_DIPM
#define ATA_STANDBY_CLK_SLOWDN				(SYS_CLK_DIV_512)

#if (defined(SATA_HIPM) || defined(SATA_DIPM))
#define SATA_IPM
//eddie @0906 adds Automatic Partial to Slumber transition
#define SATA_IPM_APS
#endif

#define NEW_NCQ_TAG
#define ATA_LOG_DMA_EXT_ON
#define ATA_SMART_SCT_ON
#define SATA_NCQ_WORKAROUND_ON
//#define FIS_RETRY
#define SATA_PHY_POWER_CUT

#define CPU_POWERDOWNCOUNT		10

#ifndef JTAG_MODE
#define NCQ_SMALL_SECTOR_FIX_ON
#endif
//====================================================
// eddie adds for fixing the FIS arbitration issue
#define FIS_ARB_WA

//====================================================
#define SATA_STS_NONE							0x0000
#define SATA_STS_REQ_EXEC_NEW_CMD	0x0001		 
#define SATA_STS_EXECING_DMA_CMD	0x0100		 
#define SATA_STS_CONNECTED				0x8000


//------------------------------------------------------------------------
//		SATA IP REG DEFINE
//------------------------------------------------------------------------


#define BYTE0_OF(v)		((v) & 0x000000FF)
#define BYTE1_OF(v)		(((v) & 0x0000FF00) >> 8) 
#define BYTE2_OF(v)		(((v) & 0x00FF0000) >> 16) 
#define BYTE3_OF(v)		((v) >> 24)


#define FISTYPE_27		0x27	
#define FISTYPE_34		0x34	
#define FISTYPE_39		0x39	
#define FISTYPE_41		0x41	
#define FISTYPE_46		0x46	
#define FISTYPE_5F		0x5F	
#define FISTYPE_A1		((unsigned int) 0xA1)	

#define IS_STATUS_OK()		((REG_R000C & 0x00FF0000) == 0x00500000) 
#define IS_STATUS_BSY_ON()	((REG_R000C & 0x00800000))
#define IS_STATUS_DRQ_ON()	((REG_R000C & 0x00080000))


//------------------------------------------------------------------------
//		Status Register
//------------------------------------------------------------------------
#define STATUS_BSY				0x80	
#define STATUS_DRDY				0x40	
#define STATUS_DF					0x20	
#define STATUS_DSC				0x10	
#define STATUS_DRQ				0x08	
#define STATUS_CORR				0x04	
#define STATUS_IDX				0x02	
#define STATUS_ERROR			0x01	

//------------------------------------------------------------------------
//		Error Register
//------------------------------------------------------------------------
#define ERROR_ICRC				0x80	
#define ERROR_UNC					0x40	
#define ERROR_MC					0x20	
#define ERROR_IDNF				0x10	
#define ERROR_MCR					0x08	
#define ERROR_ABRT				0x04	
#define ERROR_TK0NF				0x02	
#define ERROR_AMNF				0x01	
#define ERROR_NONE				0x00	

 
#define ACT_ALL_ONE				0x40
#define ACT_ALL_ZERO			0x41

typedef struct shadow_reg_blk
{
	UINT8 SectorCnt;
	UINT8 SectorCnt_exp;

	UINT8 Command;

	UINT8 Features;

	union
	{
		UINT8 SectorNum;	
		UINT8 LBALow;		
	} r1;

	union
	{
		UINT8 CylinderLow;	
		UINT8 LBAMid;		
	} r2;

	union
	{
		UINT8 CylinderHigh;	
		UINT8 LBAHigh;		
	} r3;

	union
	{
		UINT8 DevHead;		
		UINT8 Device;		
	} r4;

	union
	{
		UINT8 SectorNum_exp;	
		UINT8 LBALow_exp;	
	} r5;

	union
	{
		UINT8 CylinderLow_exp;	
		UINT8 LBAMid_exp;	
	} r6;

	union
	{
		UINT8 CylinderHigh_exp;	
		UINT8 LBAHigh_exp;	
	} r7;

	UINT8 Features_exp;
	UINT8 Control;

	UINT8 Error;
	UINT8 Status;
	UINT8 E_Status;
	UINT8 ICADN_ControlBits;

} shadow_reg_blk;

typedef struct SATA_context
{
	shadow_reg_blk	srb;		

	struct isrSts
	{
		bool_T		doSRST;		
        
		bool_T		FIS27Recv;	
		
		bool_T		BISTRecv;
				
		UINT8		TxRxSts;	
		#define TXRX_UNKNOWN	0
		#define TXRX_DONE	1
		#define TXRX_ERR	2

		bool_T		DetPHYEstblsh;

		bool_T		DetPHYDiscnt;
	} isrSts;
	
	unsigned int	sata_sts;	

	unsigned int	sata_sts_connet;

	unsigned int	sata_dmaio_cmd_sts;
					
} SATA_context; 

extern SATA_context sataSts_gi;

typedef struct sata_ncq
{
	UINT8 tag;
	bool_T isRead;
	bool_T bFUA;
	
	UINT32 nSSect;
	UINT32 nSectCnt;

	UINT32 nSectCntTx;	
	bool_T boECCfailDetected;
	UINT32 SN; 
	
	struct sata_ncq *next;
} sata_ncq;


void sata_init(void);


void sata_disable_some_clks(bool_T boWithDRAM);

byte sata_wakeup_interface(void);

void sata_NCQ_setting(bool_T boNCQenable);

void sata_update_IPM_setting(bool_T boIPMenable);

unsigned int sata_poll_status(void);

byte sata_error_status(void);

void sata_invalid_cmd(void);

extern void sata_start_ncq_cmd_data(bool_T isRead, UINT8 txComplete, UINT8 bFUA);
extern unsigned int sata_poll_ncq_cmd_status(UINT8 tag, UINT8 boECCfailDetected, UINT8 bDebug);
extern void sata_report_ncq_status(UINT8 tag, bool_T EccFailDetected);
extern void sata_report_ncq_err_status(void);
extern bool_T boDAPSenable;
extern bool_T boDevSleepEnable;

#define NCQ_NONQ_CHECK_NONE			0x00
#define NCQ_NONQ_CHECK_INTERMIX	0x01
#define NCQ_NONQ_CHECK_ERR			0x02

 void sata_dma_write_pre_act(UINT32 nSectCnt);
bool_T sata_start_dmaio_cmd(UINT32 nPRDTblAddr, UINT32 nSectCnt, bool_T isRead);

#define SATA_DMAIO_CMD_STS_DONE			0x0200	
#define SATA_DMAIO_CMD_STS_DONE_ERR	0x0400	
#define SATA_DMAIO_CMD_STS_EXECING	0x0800
#define SATA_DMAIO_CMD_STS_RST			0x1000
unsigned int sata_poll_dmaio_cmd_status(bool_T autoSendFIS34, bool_T boECCfailDetected);





 bool_T sata_exec_pio_cmd(unsigned int nPRDTblAddr, void *,
			unsigned int nMaxDATASize,
			unsigned int nSectcnt, bool_T isRead,
			bool_T autoSendFIS34,
			bool_T bFirstIter,
			bool_T bLastIter,
			bool_T boClearLBAfield);





void sata_report_status(UINT8 Status, UINT8 Error);


#endif

