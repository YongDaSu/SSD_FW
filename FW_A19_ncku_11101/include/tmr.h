#ifndef _TMR_H_
#define _TMR_H_

#include <global.h>

// It isn't necessary to remove the double slash mark if we don't use one-shot timer 
//#define	TMR_ONESHOT_ON



typedef void (*TmrIntCB_FT) (void);

enum TmrSoftTimer_E
{
	TmrPeriodicTimer,
	TmrOneShotTimer
};

struct softTimer_S
{
	TmrIntCB_FT	function;
	int		ticks;		/* number of ticks to wait */
	int		curTicks;

	struct softTimer_S *next;
};

extern dword dwTmrSysClock(byte bShowClk);
extern dword dwTmrHWClock(byte bShowClk);

/*
 * start a timer provide periodic ticks
 */
extern void TmrInit(UINT32 dwFreq);


//void TmrRegisterSoftTimer(enum TmrSoftTimer_E, unsigned int nMiniSec, TmrIntCB_FT);
extern void TmrRegisterSoftTimer(enum TmrSoftTimer_E kind, unsigned int nMiniSec, TmrIntCB_FT, struct softTimer_S *p);



/*
 * start a timer to provide a one-shot pulse; the one-shot pulse occurs
 * while the specified time passed; one should call xxx to query whether
 * or not the last "start" has ended
 *
 *   unit of count = 1/10000 second
 */
#ifdef TMR_ONESHOT_ON

bool_T TmrOneShotTimerStart(unsigned int count);

#endif
/*
 * Query whether the one-shot timer suspends or run.
 *
 * Return value :
 *   TRUE  : the one-shot timer suspends
 *   FALSE : the one-shot timer runs
 */
#ifdef TMR_ONESHOT_ON

bool_T TmrIsOneShotTimerSuspended(void);

#endif



#endif

