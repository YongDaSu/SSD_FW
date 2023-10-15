
#ifndef _SMART_H_
#define _SMART_H_

#include <sata.h>

__packed typedef struct
{
	UINT32 dwStartLSB;	
	UINT32 dwStartMSB;	
	UINT32 dwEndLSB;	
	UINT32 dwEndMSB;	
} _LBA_SPAN;

typedef struct
{
	UINT16 wRevisionNum;
	_LBA_SPAN aSpan[5];
	UINT8 abReserved[256];
	UINT8 abVendor1[154];
	UINT32 dwCurLBA0;
	UINT32 dwCurLBA1;
	UINT16 wCurSpan;
	UINT16 wFlags;
	UINT32 dwVendor2;
	UINT16 wPendingTime;
	UINT8 bReserved;	
	UINT8 bChecksum;	
} _SEL_SELFTEST_LOG;

__packed typedef struct
{
	byte bAttrID;
	word wStatusFlag;
	byte bAttrValue;
	byte bWorst;
	byte abRaw[6];
	byte bReserved;
		
} _IND_ATTR_DATA;


__packed typedef struct
{
	byte bAttrID;
	word wStatusFlag;
	byte bAttrValue;
	byte abVendor[8];	
} _OLD_IND_ATTR_DATA;


typedef struct
{
	word wRevisionNum;
	_IND_ATTR_DATA aIndAttrData[30];
	byte bOfflineCollectStatus;
	byte bSelftestExeStatus;
	word wOfflineCollectTotalTime;
	byte bVendor1;
	byte bOfflineCollectCapability;
	word wSmartCapability;
	byte bErrLogCapability;
	byte bVendor2;
	byte bShortPollingTime;
	byte bExtendedPollingTime;
	byte bConveyancePollingTime;
	word wExtendedPollingTime;
} _DEVICE_ATTR_DATA;

typedef struct
{
	byte bAttrID;
	byte bAttrThreshold;
	byte abReserved[10];
} _IND_ATTR_THRESHOLD;

typedef struct
{
	word wRevisionNum;
	_IND_ATTR_THRESHOLD aIndAttrThreshold[30];
	byte abReserved[18];
	byte abVendor[131];
	byte bChecksum;	
} _DEVICE_ATTR_THRESHOLD;

__packed typedef struct
{
	byte bAttrID;
	word wStatusFlag;
	byte bThreshold;
} _FTL_SMART;

typedef struct
{
	byte bAttrID;
	word wStatusFlag;
	byte bAttrValue;
	//byte bWorst;
	byte bThreshold;	// bThreshold = bWorst(refer to TSB spec.)
} _ATA_SMART;

typedef struct			// SCT command format
{
	UINT16 wAction;		
	UINT16 wFun;
	UINT16 wParameter[10];
} _SCT_CMD;

typedef struct
{
	UINT16 wAction;		
	UINT16 wFun;
	union
	{
		UINT16 wSelection;
		UINT16 wFeature;	
		UINT16 wTblID;	
	} u0;
	// Error Recovery Control
	UINT16 wReadTimer;
	UINT16 wWriteTimer;
	// Feature Control
	//UINT16 wDefState[3];
	//UINT8  bDefOption[3];	// Option Flag
	
	UINT16 wState[3];	// wState[0] : write cache; wState[1] : write cache reordering; wState[2] : temperature logging
	UINT8  bOption[3];	// Option Flag

	// Data Table
	UINT8  bDataSect;	// transfer sector count of SCT Data Table command
	UINT8  bValueHDA;
	UINT8  bOneMin;
	UINT16 wIntervalTick;
	
	// SCT Extended Status
	UINT16 wExtStatus;
} _SCT_POOL;

typedef struct
{
	byte bHaltSystemID;
	byte abFlashID[7];
} _ATTR_HALT_ID;

__packed typedef struct
{
	word wAverageEraseCount;
	word wMaximumEraseCount;
	byte bAverageEraseCountHiByte;
	byte bMaximumEraseCountHiByte;
	//word wMinimumEraseCount;
} _ATTR_ERASE_COUNT_DATA;

__packed typedef struct
{
	word wMaxDieBadBlkNum;
	word wMaxTotalBadBlkNum;
	word wRetiringBlockNum;
} _ATTR_BAD_BLOCK_DATA;

//#define SMART_USR_PROTECT

#define SMART_RW_MODE					0
#define SMART_W_THROUGH_MODE			1
#define SMART_W_PROTECT_MODE			2
#define SMART_R_ONLY_MODE				3


#ifdef ATA_WD_REQUEST
#define NUM_OF_ATA_SMART   			(15)
#else
#define NUM_OF_ATA_SMART   			(17)
#endif

#define NUM_OF_FTL_SMART				(5)
#define NUM_OF_ALL_SMART				(NUM_OF_ATA_SMART+NUM_OF_FTL_SMART)
#define FTL_SMART_START_INDEX			NUM_OF_ATA_SMART

#define SMART_ATTR_DATA_REV			0x0010

// Log Address Definition
#define LOG_DIRECTORY_00					      0x00
#define LOG_SUMMARY_SMART_01				      0x01
#define LOG_COMPREHENSIVE_SMART_02			   0x02
#define LOG_EXTENDED_COMPREHENSIVE_SMART_03	0x03
#define LOG_DEVICE_STATISTICS_04			      0x04
#define LOG_SMART_SELFTEST_06				      0x06
#define LOG_EXTENDED_SELFTEST_07			      0x07
#define LOG_SELECTIVE_SELFTEST_09			   0x09
#define LOG_NCQ_QUEUED_10					      0x10
#define LOG_PHY_EVENT_COUNTERS_11			   0x11
#define LOG_HOST_VENDOR_80					      0x80
#define LOG_SCT_CMD_E0						      0xE0
#define LOG_SCT_DATA_E1						      0xE1

// SMART Definition
#define TIME_OFF_LINE_DATA_COLLECTION		   0x20

// Self-test polling time(unit:min)
#define TIME_POLL_SHORT_ST					      0x01
#define TIME_POLL_EXTENDED_ST				      TIME_POLL_SHORT_ST

#define TIME_SETUP_SELECTIVE				      1	//10

// Smart Test Type
#define SMART_OFFLINE					0x00
#define SMART_SHORT						0x01
#define SMART_EXTENDED					0x02
#define SMART_CONVEYANCE				0x03
#define SMART_SELECTIVE					0x04
#define SMART_READSCAN					0x05

// Subcommands of SMART EXECUTE OFF-LINE IMMEDIATE
#define SMART_OFFLINE_IN_OFFLINE			   SMART_OFFLINE			 
#define SMART_SHORT_IN_OFFLINE				SMART_SHORT 
#define SMART_EXTENDED_IN_OFFLINE			SMART_EXTENDED 
#define SMART_CONVEYANCE_IN_OFFLINE			SMART_CONVEYANCE 
#define SMART_SELECTIVE_IN_OFFLINE			SMART_SELECTIVE
#define SMART_ABORT_OFFLINE					0x7f
#define SMART_SHORT_IN_CAPTIVE				(0x80 | SMART_SHORT) 
#define SMART_EXTENDED_IN_CAPTIVE			(0x80 | SMART_EXTENDED) 
#define SMART_CONVEYANCE_IN_CAPTIVE			(0x80 | SMART_CONVEYANCE) 
#define SMART_SELECTIVE_IN_CAPTIVE			(0x80 | SMART_SELECTIVE)
 

// Selective self-test
// featue flags (in Selective self-test log) 
#define OFF_LINE_SCAN_ON				0x02
#define OFF_LINE_SCAN_PENDING			0x08
#define OFF_LINE_SCAN_ACTIVE			0x10

#define PENDINT_TIME					   1

// SCT Action Code
#define SCT_RW_LONG						0x01
#define SCT_WRITE_SAME					0x02
#define SCT_ERR_RECOVERY				0x03
#define SCT_FEATURE						0x04
#define SCT_DATA_TBL					   0x05
#define SCT_VENDOR						0x06



// SCT Error Recovery Control command
// Function Code 
#define ERR_ERCOVERY_SET				0x01
#define ERR_ERCOVERY_RETURN			0x02
// Selection Code
#define ERR_ERCOVERY_RD					0x01
#define ERR_ERCOVERY_WR					0x02
// Recovery time definition
#define MIN_RD_TIME_LIMIT				0x46
#define MIN_WR_TIME_LIMIT				0x46

// SCT Data Table command
// Function Code
#define DATA_TBL_RD_TABLE				0x01
// Table ID
#define DATA_TBL_HDA					   0x02
// Absolute HDA Temperature
#define HDA_FORMAT_VERSION				0x0002
#define HDA_SAMPLING_PERIOD 			0x0001		//unit = min., 0:disable
#define HDA_MAX_OP						0x7F		// 127C
#define HDA_OVER						   0x7F		// 127C
#define HDA_MIN_OP						0x81		// -127C
#define HDA_UNDER						   0x81		// -127C
#define HDA_CB_SIZE						478
#define HDA_MAGIC_NUM					0xAA55

typedef struct
{
	UINT16 wFormatVer;
	UINT16 wSamplingPeriod;
	UINT16 wInterval;
	UINT8 bMaxOpLimit;	
	UINT8 bOverLimit;	
	UINT8 bMinOpLimit;	
	UINT8 bUnderLimit;	
	UINT8 abReserved[20];
	UINT16 wCBSize;
	UINT16 wCBIndex;
	UINT8 abCB[HDA_CB_SIZE];
} _HDA_TEMPERATURE_HISTORY;

// Extended Status Codes   
#define ES_OK_00					   0x00
#define ES_INVALID_FUN_01			0x01
#define ES_LBA_02					   0x02
#define ES_OVERFLOW_03				0x03
#define ES_INVALID_FUN_ER_04		0x04
#define ES_INVALID_SEL_ER_05		0x05
#define ES_RD_TIMER_06				0x06
#define ES_WR_TIMER_07				0x07
#define ES_SCT_ABORT_08				0x08
#define ES_SCT_ERROR_09				0x09

#define ES_INVALID_FUN_RWL_0A		0x0A
#define ES_NO_CMD_0B				   0x0B
#define ES_INVALID_FUN_FC_0C		0x0C
#define ES_INVALID_FEA_FC_0D		0x0D
#define ES_INVALID_STATE_FC_0E	0x0E
#define ES_INVALID_OPTION_FC_0F	0x0F
#define ES_INVALID_ACT_10			0x10
#define ES_INVALID_TBL_11			0x11
#define ES_SLOCK_12					0x12
#define ES_INVALID_REV_13			0x13
#define ES_UN_ERROR_14				0x14
#define ES_TMOUT_15					0x15

#define ES_EXE_FFFF					0xFFFF


#ifdef ATA_LOG_DMA_EXT_ON
extern bool_T boLogDMAExt(UINT32 *pPRDAddr, bool_T isRead);
#endif


// the SET FEATURES command shall be determine the state of write cache if State = 01
// write cache shall be enabled if State = 02
// write cache shall be disable if State = 03
#ifdef ATA_SMART_SCT_ON
#define WRITE_CACHE_ENABLE		((boWriteCacheEnable&&(SCT_DATA_BASE.wState[0]==0x01))||(SCT_DATA_BASE.wState[0]==0x02))
#else
#define WRITE_CACHE_ENABLE		(boWriteCacheEnable)
#endif

extern void vSmartErrLog_Error(byte bType);
extern void vSmartErrLog_Command(byte bType);
extern void SMART_Subcommand(void);

#ifdef ATA_SMART_SCT_ON
extern void vSCTLogInit(void);
extern void vSCTResetAction(void);
extern void vSCTInit(bool_T boPowerOnCycle);
extern void vSCTReturnDefault(void);
extern void vSCTCmdReset(void);
extern void vSCTPollingThermalMeter(void);    
extern void vSCTReadStatus_E0(void);
extern void vSCTDataRead_E1(void);
extern void vSCTWriteCmd_E0(void);
extern void vSCTDataWrite_E1(void);
#endif

#ifdef ATA_FEATURE_NCQ
extern void vLogUpdate_NCQErr(bool_T boNQ, UINT8 Status, UINT8 Error);
#endif
extern void vLogUpdate_PhyEventReset(void);
extern void vLogUpdate_PhyEvent(byte bType);
extern void vLogUpdate_SmartErr(void);
extern void vLogUpdate_SmartErrExt(void);
extern void vLogUpdate_SmartSelfTest(void);
extern void vLogUpdate_SmartSelfTestExt(void);
extern void vLogUpdate_SmartSelfTestStatusUpdate(void);
extern void vLogUpdate_SmartSelfTestStatusReload(void);


extern void ata_read_log_ext(void);
extern void ata_write_log_ext(void);

static void vReadLogExt_00(void);
static void vReadLogExt_03(void);
static void vReadLogExt_07(void);
static void vReadLogExt_10(void);
static void vReadLogExt_11(void);
static void vReadLogExt_80(void);
static void vWriteLogExt_80(void);


extern void vFTLgetIndAttrData(_IND_ATTR_DATA *pIndAttrData);

extern _SCT_POOL SCT_DATA_BASE;

extern byte gbFtlWriteProtect;

#endif  //_SMART_H_
