#include "uart.h"
#include "debug_frmwrk.h"

// DBG Levels
// 1 - Basic
// 2 - Verbose
#define DBG_LEVEL 1

uint8_t sig;
uint32_t ret;

uint32_t cmdSig(unsigned char *buf) {
  sig = SEND_SIGNATURE;
  ret = serialSend(&sig,1);
  ret = serialRecv(buf,6);
  return ret;
}


uint32_t cmdLeftMFw(int speed) {
  uint8_t data = (speed > 127) ? 127 : speed;
  sig = M1_FORWARD;
  ret = serialSend(&sig,1);
  ret = serialSend(&data,1);
  return ret;
}

uint32_t cmdLeftMBw(int speed) {
  uint8_t data = (speed > 127) ? 127 : speed;
  sig = M1_BACKWARD;
  ret = serialSend(&sig,1);
  ret = serialSend(&data,1);
  return ret;
}

uint32_t cmdRightMFw(int speed) {
  uint8_t data = (speed > 127) ? 127 : speed;
  sig = M2_FORWARD;
  ret = serialSend(&sig,1);
  ret = serialSend(&data,1);
  return ret;
}

uint32_t cmdRightMBw(int speed) {
  uint8_t data = (speed > 127) ? 127 : speed;
  sig = M2_BACKWARD;
  ret = serialSend(&sig,1);
  ret = serialSend(&data,1);
  return ret;
}


uint32_t serialRecv(uint8_t* rxbuf, uint32_t len) {
	return(UART_Receive(LPC_UART3, rxbuf, len, BLOCKING));
}

uint32_t serialSend(uint8_t* txbuf, uint32_t len) {
	return(UART_Send(LPC_UART3, txbuf, len, BLOCKING));
}

void initSerial() {

  if (DBG_LEVEL >= 2) _DBG_("Starting Serial Init");
  
// UART Configuration structure variable
	UART_CFG_Type uartConfig;
// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type uartFifoConfig;
// Pin configuration for UART
	PINSEL_CFG_Type PinCfg;

  if (DBG_LEVEL >= 2) _DBG_("Structs assigned");
  
// Initialize UART pin connect
	PinCfg.Funcnum = PINSEL_FUNC_2;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum = PINSEL_PORT_0;
	PinCfg.Pinnum = 0; //Out pin 9
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1; //Out pin 10
	PINSEL_ConfigPin(&PinCfg);
	
	if (DBG_LEVEL >= 2) _DBG_("Pins Configured");
	
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
	
	if (DBG_LEVEL >= 2) _DBG_("UART Configured");
	
	/* Initialize FIFOConfigStruct to default state:
	 * - FIFO_DMAMode = DISABLE
	 * - FIFO_Level = UART_FIFO_TRGLEV0
	 * - FIFO_ResetRxBuf = ENABLE
	 * - FIFO_ResetTxBuf = ENABLE
	 * - FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&uartFifoConfig);
  
  if (DBG_LEVEL >= 2) _DBG_("FIFO Configured");
  
// Initialize UART3
	UART_Init(LPC_UART3, &uartConfig);
	
	if (DBG_LEVEL >= 2) _DBG_("UART Initialised");
	
// Initialize FIFO for UART3
	UART_FIFOConfig(LPC_UART3, &uartFifoConfig);
	
	if (DBG_LEVEL >= 2) _DBG_("FIFO Initialised");
	
// Enable UART Transmit
	UART_TxCmd(LPC_UART3, ENABLE);
	
	if (DBG_LEVEL >= 2) _DBG_("UART Started");
}





