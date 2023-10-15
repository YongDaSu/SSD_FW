#ifndef _ATAI_H_
#define _ATAI_H_


struct ata_IO_CMD_info	//compatable to ata_io_cmd_info
{
	UINT32		nSSect;		/* start sector */
	UINT32		nSectCnt;	/* sector count */
	bool_T		isRead;		/* TRUE : indicating read command;
					 * otherwise : indicating write command */
	bool_T		isFPDMA;

	UINT32		nSectCntTx;	/* number of sectors transmitted */
	bool_T		boECCfailDetected;
};

typedef struct ATA_context
{
	shadow_reg_blk	*srb;		/* update this data structure in task
					 * task context only
					 */
	struct vendor1
	{
		bool_T		enable;	/* enable vendor1 PIO command (or say PIO vendor command)
					 * defined by JMicron
					 */
		UINT8		sectNumVal;
					/* Dynamically concatenate this value with 0x12 and 0x34
					 * to form a vendor1 PIO command. (e.g. 0x1234FF, 0x1234XX)
					 * This value is initialized as 0xFF.
					 */
	} vendor1;
	
	struct ata_IO_CMD_info io_CMD_info;
					/* io_CMD_info is only valid while Command
					 * is a READ/WRITE command (DMA IO, non-DMA IO, vendor IO).
					 *
					 * This field is used to store the original IO cmd information. (from host)
					 * One IO cmd might be divided into several iterations.
					 * Transfer size in each iteration will be less than or equal to 256 sectors.
					 */
					 
	struct ata_io_cmd_info io_cmd_info;
					/* io_cmd_info is only valid while Command
					 * is a READ/WRITE command (DMA IO, non-DMA IO, vendor IO).
					 *
					 * This field is used to store the IO cmd information per iteration. (to main_loop)
					 */

#ifdef ATA_FEATURE_NCQ
	sata_ncq	*read_ncq;	/* accumulated read NCQ commands */
	sata_ncq	*write_ncq;	/* accumulated write NCQ commands */
	sata_ncq	*exec_ncq;	/* the NCQ command being processed */
	bool_T		ncq_intermix_err;
#endif

	struct ata_v2_cmd_info v2_cmd_info;
					/* v2_cmd_info is only valid while Command
					 * is a vendor2 commands extended by JMicron.
					 */
	unsigned int	ata_sts;	/* ATA status; combined with
					 * ATA_STS_XXX constants
					 */

	unsigned int	ata_dmaio_cmd_sts;
					/* extra ATA status while executing
					 * DMA commands combined with ATA_DMAIO_CMD_STS_XXX
					 */
	void (*ata_standby_fun) (void);
	
	UINT8 sata_speed;
	
} _ATA_CTX;

extern _ATA_CTX ataCtx_gi;

extern ata_sys_access_FT		ataSysAccessCB_gi;
extern UINT32 *pSysPRDAddr;
extern UINT8 *pSysBuf;
extern UINT32 *pSysAllPRDAddr;
extern UINT8 *pSysAllBuf;

extern bool_T boDIPMenable;

extern UINT32 dwSYStimestamp;
extern UINT8 bSYStimeCnt;
extern UINT8 bSYStimeSec;
extern UINT8 bSYStimeMin;
extern UINT8 bPowerDownCount_CPU;
extern UINT16 wSMARToffLinePending;
extern UINT16 wSMARToffLineCount;
extern UINT32 dwSMARTselfTestCount;

#define DEF_HEADS_NUMBER						16
#define DEF_SECTS_PER_TRACK					63
#define MAX_SECTOR_ON_MULTI_PIO			16
//#define MAX_SECTOR_ON_MULTI_PIO				1//Jasper: for ULINK test

#define MAX_NCQ_QUEUE_DEPTH					32
#define NCQ_WRITE_QUEUE_POLL_INTERVAL			100//100 ms

//LBA_OFFSET_VALUE must be the same as include\usb.h
#define LBA_OFFSET_VALUE						0

#endif

