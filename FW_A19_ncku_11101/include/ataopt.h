#ifndef _ATAOPT_H_
#define _ATAOPT_H_

#include <smart.h>
#include <autocfg.h>

//========================================================================
//  ataopt.c
//========================================================================

#define READ_DATA		1
#define WRITE_DATA		0

#define ACTIVE_MODE		00
#define IDLE_MODE		01
#define STANDBY_MODE	02
#define SLEEP_MODE		03
//------------------------------------------------------------------------
extern UINT32	dwSYStimestamp;
extern byte 	PM_mode;
extern bool_T 	boStandbyTimerEnable;
extern dword	dwStandbyTimerValue;
extern dword	dwStandbyTimerCount;
extern bool_T 	boATA_SectorNumValid;
extern byte 	bATA_MultiSectorNum;

extern dword CHS_TOTAL_SECTORS;
extern word	wCHS_Def_Cylinders;
extern word wCHS_Current_Cylinders;
extern byte bCHS_Current_Heads;
extern byte bCHS_Current_Sectors;

extern byte bTAG;
extern bool_T boForceUnitAccess;
extern bool_T boAutoActivateEnable;
extern bool_T boRevertingToDefaults;
extern bool_T boAPMEnable;
extern byte	  bAPM_Value;
extern bool_T boWriteCacheEnable;
extern bool_T boLookAheadEnable;
extern byte bATA_CurrentDMAMode;
extern byte bATA_CurrentDMAType;

//extern dword NATIVE_MAX_LBA;
//------------------------------------------------------------------------
extern void ataopt_init(bool_T boPowerOnCycle, struct ata_stuff *p);
extern void vUpdate_CHS_Parameter(void);
extern void vCalChecksum(byte *dst);
extern bool_T boPIO_Data_Out(UINT32 *pPRDAddr);
extern bool_T boPIO_Data_In(UINT32 *pPRDAddr, bool_T boClearLBAfield);
extern void DCO_Subcommand(byte bSubCommand);
extern void HPA_Subcommand(byte bSubCommand);



extern dword SYS_MAX_LBA;

#define LOGSIZE_IN_BLOCKS_00H				1
#define LOGSIZE_IN_BLOCKS_01H				1
#define LOGSIZE_IN_BLOCKS_02H				51
#define LOGSIZE_IN_BLOCKS_03H				64
#define LOGSIZE_IN_BLOCKS_06H				1
#define LOGSIZE_IN_BLOCKS_07H				1
#define LOGSIZE_IN_BLOCKS_09H				1
#define LOGSIZE_IN_BLOCKS_10H				1
#define LOGSIZE_IN_BLOCKS_11H				1
#define LOGSIZE_IN_BLOCKS_80H				16
// for SCT
#define LOGSIZE_IN_BLOCKS_E0H				1
#define LOGSIZE_IN_BLOCKS_E1H				1

//#define SYSTEM_RESERVED_LBA						768//384KB
//#define LBA_ADDR_SYS_INFO_LBA						NATIVE_MAX_LBA+LBA_OFFSET_VALUE+1
#define LBA_ADDR_SYS_INFO_OFFSET					      (0)	// 2  page	
#define LBA_ADDR_LOG_SMART_SUMMARY_OFFSET			   (2)	// 1  page
#define LBA_ADDR_LOG_SMART_ERR_OFFSET				   (LBA_ADDR_LOG_SMART_SUMMARY_OFFSET + LOGSIZE_IN_BLOCKS_01H)		//LBA 3 & 51 pages
#define LBA_ADDR_LOG_SMART_ERR_EXT_OFFSET			   (LBA_ADDR_LOG_SMART_ERR_OFFSET + LOGSIZE_IN_BLOCKS_02H)			//LBA 54 & 64  pages
#define LBA_ADDR_LOG_SMART_SELFTEST_OFFSET			(LBA_ADDR_LOG_SMART_ERR_EXT_OFFSET + LOGSIZE_IN_BLOCKS_03H)		//LBA 118 & 1 page
#define LBA_ADDR_LOG_SMART_SELFTEST_EXT_OFFSET		(LBA_ADDR_LOG_SMART_SELFTEST_OFFSET + LOGSIZE_IN_BLOCKS_06H)		//LBA 119 & 1 page
#define LBA_ADDR_LOG_SELECTIVE_SELFTEST_OFFSET		(LBA_ADDR_LOG_SMART_SELFTEST_EXT_OFFSET + LOGSIZE_IN_BLOCKS_07H) 	//LBA 120 & 1 page
#define LBA_ADDR_LOG_NCQ_ERR_OFFSET					   (LBA_ADDR_LOG_SELECTIVE_SELFTEST_OFFSET + LOGSIZE_IN_BLOCKS_09H) 	//LBA 121 & 1 page
#define LBA_ADDR_LOG_PHY_COUNTER_OFFSET				(LBA_ADDR_LOG_NCQ_ERR_OFFSET + LOGSIZE_IN_BLOCKS_10H) 			//LBA 122 & 1 page
//#define LBA_ADDR_LOG_HOST_VENDER_OFFSET				(LBA_ADDR_LOG_PHY_COUNTER_OFFSET + LOGSIZE_IN_BLOCKS_11H)		//LBA 123 & 16*32 pages
//#define LBA_ADDR_LOG_SCT_DATA_TBL_OFFSET			(LBA_ADDR_LOG_HOST_VENDER_OFFSET + LOGSIZE_IN_BLOCKS_80H*32)		//LBA 635 & 1 pages
//#define LBA_ADDR_END_OFFSET							(LBA_ADDR_LOG_SCT_DATA_TBL_OFFSET + LOGSIZE_IN_BLOCKS_E1H)		//LBA 636
// fywei 0503 exchange the position of LBA_ADDR_LOG_HOST_VENDER_OFFSET and LBA_ADDR_LOG_SCT_DATA_TBL_OFFSET, so we can save every flushinfo time
#define LBA_ADDR_LOG_SCT_DATA_TBL_OFFSET			   (LBA_ADDR_LOG_PHY_COUNTER_OFFSET + LOGSIZE_IN_BLOCKS_11H )		//LBA 123 & 1 pages
#define LBA_ADDR_LOG_HOST_VENDER_OFFSET				(LBA_ADDR_LOG_SCT_DATA_TBL_OFFSET + LOGSIZE_IN_BLOCKS_E1H  )		//LBA 124 & 16*32 pages
#define LBA_ADDR_END_OFFSET							   (LBA_ADDR_LOG_HOST_VENDER_OFFSET + LOGSIZE_IN_BLOCKS_80H*32 )		//LBA 636

#ifdef DEGRADE_FLASH
#define LOGICAL_FAIL_COUNT						60
#else
#define LOGICAL_FAIL_COUNT						8//30:UNC queue depth
#endif

#define SMART_ERR_LOG_PAGE_SIZE				256 //51*5+1
#define SMART_EXT_LOG_PAGE_SIZE				257 //64*4+1

#define TRIM_MAX_NUM	2

//Security definition
#define SEC_PASSWD_LEN		32

#pragma pack(1)     /* byte alignment */

typedef struct
{
	byte bDCOstate;
	byte abData[46];
}_DCO_INFO;

typedef struct
{
	byte bHPAstate;
	dword HPA_MAX_LBA;
} _HPA_INFO;

typedef struct 
{
	byte master_password[SEC_PASSWD_LEN];   	// security
	byte user_password[SEC_PASSWD_LEN];
	byte security_enable;
	byte security_level;					// 0: high or 1: Maximum
	word password_identifier;			// password hint
} _SECURITY_INFO;

typedef struct 
{
	byte SMART_enable;	 			// SMART
	byte SMART_autosave;				// 0: disable  1: enable
	byte bSMARTerrLogIndex;				// 0~255
	word wSMARTerrCount;				// 0~FFFF
	word wSMARTextLogIndex;				// 0~256
	word wSMARTerrCountEXT;				// 0~FFFF
} _SMART_INFO;

typedef struct
{
	UINT16 wDefState[3];
	UINT8  bDefOption[3];				// Option Flag
	
} _SCT_INFO;


typedef struct
{
	word wCount;
	word wBlockUnit;
	byte bPageNo;
	byte bCh;
	byte bBank;
	byte bReserved;	
} _ECC_FAIL_PHYSICAL;

typedef struct
{
	byte	bErrType;
	dword 	dwStartLBA;
	dword 	dwEndLBA;
} _ECC_FAIL_CONTENT;

typedef struct
{
	byte 				bIndex;
	_ECC_FAIL_CONTENT	abECCfail[LOGICAL_FAIL_COUNT];
} _ECC_FAIL_LOGICAL;

typedef struct
{
	byte bSSPinfoValidTag;
	bool_T boSecurityMode_Locked;
	bool_T boSecurityMode_Frozen;
	byte bSecurityMode_Count;
	bool_T boStandyTimer_Enable;
	dword dwStandyTimer_Value;
	dword dwStandyTimer_Count;
	byte bHPAstate;
	dword dwSetMaxAddress;
	bool_T boAPMEnable;
	byte bAPM_Value;
	bool_T boWriteCacheEnable;
	byte bTransferMode_Mode;
	byte bTransferMode_Type;
	bool_T boReadLookAhead;
	bool_T boMultipleMode_Valid;
	byte bMultipleMode_Count;
	byte bCHSheads;
	byte bCHSsectors;
	bool_T boRevertingToDefaults;
	bool_T boDevSleepEnable;
	bool_T boDIPMenable; //eddie adds for DEVSLP REDUCED_PWR_STATE
} _SSP_INFO;

typedef struct 
{
   dword qwSR8M;
   dword qwSR4M;
   dword qwSR1M;
   dword qwSR128K;
   dword qwSR64K;
   dword qwSR32K;
   
   dword qwSW8M;
   dword qwSW4M;
   dword qwSW1M;
   dword qwSW128K;
   dword qwSW64K;
   dword qwSW32K;
   
   dword qwRR64K;
   dword qwRR32K;
   dword qwRR16K;
   dword qwRR8K;
   dword qwRR4K;
   
   dword qwRW64K;
   dword qwRW32K;
   dword qwRW16K;
   dword qwRW8K;
   dword qwRW4K;  
   
   qword qwSctrWtn; 
   
   dword dwRrCmdCnt;
   dword dwWrCmdCnt;
        
} _DATA_LOG;

typedef struct
{
	word 			         wPowerCycleCount;		//2
	word 			         wPowerLossCount;		//2
	word 			         wLifeTimestamp;			//2 (in Hours)
	_DCO_INFO 		      DCOinfo;			//47
	_HPA_INFO 		      HPAinfo;			//5==>8
	_SECURITY_INFO		   SECURITYinfo;			//68
	_SMART_INFO		      SMARTinfo;			//9==>10
	_SCT_INFO		      SCTinfo;			//9
	_ECC_FAIL_PHYSICAL   ECCfailPhysical;		//8
	_ECC_FAIL_LOGICAL	   ECCfailLogical;			//271==>364
	_SSP_INFO	         SSPinfo; //30
	byte			         bDevSlpSaveSSP;
	byte				      bWPEnable;	// Write Protect
	byte				      bPSEnable;	// Power Saving	
	_DATA_LOG            DataLog;
	byte                 bDataLogEnable;
	word                 wSecureEraseCount;
} _SYS_INFO;

#pragma pack()    /* reset to default alignment */

extern _SYS_INFO sSYSinfo;

//========================================================================
//  DCO command set
//========================================================================
extern UINT16 DCO_IDENTIFY_INFO_WORD0;
extern UINT16 DCO_IDENTIFY_INFO_WORDn;

#define DCO_DATA_REVISION				   (((word)sSYSinfo.DCOinfo.abData[(0<<1)+1] << 8) | ((word)sSYSinfo.DCOinfo.abData[0<<1]))
#define DCO_MDMA_SUPPORT_MODE			   (sSYSinfo.DCOinfo.abData[1<<1] & 0x07) //v
#define DCO_UDMA_SUPPORT_MODE			   (sSYSinfo.DCOinfo.abData[2<<1] & 0x7F) //v
#define DCO_MAX_LBA						   (((dword)sSYSinfo.DCOinfo.abData[(4<<1)+1] << 24) | ((dword)sSYSinfo.DCOinfo.abData[4<<1] << 16) | \
										         ((dword)sSYSinfo.DCOinfo.abData[(3<<1)+1] << 8) | ((dword)sSYSinfo.DCOinfo.abData[3<<1])) //v
#define DCO_SMART_CONVEYANCE_ENABLE		((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x20) == 0x20) 
#define DCO_SMART_SELECTIVE_ENABLE		1	//((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x10) == 0x10) 

#define DCO_FUA_ENABLE					   1	// ((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x08) == 0x08)
//#define DCO_LBA48_ENABLE				   1	// ((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x01) == 0x01)
//#define DCO_HPA_ENABLE					((sSYSinfo.DCOinfo.abData[7<<1] & 0x80) == 0x80) 
#define DCO_HPA_ENABLE					   (MP_HPA_ENABLE ? ((sSYSinfo.DCOinfo.abData[7<<1] & 0x80) == 0x80) : 0)
#define DCO_SECURITY_ENABLE				((sSYSinfo.DCOinfo.abData[7<<1] & 0x08) == 0x08) 
#define DCO_SMART_ERRLOG_ENABLE			((sSYSinfo.DCOinfo.abData[7<<1] & 0x04) == 0x04) 
#define DCO_SMART_SELFTEST_ENABLE		((sSYSinfo.DCOinfo.abData[7<<1] & 0x02) == 0x02) 

// fywei
//#define DCO_SMART_ENABLE				((sSYSinfo.DCOinfo.abData[7<<1] & 0x01) == 0x01) 
#define DCO_SMART_ENABLE            SUPPORT_SMART

#define DCO_SSP_ENABLE					(MP_SSP_ENABLE)//((sSYSinfo.DCOinfo.abData[8<<1] & 0x10) == 0x10) 
#define DCO_IPM_ENABLE              0
//#define DCO_IPM_ENABLE					((sSYSinfo.DCOinfo.abData[8<<1] & 0x04) == 0x04) 

//fywei
//#define DCO_NCQ_ENABLE					0	//((sSYSinfo.DCOinfo.abData[8<<1] & 0x01) == 0x01) 
#define DCO_NCQ_ENABLE              SUPPORT_NCQ

#define DCO_WRITE_UNCORRECTABLE_EXT 1	// ((sSYSinfo.DCOinfo.abData[(21<<1)+1] & 0x20) == 0x20)
#define DCO_TRIM_ENABLE					1	// ((sSYSinfo.DCOinfo.abData[(21<<1)+1] & 0x04) == 0x04) 
#define DCO_IPM_APS_ENABLE				((sSYSinfo.DCOinfo.abData[8<<1] & 0x20) == 0x20) 

//#define DCO_FUA_ENABLE				((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x08) == 0x08) //v
//#define DCO_LBA48_ENABLE				((sSYSinfo.DCOinfo.abData[(7<<1)+1] & 0x01) == 0x01) //v
//#define DCO_HPA_ENABLE				((sSYSinfo.DCOinfo.abData[7<<1] & 0x80) == 0x80) //v
//#define DCO_SECURITY_ENABLE			((sSYSinfo.DCOinfo.abData[7<<1] & 0x08) == 0x08) //v
//#define DCO_SMART_ERRLOG_ENABLE		((sSYSinfo.DCOinfo.abData[7<<1] & 0x04) == 0x04) //v
//#define DCO_SMART_SELFTEST_ENABLE		((sSYSinfo.DCOinfo.abData[7<<1] & 0x02) == 0x02) //v
//#define DCO_SMART_ENABLE				((sSYSinfo.DCOinfo.abData[7<<1] & 0x01) == 0x01) //v
//#define DCO_SSP_ENABLE				((sSYSinfo.DCOinfo.abData[8<<1] & 0x10) == 0x10) //v
//#define DCO_IPM_ENABLE				((sSYSinfo.DCOinfo.abData[8<<1] & 0x04) == 0x04) //v
//#define DCO_NCQ_ENABLE				((sSYSinfo.DCOinfo.abData[8<<1] & 0x01) == 0x01) //v
//#define DCO_WRITE_UNCORRECTABLE_EXT	((sSYSinfo.DCOinfo.abData[(21<<1)+1] & 0x20) == 0x20) //v

extern void vDCO_Restore(bool_T);
extern void vDCO_Identify(void);
extern void vDCO_Set(void);
extern bool_T boDCO_SetInvalid(void);
extern void vDCO_Init(bool_T);
extern void vDCO_Update_DMA_Mode(void);

extern byte bDCO_DMA_Mode;
extern byte bDCO_DMA_Type;
extern byte DCO_LBA48_ENABLE;
extern byte bDCOstate;
#define DCO_STATE_FACTORY_CONFIG	0x11
#define DCO_STATE_LOCKED					0x22
#define DCO_STATE_REDUCED_CONFIG	0x44

//========================================================================
//  HPA command set
//========================================================================

extern void HPA_ReadNativeMaxAddr(void);
extern void HPA_ReadNativeMaxAddr48(void);
extern void HPA_SetMaxAddr48(void);
extern void vHPA_SetMAX(bool, dword);
extern bool_T boHPA_SetMaxInvalid(byte bMode, UINT32 *pdwATA_LBA);
extern void vHPA_SetPassword(void);
extern bool boHPA_PasswordInvalid(void);

extern byte bHPAstate;
extern byte bHPAsetMAXprepare;
extern byte bHPAsetMAX_VV;
extern bool_T boHPAnonVolatileSet;
extern byte bHPAsecurityState;	
extern bool_T boHPAsecurityEnable;
extern byte bHPAsecurityCount;	
extern byte abHPApassword[32];	

#define HPA_STATE_NOT_SET						0x00
#define HPA_STATE_28BIT_SET					0x01
#define HPA_STATE_48BIT_SET					0x02

#define HPA_SECURITY_STATE_UNLOCKED		0x00
#define HPA_SECURITY_STATE_LOCKED			0x01
#define HPA_SECURITY_STATE_FROZEN			0x02

//========================================================================
//  SSP command set
//========================================================================

extern void vSSP_Update(void);

extern _SSP_INFO sSSPinfo;
extern bool_T boSSPEnable;

//========================================================================
//  Security command set
//========================================================================

extern void Security_Set_Password(void);
extern void Security_Unlock(void);
extern void Security_Erase_Prepare(void);
extern void Security_Erase_Unit(void);
extern void Security_Freeze_Lock(void);
extern void Security_Disable_Password(void);
extern bool_T boSecurityLocked;
extern bool_T boSecurityFrozen;
extern bool_T boSecurityErasePrepare;
extern byte bSecurityCounter;

//========================================================================
//  SMART command set
//========================================================================

#pragma pack(1)     /* byte alignment */

typedef struct 
{
	byte bControl;
	byte bFeature;
	byte bCount;
	byte bLBALow;
	byte bLBAMid;
	byte bLBAHigh;
	byte bDevice;
	byte bCommand;
	dword dwTimestamp;
} _SMART_ERR_COMMAND_DATA;

typedef struct 
{
	byte bReserved;
	byte bError;
	byte bCount;
	byte bLBALow;
	byte bLBAMid;
	byte bLBAHigh;
	byte bDevice;
	byte bStatus;
	byte abExtendErrInfo[19];
	byte bState;
	word wLifeTimestamp;
} _SMART_ERR_ERROR_DATA;

typedef struct 
{
	byte 					bIndex;
	_SMART_ERR_COMMAND_DATA CommandData[5];
	_SMART_ERR_ERROR_DATA 	ErrData;
} _LOG_SMART_ERR;

typedef struct 
{
	byte bControl;
	byte bFeature;
	byte bFeatureExp;
	byte bCount;
	byte bCountExp;
	byte bLBALow;
	byte bLBALowExp;
	byte bLBAMid;
	byte bLBAMidExp;
	byte bLBAHigh;
	byte bLBAHighExp;
	byte bDevice;
	byte bCommand;
	byte bReserved;
	dword dwTimestamp;
} _SMART_ERR_EXTEND_COMMAND_DATA;

typedef struct 
{
	byte bControl;
	byte bError;
	byte bCount;
	byte bCountExp;
	byte bLBALow;
	byte bLBALowExp;
	byte bLBAMid;
	byte bLBAMidExp;
	byte bLBAHigh;
	byte bLBAHighExp;
	byte bDevice;
	byte bStatus;
	byte abExtendErrInfo[19];
	byte bState;
	word wLifeTimestamp;
} _SMART_ERR_EXTEND_ERROR_DATA;

typedef struct 
{
	byte 							bIndex;
	_SMART_ERR_EXTEND_COMMAND_DATA 	CommandData[5];
	_SMART_ERR_EXTEND_ERROR_DATA 	ErrData;
} _LOG_SMART_ERR_EXT;

typedef struct
{
	byte bLBAfield;
	byte bStatus;
	word wLifeTimeStamp;
	byte bCheckPoint;
	byte bFailingLBA0;
	byte bFailingLBA1;
	byte bFailingLBA2;
	byte bFailingLBA3;
	byte abVender[15];
} _LOG_SMART_SELFTEST_ENTRY;

typedef struct
{
	byte bLBAfield;
	byte bStatus;
	word wLifeTimeStamp;
	byte bCheckPoint;
	byte bFailingLBA0;
	byte bFailingLBA1;
	byte bFailingLBA2;
	byte bFailingLBA3;
	byte bFailingLBA4;
	byte bFailingLBA5;
	byte abVender[15];
} _LOG_SMART_SELFTEST_ENTRY_EXT;

#pragma pack()    /* reset to default alignment */

extern _LOG_SMART_ERR 		SMART_ERR_LOG;
extern _LOG_SMART_ERR_EXT 	SMART_EXT_LOG;

#define SMART_LOGTYPE_28BIT			0
#define SMART_LOGTYPE_48BIT			1
#define SMART_LOGTYPE_COMRESET	2
#define SMART_LOGTYPE_SWRESET		3
#define SMART_LOGTYPE_NOLOG			4

extern byte 	bSMARToffLineStatus;
extern byte 	bSMARTselfTestStatus;
extern byte 	bSMARTselfTestType;
extern bool_T 	boSMARTselfTestSuspend;
extern byte 	bSMARTlogType;
extern byte 	bSMARTerrLogState;

#define SMART_OFFLINE_NEVER_START	0
#define SMART_OFFLINE_COMPLETE		2
#define SMART_OFFLINE_IN_PROGRESS	3
#define SMART_OFFLINE_SUSPEND			4
#define SMART_OFFLINE_ABORTED			5

#define SMART_SELFTEST_WITHOUT_ERR					0x00
#define SMART_SELFTEST_ABORTED							0x10
#define SMART_SELFTEST_INTERRUPT_WITH_RESET	0x20
#define SMART_SELFTEST_IN_PROGRESS					0xF0

//========================================================================
//  GPL command set
//========================================================================

typedef struct 
{
	UINT16 wCommandFailedID_01;	//0
	
	UINT16 wD2HDataID_03;		// R_ERRP for Device-to-Host Data FIS		
	UINT16 wH2DDataID_04;		// R_ERRP for Host-to-Device Data FIS		
	UINT16 wD2HNonDataID_06;	// R_ERRP for Device-to-Host non-Data FIS		
	UINT16 wH2DNonDataID_07;	// R_ERRP for Host-to-Device non-Data FIS		
	UINT16 wD2HNonDataRetryID_08;	// R_ERRP for Device-to-Host non-Data FIS retries
	UINT32 dwTransitionID_09;	// Transitions from drive PHYRDY to drive PHYRDYn
			
	UINT32 dwSignatureID_0A;		//1
	
	UINT16 wH2DDataCRCID_0F;	// R_ERRP for Host-to-Device Data FIS due to CRC errors
	UINT16 wH2DDataNonCRCID_10;	// R_ERRP for Host-to-Device Data FIS due to non-CRC errors
	UINT16 wH2DNonDataCRCID_12;	// R_ERRP for Host-to-Device non-Data FIS due to CRC errors
	UINT16 wH2DNonDataNonCRCID_13;	// R_ERRP for Host-to-Device non-Data FIS due to non-CRC errors

} _LOG_SATA_PHY_EVENT;

typedef struct 
{
	byte bTAG;
	byte bStatus;
	byte bError;
	byte bLBA_Low;
	byte bLBA_Mid;
	byte bLBA_High;
	byte bDevice;
	byte bLBA_Low_Exp;
	byte bLBA_Mid_Exp;
	byte bLBA_High_Exp;
	byte bSector_Count;
	byte bSector_Count_Exp;
} _LOG_NCQ_COMMAND_ERR;



extern byte	bLog_Specific;
extern word	wLog_BlockCount;
extern byte	bLog_Address;
extern byte	bLog_HostLogAddr;
extern word	wLog_PageNum;
extern _LOG_SATA_PHY_EVENT PHY_EVT_LOG;
extern _LOG_NCQ_COMMAND_ERR NCQ_ERR_LOG;


extern void vSYSinfoUpdate(void);
extern void vSYSinfoUpdateIm(void);
extern void vSYSInfoFlush(void);
extern void vSYSinfoPowerLossUpdate(void);

#endif // _ATACMD_H_


