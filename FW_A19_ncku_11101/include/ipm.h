
#ifndef _IPM_H_
#define _IPM_H_

#include <sata.h>

#define IPM_TIME_UNIT			1	// run in 2.5ms 

//DIPM
#define DIPM_PARTIAL_TIME		5	// (4*2.5 = 10 ms) unit dependent on IPM_TIME_UNIT
#define DIPM_SLUMBER_TIME		21//36	// (36*2.5 = 90 ms) unit dependent on IPM_TIME_UNIT

extern UINT8 bCountDownDIPM;


extern void ipmTimerCB(void);
extern void vSetPowerMode(UINT8 bMode);
extern byte sata_wakeup_interface(void);
extern void vCheckDIPM(void);

#endif  //_IPM_H_
