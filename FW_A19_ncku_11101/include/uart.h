#ifndef _UART_H_
#define _UART_H_

#include <global.h>


#define CONFIG_UART_TX_BUF_SIZE		4096
#define CONFIG_UART_RX_BUF_SIZE		256
#define CONFIG_UART_COMMAND_SIZE	31
#define CONFIG_UART_TX_FIFO_SIZE	16

typedef struct SIO_RX_BUFFER
{
	byte bLen;
	byte abData[CONFIG_UART_COMMAND_SIZE];
} SIO_RX_BUFFER;


extern void UARTinit(void);
extern void process_uart_cmd_channel(UINT8 bFlag, int* write_signal);

#if (!defined(MAKE_LOADER_ONLY))
extern void UARTprintf(const char *fmt, ...);
extern void UARTputs(UINT8 *pbString);
#else
#define UARTprintf(fmt, ...) ((void) 0)
#define UARTputs(fmt)        ((void) 0)
#endif

extern void UARTputchar(UINT8 bHEX);
extern void putHEX(UINT8 bHEX);
extern void put2HEX(UINT16 wHEX);
extern void put4HEX(UINT32 dwHEX);
extern void put8HEX(UINT64 qwHEX);
//extern void UARTputs(UINT8 *pbString);
extern bool_T UARTpollCommandReady(void);
extern struct SIO_RX_BUFFER *UARTgetCommand(void);
//extern UINT32 dwStrToHexval(UINT8 *pStr);
extern void vDBGwhile(UINT8 bFlag);
extern void vDBGwhileRest(UINT8 bFlag);


#endif //_UART_H_

