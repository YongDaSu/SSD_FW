#ifndef _INTC_H_
#define _INTC_H_

#include <global.h>


#define INTC_NUM_OF_CHANNELS	16	/* number of channels */

/*
 * Function type of an IP's interrupt service routine.
 * A function of this type shall be registered to "INTC"
 * and will be called back while IP's interrupt occur.
 */
typedef void (*IpIsrFunc) (void);

enum IntcIntrPrio
{
//	Intc_FIQ0 = 0,		//FIQ; FIQ's higher priority
//	Intc_FIQ1 = 1,		//FIQ; FIQ's lower priority
	Intc_IRQ0 = 2,		//IRQ; IRQ's highest priority
	Intc_IRQ1 = 3,		//IRQ; IRQ's 2nd highest priority
	Intc_IRQ2 = 4,
	Intc_IRQ3 = 5,
	Intc_IRQ4 = 6,
	Intc_IRQ5 = 7,		//IRQ; IRQ's lowest priority
};

typedef enum IntcIntrPrio IntcIntrPrio;

void IntcIsrFIQ(void);
void IntcIsrIRQ(void);
void IntcInit(void);
UINT8 IntcRegisterISR(UINT8 bChnlNum, IntcIntrPrio nPrio, IpIsrFunc isr);
void IntcUnregisterISR(UINT8 bChnlNum);
void IntcEnableIntr(UINT8 bChnlNum);
void IntcDisableIntr(UINT8 bChnlNum);
void IntcDisableAllIntrs(void);
void IntcClearIntr(UINT8 bChnlNum);
void IntcClearAllIntrs(void);


#endif

