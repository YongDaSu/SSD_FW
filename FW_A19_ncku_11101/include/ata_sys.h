#ifndef _ATA_SYS_H_
#define _ATA_SYS_H_


#include <sata.h>
//
//
// Normal ATA commands are classified into the followings classes by this program:
//	DMAIO commands (normal, FPDMA),	->	ata_io_cmd_info
//	PIO commands,			->	ata_io_cmd_info
//	NonIO commands
//
//
// V1 commands are classified into the following classes by this program:
//	V1PIO commands			-->	ata_io_cmd_info
//
//
// V2 commands are classified into the following classes by the upper layer program:
//	V2DMAIO commands,		->	ata_v2_cmd_info
//	V2PIO commands,			->	ata_v2_cmd_info
//	V2NonIO commands,		->	ata_v2_cmd_info
//
//

//------------------------------------------------------------------------
//		ATA command code
//------------------------------------------------------------------------
#define ATA_CMD_DATA_SET_MANAGEMENT						0x06
#define ATA_CMD_DEVICE_CONFIGURATION_OVERLAY			0xB1
#define ATA_CMD_DOWNLOAD_MICROCODE						0x92
#define ATA_CMD_EXECUTE_DEVICE_DIAGNOSTIC				0x90
#define ATA_CMD_FLUSH_CACHE								0xE7
#define ATA_CMD_FLUSH_CACHE_EXT							0xEA
#define ATA_CMD_IDENTIFY_DEVICE							0xEC
#define ATA_CMD_INITIALIZE_DEVICE_PARAMETERS			0x91
#define ATA_CMD_NOP										   0x00
#define ATA_CMD_READ_BUFFER								0xE4
#define ATA_CMD_READ_DMA								   0xC8
#define ATA_CMD_READ_DMA_WO_RETRY						0xC9
#define ATA_CMD_READ_DMA_EXT							   0x25
#define ATA_CMD_READ_FPDMA_QUEUED						0x60
#define ATA_CMD_READ_LOG_EXT							   0x2F
#define ATA_CMD_READ_LOG_DMA_EXT						   0x47
#define ATA_CMD_READ_MULTIPLE							   0xC4
#define ATA_CMD_READ_MULTIPLE_EXT						0x29
#define ATA_CMD_READ_NATIVE_MAX_ADDRESS				0xF8
#define ATA_CMD_READ_NATIVE_MAX_ADDRESS_EXT			0x27
#define ATA_CMD_READ_SECTOR								0x20
#define ATA_CMD_READ_SECTOR_WO_RETRY					0x21
#define ATA_CMD_READ_SECTOR_EXT							0x24
#define ATA_CMD_READ_SECTOR_AND_VERIFY					0x40
#define ATA_CMD_READ_SECTOR_AND_VERIFY_WO_RETRY		0x41
#define ATA_CMD_READ_SECTOR_AND_VERIFY_EXT			0x42
#define ATA_CMD_RECALIBRATE								0x10
#define ATA_CMD_SEEK									      0x70//0x70~0x7F
#define ATA_CMD_SET_FEATURE								0xEF
#define ATA_CMD_SET_MAX_ADDRESS							0xF9
#define ATA_CMD_SET_MAX_ADDRESS_EXT						0x37
#define ATA_CMD_SET_MULTIPLE_MODE						0xC6
#define ATA_CMD_WRITE_BUFFER							   0xE8
#define ATA_CMD_WRITE_DMA								   0xCA
#define ATA_CMD_WRITE_DMA_WO_RETRY						0xCB
#define ATA_CMD_WRITE_DMA_EXT							   0x35
#define ATA_CMD_WRITE_DMA_FUA_EXT						0x3D
#define ATA_CMD_WRITE_FPDMA_QUEUED						0x61
#define ATA_CMD_WRITE_LOG_EXT							   0x3F
#define ATA_CMD_WRITE_LOG_DMA_EXT						0x57
#define ATA_CMD_WRITE_MULTIPLE							0xC5
#define ATA_CMD_WRITE_MULTIPLE_EXT						0x39
#define ATA_CMD_WRITE_MULTIPLE_FUA_EXT					0xCE
#define ATA_CMD_WRITE_SECTOR							   0x30
#define ATA_CMD_WRITE_SECTOR_WO_RETRY					0x31
#define ATA_CMD_WRITE_SECTOR_EXT						   0x34
#define ATA_CMD_WRITE_VERIFY							   0x3C
#define ATA_CMD_WRITE_UNCORRECTABLE_EXT				0x45
#define ATA_CMD_IDENTIFY_PACKET_DEVICE					0xA1
//------------------------------------------------------------------------
//  DCO subcommand set
//------------------------------------------------------------------------
#define ATA_CMD_DCO_RESTORE								0xC0
#define ATA_CMD_DCO_FREEZE_LOCK							0xC1
#define ATA_CMD_DCO_IDENTIFY							0xC2
#define ATA_CMD_DCO_SET									0xC3
//------------------------------------------------------------------------
//  HPA subcommand set
//------------------------------------------------------------------------
#define ATA_CMD_HPA_SET_MAX								0x00
#define ATA_CMD_HPA_SET_PASSWORD						0x01
#define ATA_CMD_HPA_LOCK								0x02
#define ATA_CMD_HPA_UNLOCK								0x03
#define ATA_CMD_HPA_FREEZE_LOCK							0x04
//------------------------------------------------------------------------
//  Security command set
//------------------------------------------------------------------------
#define ATA_CMD_SECURITY_CLEAR_FREEZE_LOCK         0xFA
#define ATA_CMD_SECURITY_DISABLE_PASSWORD				0xF6
#define ATA_CMD_SECURITY_ERASE_PREPARE					0xF3
#define ATA_CMD_SECURITY_ERASE_UNIT						0xF4
#define ATA_CMD_SECURITY_FREEZE_LOCK					0xF5
#define ATA_CMD_SECURITY_SET_PASSWORD					0xF1
#define ATA_CMD_SECURITY_UNLOCK							0xF2
//------------------------------------------------------------------------
//  Power management command set
//------------------------------------------------------------------------
#define ATA_CMD_STANDBY_IMMEDIATE						0xE0
#define ATA_CMD_IDLE_IMMEDIATE							0xE1
#define ATA_CMD_STANDBY									0xE2
#define ATA_CMD_IDLE									0xE3
#define ATA_CMD_CHECK_POWER_MODE						0xE5
#define ATA_CMD_SLEEP									0xE6
//------------------------------------------------------------------------
//  Write Protect & Power Saving command set
//------------------------------------------------------------------------
#define INNODISK_WRITE_PROTECT                          0x84
#define INNODISK_POWER_SAVING                           0x85

//------------------------------------------------------------------------
//  S.M.A.R.T. command
//  S.M.A.R.T. subcommands define
//------------------------------------------------------------------------
#define ATA_CMD_SMART									0xB0
#define SMART_READ_DATA									0xD0
#define SMART_READ_ATTR_THRESHOLDS						0xD1
#define SMART_EN_DISABLE_ATTR_AUTOSAVE					0xD2
#define SMART_SAVE_ATTR_VALUES							0xD3
#define SMART_EXECUTE_OFF_LINE_IMMEDIATE				0xD4
#define SMART_READ_LOG									0xD5
#define SMART_WRITE_LOG									0xD6
#define SMART_ENABLE_OPERATIONS							0xD8
#define SMART_DISABLE_OPERATIONS						0xD9
#define SMART_RETURN_STATUS								0xDA
#define SMART_EN_DISABLE_AUTO_OFF_LINE					0xDB
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//  ATA Vender command code
//------------------------------------------------------------------------
#define VENDOR_CMD_DMA_READ								0x86
#define VENDOR_CMD_DMA_WRITE							   0x88
#define VENDOR_CMD_PIO_READ								0x8A
#define VENDOR_CMD_PIO_WRITE							   0x8F

#define ATA_STS_NONE				                     0x0000
#define ATA_STS_REQ_EXEC_DMAIO_CMD	               0x0001		// request to execute a DMA IO command
#define ATA_STS_REQ_EXEC_PIO_CMD	                  0x0002		// request to execute a PIO command
#define ATA_STS_REQ_EXEC_V1PIO_CMD	               0x0004		// request to execute a vendor1 PIO command
#define ATA_STS_REQ_EXEC_NONIO_CMD	               0x0008		// request to execute a non IO command

#define ATA_STS_REQ_EXEC_V2_CMD		               0x0010		// request to execute a vendor2 command

#define ATA_STS_REQ_EXEC_NCQRD_CMD	               0x0020
#define ATA_STS_REQ_EXEC_NCQWR_CMD	               0x0040

#define ATA_STS_EXECING_DMA_CMD		               0x0100		// is executing DMA command now

#define MAX_CODE_SIZE					               163840		// max. 160K program code
#define MIN_NUM_PER_SEND					            512								// min. number size per DOWNLOAD MICROCODE command(mode 3)
#define MAX_NUM_PER_SEND					            MAX_CODE_SIZE			// max. number size per DOWNLOAD MICROCODE command(mode 3)
/*	0x80000000 : reserved for ata internal use */


typedef bool_T		(*ata_is_system_busy_FT)(void);
typedef void 		(*ata_flush_cache_FT)	(void);
typedef void		(*ata_idle_FT)		(void);
typedef void		(*ata_standby_FT)	(void);
typedef void		(*ata_sleep_FT)		(void);
//typedef void		(*ata_sys_access_FT)(bool_T, UINT32, UINT16, UINT32*);
typedef void		(*ata_sys_access_FT)(bool_T, UINT8*);
typedef byte		(*ata_check_ecc_FT)(UINT32, UINT16, bool_T);
typedef byte		(*ata_update_ecc_FT)(UINT32, UINT16, bool_T);
typedef bool_T		(*ata_save_dram_FT)		(void);
typedef bool_T		(*ata_load_dram_FT)		(void);

struct ata_stuff
{
	unsigned int			storageSizeSectors;
	UINT16					IO_ITER_SIZE;
	
	UINT16					*pIdentifyDevTbl;
	UINT16					nIdentifyDevTblSize;	/* count in byte */
	
	UINT16					*pDCOidentifyInfo;
	UINT16					nDCOidentifyInfoSize;	/* count in byte */
	
	ata_flush_cache_FT		flushCacheCB;

	ata_idle_FT				idleCB;			/* callback for system-level control */
	ata_standby_FT			standbyCB;		/* callback for system-level control */
	ata_sleep_FT			sleepCB;		/* callback for system-level control */
	
	ata_sys_access_FT		SysAccessCB;
	
	ata_check_ecc_FT		CheckEccCB;
	ata_update_ecc_FT		UpdateEccCB;

	ata_save_dram_FT		SaveDramCB;
	ata_load_dram_FT		LoadDramCB;
};

struct ata_io_cmd_info
{
	UINT32		nSSect;		/* start sector */
	UINT32		nSectCnt;	/* sector count */
	bool_T		isRead;		/* TRUE : indicating read command;
					 * otherwise : indicating write command */
	bool_T		isFPDMA;
};

struct ata_v2_cmd_info
{
	UINT8		Command;
	UINT8		Features;
	UINT8		SectorCnt;
	UINT8		SectorNum;
	UINT8		CylinderLow;
	UINT8		CylinderHigh;
};

struct ata_download_cmd_info
{
	UINT16 wNxtOffset;
	UINT16 wMicroCodeSize;
	UINT8 *pBuf_alloc;
	UINT8 *pBuf;
};


void ata_init(struct ata_stuff *);

void ata_host_reset(void);
void ata_soft_reset(void);
void ata_bist_handle(void);
void ata_phy_event_handle(byte bType);
bool_T ata_power_mode_check(void);
void cpu_power_saving_mode(byte bSaveWithDRAM);

unsigned int ata_poll_status(void);

void ncq_command_acceptance(void);
void ncq_free_ds(sata_ncq *q, bool_T boClearTag);
void ncq_clr_tag(UINT8 tag);

#define NCQ_READ_REGULAR	0x01
#define NCQ_READ_LEAVE		0x02

struct ata_io_cmd_info * ata_get_vendor_io_cmd_info(void);
	// Call this function while needs to execute a V1PIO.
	
struct ata_v2_cmd_info * ata_get_v2_cmd_info(void);
	// Call this function while needs to execute a vendor2 command.
	// Callers to this function analysis/parse 'struct ata_v2_cmd_info'
	// and determine to call one of the following functions:
	//   1. ata_invalid_v2_cmd()
	//   2. ata_start_v2dmaio_cmd() and ata_poll_v2dmaio_cmd_status()
	//   3. ata_exec_v2pio_cmd()
	//   4. execute nonio itself and call ata_v2nonio_cmd_result()

void ata_invalid_v2_cmd(void);
	// Call this function to terminate a vendor2 command without
	// executing it because of encountering an invalid vendor2 command.




//                                          //
//          DMA IO command functions        //
//       V2 DMA IO command functions        //
//                                          //
void ata_start_dmaio_cmd(unsigned int nPRDTblAddr, bool_T boECCrecordHit);	/* without blocking */
bool_T ata_start_v2dmaio_cmd(unsigned int nPRDTblAddr, bool_T isRead);	/* without blocking */

#define ATA_DMAIO_CMD_STS_DONE		0x0200
#define ATA_DMAIO_CMD_STS_EXECING	0x0400
unsigned int ata_poll_dmaio_cmd_status(bool_T boECCfailDetected);		/* to query command status since not blocking */
unsigned int ata_poll_v2dmaio_cmd_status(void);



//                                          //
//      peripheral IO command function      //
//       VENDOR1 PIO command function       //
//       VENDOR2 PIO command function       //
//                                          //
bool_T ata_check_pio_read_ecc(void);
bool_T ata_exec_pio_cmd(unsigned int nPRDTblAddr, void *);	/* blocking */

bool_T ata_exec_v1pio_cmd(unsigned int nPRDTblAddr);		/* blocking */
UINT8  ata_get_v1pio_cmd(void);
void   ata_set_v1pio_cmd(UINT8 v);
	/* Concatenate 0x12, 0x34, and "vendorio_cmd" to form a real
	 * vendor1 PIO command identifier recognized by the ATA program.
	 */

bool_T ata_exec_v2pio_cmd(unsigned int nPRDTblAddr, bool_T isRead);	/* blocking */





//                                          //
//          NON IO command function         //
//     VENDOR2 NON IO command function      //
//                                          //
bool_T ata_exec_nonio_cmd(void);				/* blocking */

void ata_v2nonio_cmd_result(UINT8 result);			/* blocking */
	/* Report execution result to the host only. */
	/* All the jobs of v2nonio commands are done by the caller. */
void vDataLogging(bool_T isRead, dword nSSect, dword nSectCnt);
void vClearDataLoggingRecord(void);
#endif

