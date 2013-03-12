/**********************************************************************//**
 *	@file uart.h
 *	@brief	UART library for m3pi. Provides basic functions for each serial command that can be sent to the m3pi
 *
 *	@author	Andrew Durant (Initial Coding)
 *	@version: V1.0
 *	@date: 12 March 2013
 */

#ifndef UART_INC
#define UART_INC

#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "lpc17xx.h"


/*! \def SEND_SIGNATURE
 *  \brief M3pi signature command 
*/
/*! \def SEND_RAW_SENSOR_VALUES
 *  \brief M3pi PID raw sensor values command 
*/
/*! \def SEND_CAL_SENSOR_VALUES
 *  \brief M3pi PID calibrated sensor values command 
*/
/*! \def SEND_TRIMPOT
 *  \brief M3pi trimpot value command 
*/
/*! \def SEND_BATTERY_MILLIVOLTS
 *  \brief M3pi battery level command 
*/
/*! \def DO_PLAY
 *  \brief M3pi play() command 
*/
/*! \def PI_CALIBRATE
 *  \brief M3pi PID calibration command 
*/
/*! \def LINE_SENSORS_RESET_CALIBRATION
 *  \brief M3pi PID calibration reset command 
*/
/*! \def SEND_LINE_POSITION
 *  \brief M3pi PID line position command 
*/
/*! \def DO_CLEAR
 *  \brief M3pi clear LCD command  
*/
/*! \def DO_PRINT
 *  \brief M3pi print to LCD command 
*/
/*! \def DO_LCD_GOTO_XY
 *  \brief M3pi LCD postion command 
*/
/*! \def AUTO_CALIBRATE
 *  \brief M3pi PID auto calibration command
*/
/*! \def SET_PID
 *  \brief M3pi PID start command 
*/
/*! \def STOP_PID
 *  \brief M3pi PID stop command 
*/
/*! \def M1_FORWARD
 *  \brief M3pi M1 forwards command 
*/
/*! \def M1_BACKWARD
 *  \brief M3pi M1 backwards command
*/
/*! \def M2_FORWARD
 *  \brief M3pi M2 forwards command
*/
/*! \def M2_BACKWARD
 *  \brief M3pi M2 backwards command
*/

// m3pi hex commands
#define SEND_SIGNATURE 0x81
#define SEND_RAW_SENSOR_VALUES 0x86
#define SEND_CAL_SENSOR_VALUES 0x87
#define SEND_TRIMPOT 0xB0
#define SEND_BATTERY_MILLIVOLTS 0xB1
#define DO_PLAY 0xB3
#define PI_CALIBRATE 0xB4
#define LINE_SENSORS_RESET_CALIBRATION 0xB5
#define SEND_LINE_POSITION 0xB6
#define DO_CLEAR 0xB7
#define DO_PRINT 0xB8
#define DO_LCD_GOTO_XY 0xB9
#define AUTO_CALIBRATE 0xBA
#define SET_PID 0xBB
#define STOP_PID 0xBC
#define M1_FORWARD 0xC1
#define M1_BACKWARD 0xC2
#define M2_FORWARD 0xC5
#define M2_BACKWARD 0xC6

/**
 * Sends the slave name and code version,
 * e.g. “3pi1.0”. 
 * This command also sets motor speeds to 0
 * and stops PID line following, if active,
 * so it is useful as an initialization command.
 *
 * @author Andrew Durant (Initial Coding)
 * @param[out]  buf   address to write to
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdSig(unsigned char *buf);

/**
 * Reads all five IR sensors and sends the
 * raw values as a sequence of two-byte ints,
 * in the range 0-2000
 *
 * @author Andrew Durant (Initial Coding)
 * @param[out] sens array size 5 (10 bytes) this is where is writes the values to
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdRawSens(uint16_t *sens);

/**
 * Reads all five IR sensors and sends
 * calibrated values as a sequence of
 * two-byte ints, in the range 0-1000
 *
 * @author Andrew Durant (Initial Coding)
 * @param[out] sens array size 5 (10 bytes) this is where is writes the values to
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdCalSens(uint16_t *sens);

/*
 * Sends the voltage output of the trimpot
 * as a two-byte int, in the range 0-1023
 *
 * @author Andrew Durant (Initial Coding)
 * @param address to write to @todo not sure at the moment (2)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
//uint32_t cmdTrim();

/*
 * Sends the battery voltage of the 3pi in mV,
 * as a two-byte int
 *
 * @author Andrew Durant (Initial Coding)
 * @param address to write to @todo not sure at the moment (2)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
//uint32_t cmdBat();

/*
 * Plays a tune specified by a string of
 * musical commands. The first data byte
 * specifies the length of the following
 * string (max length 100), so that the
 * slave program knows how many more data
 * bytes to read.
 *
 * @author Andrew Durant (Initial Coding)
 * @param address to write to @todo not sure at the moment (100 + first bit sends length)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
//void cmdPlay(data);

/*
 * Performs one round of calibration
 * on the sensors, reads all five IR
 * sensors, and sends calibrated values
 * as a sequence of two-byte ints, in
 * the range 0-1000. This should be called
 * multiple times, as the robot moves over
 * a range from white to black.
 *
 * @author Andrew Durant (Initial Coding)
 * @param address to write to @todo not sure at the moment (10)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
//uint32_t cmdCal();

/**
 * Resets the calibration.
 * This should always be used when
 * connecting to a slave, in case the
 * master reset without a slave reset,
 * for example in case of a power glitch.
 *
 * @author Andrew Durant (Initial Coding)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdRstCal();

/**
 * Reads all five IR sensors using calibrated
 * values and estimates the position of a
 * black line under the robot. The value,
 * which is sent back as a two-byte integer,
 * is 0 when the line is under sensor PC0 or
 * farther to the left, 1000 when the line is
 * directly under sensor PC1, up to 4000 when
 * it is under sensor PC4 or farther to the right.
 *
 * @author Andrew Durant (Initial Coding)
 * @param address to write to @todo not sure at the moment (2)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdLinePos(uint8_t *linePos);

/**
 * Clears the LCD screen on the 3pi.
 *
 * @author Andrew Durant (Initial Coding)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdLcdClear();

/**
 * Prints 1-8 characters to the LCD.
 * The first byte is the length of the
 * following string of characters,
 * as with the play command above.
 *
 * @author Andrew Durant (Initial Coding)
 * @param[in] buf string of characters (8 + first bit is length)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdLcdPrint(char *buf);

/*
 * Moves the LCD cursor to x-y coordinates
 * given by the next two bytes.
 *
 * @author Andrew Durant (Initial Coding)
 * @param xy coords (2)
 * @return uint32_t status
 */
//uint32_t cmdLcdGoto();

/**
 * Turns the robot left and right while
 * calibrating. For use when the robot
 * it positioned over a line.
 *
 * @author Andrew Durant (Initial Coding)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdAutoCal();

/**
 * Sets up PID parameters and begins
 * line following. The first data byte
 * sets the maximum motor speed.
 * The next four bytes, a, b, c, and d,
 * represent the PID parameters.
 * Specifically, the difference in the motor
 * speeds will be set to (L-2000)×a/b + D×c/d,
 * where L is the position of the line as
 * described above, and D is the derivative of L.
 *
 * @author Andrew Durant (Initial Coding)
 * @param data sets speed and parameters for PID
 * @return uint32_t status
 */
uint32_t cmdPIDstart(uint8_t *data);

/**
 * Stops PID line following, setting motor speeds to 0.
 *
 * @author Andrew Durant (Initial Coding)
 * @return uint32_t status
 */
uint32_t cmdPIDstop();

/**
 * Sets motor M1 turning forward with a speed of
 * 0 (off) up to 127 (full speed).
 *
 * @author Andrew Durant (Initial Coding)
 * @param[in] speed motor speed 0-127
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdLeftMFw(int speed);

/**
 * Sets motor M1 turning backward with a speed of
 * 0 (off) up to 127 (full reverse).
 *
 * @author Andrew Durant (Initial Coding)
 * @param[in] speed motor speed 0-127
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdLeftMBw(int speed);

/**
 * Sets motor M2 turning forward with a speed of
 * 0 (off) up to 127 (full speed).
 *
 * @author Andrew Durant (Initial Coding)
 * @param[in] speed motor speed 0-127
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdRightMFw(int speed);

/**
 * Sets motor M2 turning backward with a speed of
 * 0 (off) up to 127 (full reverse).
 *
 * @author Andrew Durant (Initial Coding)
 * @param[in] speed motor speed 0-127
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t cmdRightMBw(int speed);

/**
 * Tells the robot to play the given series of characters
 * using the onboard speakers.
 * http://www.pololu.com/docs/0J18/3 includes full
 * reference of accepted syntax for this command.
 *
 * @author Lloyd Wallis (Initial Coding)
 * @param[in] seq Speaker playout sequence string
 */
uint32_t cmdDoPlay(char *seq);


/**
 * Read Serial Data
 * 
 * @author Andrew Durant (Initial Coding)
 * @param[out] rxbuf buffer for received data to be placed into
 * @param[in] len the length of the data (number of chars in string)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t serialRecv(uint8_t* rxbuf, uint32_t len);

/**
 * Write Serial Data
 * 
 * @author Andrew Durant (Initial Coding)
 * @param[in] txbuf string of data to write
 * @param[in] len the length of the data (number of chars in string)
 * @return uint32_t status - 0 if ok, !0 if fail
 */
uint32_t serialSend(uint8_t* txbuf, uint32_t len);

/**
 * Initialise Serial link to 3pi
 *  use pins 9 & 10
 *  - Baudrate = 115200bps
 *  - 8 data bit
 *  - 1 Stop bit
 *  - No parity
 *  
 * @author Andrew Durant (Initial Coding)
 */
void initSerial();


#endif
