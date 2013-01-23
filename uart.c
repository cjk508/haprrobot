#include "lpc17xx_uart.h"

#define SEND_SIGNATURE 0x81
#define SEND_RAW_SENSOR_VALUES 0x86
#define SEND_TRIMPOT 0xB0
#define SEND_BATTERY_MILLIVOLTS 0xB1
#define DO_PLAY 0xB3
#define PI_CALIBRATE 0xB4
#define DO_CLEAR 0xB7
#define DO_PRINT 0xB8
#define DO_LCD_GOTO_XY 0xB9
#define LINE_SENSORS_RESET_CALIBRATION 0xB5
#define SEND_LINE_POSITION 0xB6
#define AUTO_CALIBRATE 0xBA
#define SET_PID 0xBB
#define STOP_PID 0xBC
#define M1_FORWARD 0xC1
#define M1_BACKWARD 0xC2
#define M2_FORWARD 0xC5
#define M2_BACKWARD 0xC6

/**
 * Abstraction layer for robot commands
 * Takes in hex command, hex data
 * Returns response
 * 
 * @param cmd Hex command to send to robot
 * @param data Data relating to the command (if needed)
 * @return int status - 0 if ok, !0 if fail
 */

int robotCommand(int cmd, int data = 0) {
  uint32_t r = 0;
  switch (cmd) {
    case SEND_SIGNATURE:
      r = serialRecv(SEND_SIGNATURE,
}


/**
 * Read Serial Data
 * 
 * @param rxbuf buffer for received data to be placed into
 * @param len the length of the data (number of chars in string)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t serialRecv(uint8_t* rxbuf, uint32_t len) {
	return(UART_Receive(LPC_UART3, rxbuf, len, BLOCKING));
}


/**
 * Write Serial Data
 * 
 * @param txbuf string of data to write
 * @param len the length of the data (number of chars in string)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t serialSend(uint8_t* txbuf, uint32_t len) {
	return(UART_Send(LPC_UART3, txbuf, len, BLOCKING));
}

// init code for the serial line
void initSerial(void) {
	UART_CFG_Type uartConfig;			// UART Configuration structure variable
	UART_FIFO_CFG_Type uartFifoConfig;	// UART FIFO configuration Struct variable
	PINSEL_CFG_Type PinCfg;				// Pin configuration for UART
	/*
	 * Initialize UART pin connect
	 */
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
	 * - None parity
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
	// Built the basic structures, lets start the devices

// Initialize UART3 peripheral with given to corresponding parameter
	UART_Init(LPC_UART3, &uartConfig);	
// Initialize FIFO for UART3 peripheral
	UART_FIFOConfig(LPC_UART3, &uartFifoConfig);
// Enable UART Transmit
	UART_TxCmd(LPC_UART3, ENABLE);
	
}





