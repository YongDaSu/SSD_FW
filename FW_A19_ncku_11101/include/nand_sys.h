/****************************************************************************
 ****************************************************************************
 **
 ** MODULE:         $Workfile: nand.h  $
 **
 ** VERSION:        $Revision: 1.28 $
 **
 ** AUTHOR:         CYLiu
 **
 ** DESCRIPTION:    nand header file
 **
 ** LAST MODIFIED BY:
 **
 ****************************************************************************
 *
 *  (c) Copyright 2007, JMicron
 * 
 ****************************************************************************/
#ifndef _NAND_SYS_H_
#define _NAND_SYS_H_

#include "nand.h"

#define NAND_ROW_IN(plane)				(rF0_FMROWP) = (plane)

extern NAND_ADDR sLastNand;
extern dword gFDMABufSel[8];

/* Extern functions */
extern UINT8 boNAND_Init(int hostif);
extern byte bNAND_WaitReady(void);
extern void vNAND_WaitReady(void);
extern void vNAND_WaitDMAdone(void);
extern dword vNAND_GetRowAddress(byte bPageNo, word wBlkNo);

extern byte bNAND_WaitReady(void);
extern void vTwoPlaneBlockErase(void);

extern void vNAND_GetAddress2(UINT8 bPageNo, UINT16 wBlkNo);
#endif  // _NAND_SYS_H_
