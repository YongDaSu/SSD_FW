#include <autocfg.h>

#ifndef AUTO_CONFIG
#define __CMPL_CODE__ "304I"
#endif

#if defined(INTERFACE_SATA)
  #define __FW_VER__ "JMSSD_120713_S"
#else
  #error unknown interface macro definition
#endif

#define __IC_VER__	"667A"
const unsigned int dwICver	= 0x00000662;


#define VER_DATE "" ##__FW_VER__## "," ##__DATE__## "," ##__TIME__## "," ##__IC_VER__## "," ##__CMPL_CODE__## ""
const char VerDate[64] __attribute__((at(0x300))) = VER_DATE; //include'\0'

//Note: VerDate[63] (0x33F) is used for updater. (bit#0: remove ecc over later bad block)
