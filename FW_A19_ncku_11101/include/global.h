/* vi: set sw=4 ts=4: */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <string.h>
#include <autocfg.h>

#define  JMF667_SATA
#define  JMF667_SLUMBER_WA

// fywei 0417
#define  NAND_DLL_OFF // turn off NAND DLL during slow cpu clock state
#ifdef NAND_DLL_OFF
#define		ADVANCED_SLUMBER // turn off PLL and enter IDDQ during slow cpu clock and slumber state, must need NAND_DLL_OFF definition
#endif

// Thomas 1001
//#define InnerTest
//#define		TOSHIBA_A19

// IOPS related
//---------------------------------
#define BAD_BLOCK_RATIO    (4)
#define SYS_BLOCK_NUM      (5)
//---------------------------------

#define DBG_HOST_IDLE_DUMP_MSG
//#define DEVSLPDBG

#define GLOBAL_DBG_LEVEL	1
// GLOBAL_DBG_ON ranged in 3~0(default value = 1)
// 0: no any UART message
// 1: print error messages
// 2: error & warning message
// 3: error, warning & debug message

//#define JMF665_NEW_SCRAMBLE
//#define JMF665_NEW_SCRAMBLE_FW_SEED

#define EXTEND_BLOCK

#define RAND_SEED_TBL // use new random seed in scramble function

//#define JTAG_MODE
#define FPGA_MODE    0   /* 1: for FPGA; 0: for ASIC */
#if (FPGA_MODE == 0)
#define SW_CLK SYS_375MHZ 	// undef it meant HW clk is used in run-time and "clk down" feature is disabled (see sata.h).
//#define SW_CLK SYS_300MHZ
//#define SW_CLK SYS_250MHZ
//#define SW_CLK SYS_150MHZ
#endif



//#define 	JM_MPTool
//***********************************************************
//* Flash type define
//***********************************************************
// ONFI/Toggle mode define

#ifdef JM_MPTool
   //#define 	TOGGLE_MD
   //#define 	ONFI_MD
#endif

#define  LOW_PAGE_MODE		SUPPORT_ISLC // iSLC




#ifdef ONFI_MD
//#define ONFI_18 // enable if flash VCCQ = 1.8V
#endif

//***********************************************************
//* Function define
//***********************************************************
//#define 	PREFORMAT_FLASH
//***********************************************************



//#define AES_RANDOM
//#define EN_VALID_SWCAL


#define AHB_BUS_CHK
#define NEW_FUNCTION


#define QUICK_TABLE_FUN
#ifdef QUICK_TABLE_FUN
//	#define DRAM_POWER_DOWN
//	#define IDLE_DRAM_POWER_DOWN
#endif


#define FTL_LIB
//#ifdef FTL_LIB
	//re-definitions below generateed by autocfg.h
//	#undef SECTOR_SHIFT
//	#undef PAGE_SHIFT
//	#undef BLOCK_SHIFT
	#undef GAP_SHIFT
	
//	#define SECTOR_SHIFT (sFTLParam.bSectorShift)
//	#define PAGE_SHIFT   (sFTLParam.bPageShift)
//	#define BLOCK_SHIFT  (sFTLParam.bBlockShift)

	#define GAP_SHIFT    0//(sFTLParam.bGapShift)
//#endif


#if (INTEL_FLASH==1)
#define IM_FLASH
#define NEW_IM_FLASH
#elif (TOSHIBA_FLASH==1)
#define EN_SHIFT_RD
#endif


/* NAND Flash Vendor */
#define MAX_FLASH_VENDOR		(5)
#define MICRON_FLASH_TYPE		(0)
#define SAMSUNG_FLASH_TYPE		(1)
#define TOSHIBA_FLASH_TYPE		(2)
#define HYNIX_FLASH_TYPE		(3)
#define INTEL_FLASH_TYPE		(4)

// flash config
#define HW_MAX_CHANS    (8)
#define HW_MAX_BANKS    (8)
#define HW_MAX_DIES     (2)
#define HW_MAX_PLANES   (2)


/***********************************************************
 *   For different require, need modify
 ***********************************************************/
//ver.c definition
//#define __CMPL_CODE__ "308I"

//timer definition
#define CONFIG_TMR_TICK_HZ 400
//If there exists no IO over 5 second, system-io idle is detected.
#define CONFIG_SYS_IDLE_HZ (2 * CONFIG_TMR_TICK_HZ)
//The starting occasion to detect system-io idle.
#define CONFIG_SYS_START_HZ (60 * CONFIG_TMR_TICK_HZ)
//flush cach time out setting
#define CONFIG_SYS_TO_HZ (6 * CONFIG_TMR_TICK_HZ)

//The starting occasion to detect system-io idle.
#define CONFIG_SYS_START_HZ_2 (15 * CONFIG_TMR_TICK_HZ)
#define CONFIG_SYS_6sec  (6 * CONFIG_TMR_TICK_HZ)
#define CONFIG_SYS_100ms (CONFIG_TMR_TICK_HZ / 10)
#define CONFIG_SYS_300ms (CONFIG_TMR_TICK_HZ / 3)



//***********************************************************
//* DRMA Size Define 
//***********************************************************
#define BGET_ALLOC_BASE (0x100000)
//#define BGET_ALLOC_SIZE (0x200000)
//#define BGET_ALLOC_BASE (0x30000)
#define BGET_ALLOC_SIZE (0x8000000 - BGET_ALLOC_BASE)	// 64Mb(8MB)
//#define BGET_ALLOC_SIZE (0x2000000 - BGET_ALLOC_BASE)	// 32Mb

     
//#define SYS_INFO_BASE   (0x1E40000) //384K ==> 512K ????????????????????????????????????????


#define CONFIG_RST_RSST_AREA_BASE 0xB0004900
#define CONFIG_RST_RSST_AREA_SIZE 256 //count in byte

//debug enable definition
//#define ssdDebug        UARTprintf
#define ssdDebug(...)


#define IO_DRIVING      	(sParam.bIoDrive) //3 imply 8mA
#define BCH_SIZE     		(sParam.bECCmode) //(0, 1, 2, 3) = (BCH8, BCH16, BCH24, BCH40)
#define ECC_REFLASH_THR 	(sParam.D.SYS.bECCErrorCopyThreshold)
#define ECC_MARKBAD_THR 	(sParam.D.SYS.bReadErrorThreshold)
#define PLANE_SHIFT  		1//(sFTLParam.bPlaneShift)   //0: one plane command, 1: two plane command


//LBA number calculation
#define SYS_INFO_LBA_SIZE 768
#define DESCR_LBA_SIZE 512


/***********************************************************
 *   don't need modify
 ***********************************************************/
//#define SECTOR_NUM ((dword)(1 << SECTOR_SHIFT))
//#define CHAN_NUM (1 << CHAN_SHIFT)
//#define CE_NUM (1 << CE_SHIFT)
//#define PAGE_NUM (1 << PAGE_SHIFT)
//#define BLOCK_NUM (1 << BLOCK_SHIFT)


//#define BANK_MASK (BANK_NUM - 1)


//system
#define BYTE_SHIFT 8
#define WORD_SHIFT 16
#define BYTE_MASK ((1 << BYTE_SHIFT) - 1)
#define WORD_MASK ((1 << WORD_SHIFT) - 1)
#define DWORD_MASK 0xffffffff

#define PXNULL  ((byte *) 0)
#define PUBLIC
#define STATIC  static

#ifdef TRUE
  #undef TRUE
#endif
#ifdef FALSE
  #undef FALSE
#endif
#define TRUE     '\001'
#define FALSE    '\000'
#define SUCCESS  TRUE
#define FAIL     FALSE
#define NREADY   1
#define NBUSY    0


// uart
#define SYS_MAX_STR_SIZE  128
#define UARTCLKFREQ       75000000
#define UARTBAUDRATE      115200

// Interrupt
#define INTC_TMR    1
#define INTC_SATA   4
#define INTC_USB    5
#define INTC_UART   6
#define INTC_GPIO   15

// ata.c
#define D1_puts(s)       UARTputs(s)
#define _ASSERT(f, _s_)  do { if(!(f)) { UARTprintf _s_; while (1); } } while(0)

// register
#define SET_REG(reg, value)  (reg) = (value)
#define GET_REG(reg, target) (target) = (reg)

// LED
#define		HDDA_LED_OFF		0
#define		HDDA_LED_ON			1
#define		HDDA_LED_BLINK		2

/***********************************************************
 *   macros define
 ***********************************************************/
#define ARM_NOP() __asm{nop nop nop}

#define sc_enable_AHB2_limit() (rF_DRAMLMTCTRL &= ~0xC0); (rF_DRAMLMTTHR = 0x40); (rF_DRAMTR_DW) = (rF_DRAMTR_DW | (1 << 21))
#define sc_disable_AHB2_limit() (rF_DRAMTR_DW) = (rF_DRAMTR_DW & ~(1 << 21))

#define INIT_SECTION   __attribute__((section ("Init")))
#define ALWAYS_INLINE  __attribute__((always_inline))
#define _at_(s)        __attribute__((at(s)))

#define SYS_ENTER_CRITICAL(sr)  sr = sysCPUSaveSR()
#define SYS_EXIT_CRITICAL(sr)   sysCPURestoreSR(sr)


//DPDParam.FunctionEnable1

#ifdef JM_MPTool
      //FTLParam.bFlag
   #define SUPPORT_TRIM_CMD_BIT      (0x01)
   #define THERMAL_SENSOR_ENABLE_BIT (0x02)
   #define FLASH_SCRAMBLE_BIT        (0x10)
   #define REMAP_BIT                 (0x20)
   
   #define SUPPORT_TRIM_CMD          ((sFTLParam.bFlag & SUPPORT_TRIM_CMD_BIT) == SUPPORT_TRIM_CMD_BIT)
   #define THERMAL_SENSOR_ENABLE     ((sFTLParam.bFlag & THERMAL_SENSOR_ENABLE_BIT) == THERMAL_SENSOR_ENABLE_BIT)   
   #define SCRAMBLE_EN               ((sParam.bFunctionEnable1 & FLASH_SCRAMBLE_BIT) == FLASH_SCRAMBLE_BIT)   
   #define REMAP_ENABLE              ((sParam.bFunctionEnable1 & REMAP_BIT) == REMAP_BIT)
   #define COPY_BACK_ENABLE          0
   #define GPIO_WRITE_PROTECT       0        
   #define SECURITY_ERASE_ENABLE     0
   #define SUPPORT_ATA_LBA48_MODE    1
   
   //FTLParam.bParamFlag2
   #define IDLE_POWER_SAVING		 0
   #define SUPPORT_ISLC			     0
   #define SUPPORT_NCQ				 0
   #define SUPPORT_SMART			 1
   #define WRITE_PROTECT_VALUE		 0
   #define SUPPORT_IDEMA			 1
   #define CHS_VALUE_CAPACITY		 0
   
   //FTLParam.bParamFlag3
   #define	MP_SSP_ENABLE			  0
   #define	MP_HPA_ENABLE			  0
   #define	PSW_ERROR_ERASE_ALL		  0
   #define	INNOROBUST_ENABLE		  0  
   #define  DATALOG_SUPPORT        0 

#else // Inno MP tool
   //FTLParam.bParamFlag
   #define SUPPORT_TRIM_CMD_BIT      (0x01)
   #define THERMAL_SENSOR_ENABLE_BIT (0x02)
   #define FLASH_SCRAMBLE_BIT        (0x04)   
   #define COPY_BACK_BIT             (0x08)
   #define GPIO_WRITE_PROTECT_BIT   (0x10)
   #define SECURITY_ERASE_BIT        (0x20)
   #define SUPPORT_LBA48_MODE_BIT    (0x40)
   
   #define SUPPORT_TRIM_CMD          ((sFTLParam.bParamFlag & SUPPORT_TRIM_CMD_BIT) == SUPPORT_TRIM_CMD_BIT)
   #define THERMAL_SENSOR_ENABLE     ((sFTLParam.bParamFlag & THERMAL_SENSOR_ENABLE_BIT) == THERMAL_SENSOR_ENABLE_BIT)   
   #define SCRAMBLE_EN               ((sFTLParam.bParamFlag & FLASH_SCRAMBLE_BIT) == FLASH_SCRAMBLE_BIT)   
   #define COPY_BACK_ENABLE          ((sFTLParam.bParamFlag & COPY_BACK_BIT) == COPY_BACK_BIT)
   #define GPIO_WRITE_PROTECT       ((sFTLParam.bParamFlag & GPIO_WRITE_PROTECT_BIT) == GPIO_WRITE_PROTECT_BIT)
   #define SECURITY_ERASE_ENABLE     ((sFTLParam.bParamFlag & SECURITY_ERASE_BIT) == SECURITY_ERASE_BIT)
   #define SUPPORT_ATA_LBA48_MODE    ((sFTLParam.bParamFlag & SUPPORT_LBA48_MODE_BIT) == SUPPORT_LBA48_MODE_BIT)

   #define GPIO7_POWER_DETECT		    (sFTLParam.PowerDetectType)   
   
   //FTLParam.bParamFlag2
   #define IDLE_POWER_SAVING_BIT	   (0x01)
   #define SUPPORT_ISLC_BIT		 	(0x02)
   #define SUPPORT_NCQ_BIT			   (0x04)
   #define SUPPORT_SMART_BIT		   (0x08)
   #define WRITE_PROTECT_VALUE_BIT	(0x10)
   #define SUPPORT_IDEMA_BIT		   (0x20)
   #define CHS_VALUE_CAPACITY_BIT	(0x40)
   #define REMAP_BIT				      (0x80)
   
   #define IDLE_POWER_SAVING		   ((sFTLParam.bParamFlag2 & IDLE_POWER_SAVING_BIT) == IDLE_POWER_SAVING_BIT)
   #define SUPPORT_ISLC			 	   ((sFTLParam.bParamFlag2 & SUPPORT_ISLC_BIT) == SUPPORT_ISLC_BIT)
   #define SUPPORT_NCQ				   ((sFTLParam.bParamFlag2 & SUPPORT_NCQ_BIT) == SUPPORT_NCQ_BIT)
   #define SUPPORT_SMART			   ((sFTLParam.bParamFlag2 & SUPPORT_SMART_BIT) == SUPPORT_SMART_BIT)
   #define WRITE_PROTECT_VALUE	   ((sFTLParam.bParamFlag2 & WRITE_PROTECT_VALUE_BIT) == WRITE_PROTECT_VALUE_BIT)
   #define SUPPORT_IDEMA			   ((sFTLParam.bParamFlag2 & SUPPORT_IDEMA_BIT) == SUPPORT_IDEMA_BIT)
   #define CHS_VALUE_CAPACITY		   ((sFTLParam.bParamFlag2 & CHS_VALUE_CAPACITY_BIT) == CHS_VALUE_CAPACITY_BIT)
   #define REMAP_ENABLE			 	   ((sFTLParam.bParamFlag2 & REMAP_BIT) == REMAP_BIT)
   
   //FTLParam.bParamFlag3
   #define MP_SSP_ENABLE_BIT	 	   (0x01)
   #define MP_HPA_ENABLE_BIT		   (0x02)
   #define PSW_ERROR_ERASE_ALL_BIT	(0x04)
   #define INNOROBUST_ENABLE_BIT	   (0x08)
   #define SPI_BOOT_BIT             (0x10)
   #define DATALOG_SUPPORT_BIT      (0x20)
   #define ICELL_ENABLE_BIT         (0x40)
   #define	MP_SSP_ENABLE			   ((sFTLParam.bParamFlag3 & MP_SSP_ENABLE_BIT) == MP_SSP_ENABLE_BIT)
   #define	MP_HPA_ENABLE			   ((sFTLParam.bParamFlag3 & MP_HPA_ENABLE_BIT) == MP_HPA_ENABLE_BIT)
   #define	PSW_ERROR_ERASE_ALL		((sFTLParam.bParamFlag3 & PSW_ERROR_ERASE_ALL_BIT) == PSW_ERROR_ERASE_ALL_BIT)
   #define	INNOROBUST_ENABLE		   ((sFTLParam.bParamFlag3 & INNOROBUST_ENABLE_BIT) == INNOROBUST_ENABLE_BIT)  
   #define  SPI_BOOT                ((sFTLParam.bParamFlag3 & SPI_BOOT_BIT) == SPI_BOOT_BIT)
   #define  DATALOG_SUPPORT         ((sFTLParam.bParamFlag3 & DATALOG_SUPPORT_BIT) == DATALOG_SUPPORT_BIT)  
   #define  ICELL_ENABLE            ((sFTLParam.bParamFlag3 & ICELL_ENABLE_BIT) == ICELL_ENABLE_BIT)   
   
   // Over drive and ODT setting
   #define OVER_DRV_VENDOR         ((sFTLParam.bOverDrv & 0xF0) >> 4)
   #define OVER_DRV                 (sFTLParam.bOverDrv & 0x0F)
   
   #define ODT_VENDOR              ((sFTLParam.bODT & 0xF0) >> 4)
   #define ODT                      (sFTLParam.bODT & 0x0F)

#endif	// JM_MPTool


//sFTLParam.bSataSpeed
#define SATA_SPEED_I			   (0x00)
#define SATA_SPEED_II			(0x01)
#define SATA_SPEED_III			(0x02)

// Toggle type defined
#define	TOGGLE_ORIGINAL			(1)
#define	TOGGLE_LEGACY			(2)


//FTLParam.bLedLightMode
#define LED_MODE_IDLE_BIT		  (0x03)
#define LED_MODE_READ_BIT 		  (0x0C)
#define LED_MODE_WRITE_BIT	  	  (0x30)

#define LED_MODE_IDLE          	  HDDA_LED_OFF//((sFTLParam.bLedLightMode & LED_MODE_IDLE_BIT))
#define LED_MODE_READ     		     HDDA_LED_BLINK//((sFTLParam.bLedLightMode & LED_MODE_READ_BIT) >> 2)
#define LED_MODE_WRITE     		  HDDA_LED_BLINK//((sFTLParam.bLedLightMode & LED_MODE_WRITE_BIT) >> 4)

/***********************************************************
 *   data structure define
 ***********************************************************/
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

typedef unsigned char bit;
typedef unsigned char bool;
typedef unsigned char bool_T;

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;

typedef char SINT8;
typedef short SINT16;
typedef int SINT32;
typedef long long SINT64;




/***********************************************************
 *   DPD structure define
 ***********************************************************/
typedef struct
{
	byte bDeftectRatio;
	byte abReserved[7];
} _GDP;

typedef struct
{
	byte bReadErrorThreshold;
	byte bECCErrorCopyThreshold;
	byte bWearLevelFrequency;
	byte bSecurityCounter;
	byte abReserved[4];
} _SYS;

typedef struct
{
	word wFlashCode;
	byte bMode;
	byte bMaxChans;
	byte bMaxBanks;
	byte bECCmode;
	byte bIoDrive;
	byte bBlockAttribute;
	byte bReservedRatio;
	byte bFunctionEnable1;
	byte bFunctionEnable2;
	byte bChipCE;
	byte abDummy1[4];
	word awLdrBlockNo[4];
	word wDramSize;
	byte bReservedRatioHigh;
	byte abDummy2[5];

	union
	{
		_GDP GDP;
		_SYS SYS;
	} D;
} _DPD_PARAM;

typedef struct
{
	byte boIntelFlash: 1;
	byte boSamsungFlash: 1;
	byte boToshibaFlash: 1;
	byte bReserved: 5;
} _FTL_BITS;

typedef struct
{
	byte bFlashInterface;
	byte bDramNum;
	byte bParamFlag;
	byte PowerDetectType;
	byte bSataSpeed;
	byte bParamFlag2;
	byte Cylinders_H;
	byte Cylinders_L;
	byte Heads;
	byte Sectors;
	byte bDieOffsetUnit_H;
	byte bDieOffsetUnit_L;
	byte biSlcType;
	byte bParamFlag3;
	byte bThermalSensorID;	
	byte bOverDrv;
	byte bODT;	
	byte bThermalSensorID2;
	byte bThermalSensorID3;
	byte bThermalSensorID4;
	
	byte bReserved[3];
	// fywei 0715 change ab75MhzTMC to reserve byters
	//byte ab75MHzTMC[7];
	byte bFlag; //bit0: Trim, bit1: Thermal Sensor, bit3:Special Mode, bit4:Size Align
	byte abTMC[7];
	_FTL_BITS Bits;
	word wScanBlockUnit[2];
	word wRsvdRate;
	word wFirstSysPageNo;
	word wCEExtendBlock;
	word wDieOffsetUnit;  
	word wLaterTableBlkUnit[2];
	word wBLDelayCount;
	word wEndurance;
#ifdef QUICK_TABLE_FUN
	word wQuickTableBlkUnit;
	word wReserved;
#else
	dword dwReserved;
#endif
	dword dwReserved1[2];
} _FTL_PARAM;



/***********************************************************/
//extern
/***********************************************************/
void sysCPUSysModeEnaIntr(void);
void sysCPUSysModeDisIntr(void);

extern UINT32 sysCPUSaveSR(void);
extern void sysCPURestoreSR(UINT32 sr);


extern void * sysSDRAMAlloc(long size);
extern void sysSDRAMFree(void *pMem);

extern UINT16 SATA_IDENTIFY_DEVICE_WORD0;
extern UINT16 SATA_IDENTIFY_DEVICE_WORDn;
extern UINT16 DCO_IDENTIFY_INFO_WORD0;
extern UINT16 DCO_IDENTIFY_INFO_WORDn;
//Updated in rvctSubMain.c
//TRUE : this program is reloaded (caused by a cold reset)
//FALSE: this program is not reloaded (caused by a warm reset)
extern bool_T CONFIG_PROG_IS_RELOADED;

extern const _DPD_PARAM sParam;
extern const _FTL_PARAM sFTLParam;
extern const byte abBNK[8];
extern byte abBNK_[8];

extern byte boCPUpowerSaving;
//extern byte boClockSlowDnDisable; //removed
//extern void initialize_dramc(void);

extern void vDPD_Init(byte bDumpSel);

extern word 	DIE_BLOCK_UNIT;
extern byte 	FLASH_VENDER;
extern byte 	gbFlashType;
extern word 	IC_BLOCKS;
extern word 	BLOCK_PAGE;
extern byte 	PAGE_SECTOR;
extern byte 	MAX_DIES;
extern byte 	IS_4XNM_MODE;
extern word 	wDistrictRegion;
extern byte 	bDistrictRegionBit;
extern word 	DIE_OFFSET_UNIT;
extern dword	NATIVE_MAX_LBA;
extern byte		TOGGLE_MODE;
extern byte 	ONFI_MODE;
extern byte 	ONE_DRAM;
extern byte		MICRON_SHIFT_RETRY;
extern byte    TSB_SHIFT_RETRY;
//
extern UINT32 SYS_INFO_BASE;

extern byte 	gFlashModeMask1, gFlashModeMask2;

#endif
