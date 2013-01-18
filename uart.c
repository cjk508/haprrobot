#include "lpc17xx_uart.h"

/**
 * Abstraction layer for robot commands
 * Takes in hex command, hex data
 * Returns response
 * 
 * @param *buf buffer for received data to be placed into
 * @param length the length of the data (number of chars in string)
 * @return int status - 0 if ok, !0 if fail
 */
robotCommand() {
	
}


/**
 * Read Serial Data
 * 
 * @param *buf buffer for received data to be placed into
 * @param length the length of the data (number of chars in string)
 * @return int status - 0 if ok, !0 if fail
 */
int read_usb_serial_none_blocking(char *buf,int length) {
	return(UART_Receive((LPC_UART_TypeDef *)LPC_UART3, (uint8_t *)buf, length, NONE_BLOCKING));
}


/**
 * Write Serial Data
 * 
 * @param *buf string of data to write
 * @param length the length of the data (number of chars in string)
 * @return int status - 0 if ok, !0 if fail
 */
int write_usb_serial_blocking(char *buf,int length) {
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART3,(uint8_t *)buf,length, BLOCKING));
}

// init code for the serial line
void serial_init(void) {
	UART_CFG_Type UARTConfigStruct;			// UART Configuration structure variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;	// UART FIFO configuration Struct variable
	PINSEL_CFG_Type PinCfg;				// Pin configuration for UART
	/*
	 * Initialize UART pin connect
	 */
	PinCfg.Funcnum = PINSEL_FUNC_2;
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Portnum = PINSEL_PORT_0;
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 10;
	PINSEL_ConfigPin(&PinCfg);
	
	/* Initialize UART Configuration parameter structure to default state:
	 * - Baudrate = 9600bps
	 * - 8 data bit
	 * - 1 Stop bit
	 * - None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	/* Initialize FIFOConfigStruct to default state:
	 * - FIFO_DMAMode = DISABLE
	 * - FIFO_Level = UART_FIFO_TRGLEV0
	 * - FIFO_ResetRxBuf = ENABLE
	 * - FIFO_ResetTxBuf = ENABLE
	 * - FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	// Built the basic structures, lets start the devices/
	// USB serial
	UART_Init((LPC_UART_TypeDef *)LPC_UART3, &UARTConfigStruct);		// Initialize UART3 peripheral with given to corresponding parameter
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART3, &UARTFIFOConfigStruct);	// Initialize FIFO for UART3 peripheral
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART3, ENABLE);			// Enable UART Transmit
	
}
