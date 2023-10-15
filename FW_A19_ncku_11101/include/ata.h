#ifndef _ATA_H_
#define _ATA_H_

#ifdef MAKE_LOADER_ONLY
	#include <ata_ldr.h>
#else
	#include <ata_sys.h>
#endif
unsigned int ata_poll_status_2(void);

#endif

