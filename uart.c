#include "uart.h"


uint8_t sig;
uint32_t ret;

uint32_t cmdSig() {
  sig = SEND_SIGNATURE;
  ret = serialSend(&sig,1);
  ret = serialRecv(&buf,6);
  return ret;
}


uint32_t cmdLeftMFw(int speed) {
  sig = M1_FORWARD;
  ret = serialSend(&sig,1);
  
  return ret;
}

uint32_t cmdLeftMBw(int speed) {
  sig = M1_BACKWARD;
  ret = serialSend(&sig,1);
  
  return ret;
}

uint32_t cmdRightMFw(int speed) {
  sig = M2_FORWARD;
  ret = serialSend(&sig,1);
  
  return ret;
}

uint32_t cmdRightMBw(int speed) {
  sig = M2_BACKWARD;
  ret = serialSend(&sig,1);
  
  return ret;
}


uint32_t serialRecv(uint8_t* rxbuf, uint32_t len) {
	return(UART_Receive(LPC_UART3, rxbuf, len, BLOCKING));
}

uint32_t serialSend(uint8_t* txbuf, uint32_t len) {
	return(UART_Send(LPC_UART3, txbuf, len, BLOCKING));
}

void initSerial() {
// UART Configuration structure variable
	UART_CFG_Type uartConfig;
// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type uartFifoConfig;
// Pin configuration for UART
	PINSEL_CFG_Type PinCfg;

// Initialize UART pin connect
	PinCfg.Funcnum = PINSEL_FUNC_2;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum = PINSEL_PORT_0;
	PinCfg.Pinnum = 0; //Out pin 9
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1; //Out pin 10
	PINSEL_ConfigPin(&PinCfg);
	
	/* Initialize UART Configuration parameter structure:
	 * - Baudrate = 115200bps
	 * - 8 data bit
	 * - 1 Stop bit
	 * - No parity
	 */
	UART_ConfigStructInit(&uartConfig);
	  uartConfig.Parity = UART_PARITY_NONE;
    uartConfig.Databits = UART_DATABIT_8;
    uartConfig.Stopbits = UART_STOPBIT_1;
    uartConfig.Baud_rate = 115200;
	
	/* Initialize FIFOConfigStruct to default state:
	 * - FIFO_DMAMode = DISABLE
	 * - FIFO_Level = UART_FIFO_TRGLEV0
	 * - FIFO_ResetRxBuf = ENABLE
	 * - FIFO_ResetTxBuf = ENABLE
	 * - FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&uartFifoConfig);

// Initialize UART3
	UART_Init(LPC_UART3, &uartConfig);	
// Initialize FIFO for UART3
	UART_FIFOConfig(LPC_UART3, &uartFifoConfig);
// Enable UART Transmit
	UART_TxCmd(LPC_UART3, ENABLE);
}





