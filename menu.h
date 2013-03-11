/**************************************************************************//**
 * @file     menu.h
 * @brief    Enables changing the state of the robot using a sensor-based input
 * @version: 20130311
 * @author   Lloyd Wallis <lpw503@york.ac.uk>
 * @date:    11 March 2013
 ******************************************************************************/

/**
* This interrupt handler is only enabled when in the "menu" state.
* If a specific sensor combination is detected it will force the robot
* into that state.
* FL Sensor: Follow Line Mode
* FR Sensor: Follow Wall Mode
* BL Sensor: Mouse Tracking Mode
* BR Sensor: Docking Mode
* BL & BR: Short Course Mode
* FL & BL: Long Course Mode
* 
* @author Lloyd Wallis <lpw503@york.ac.uk>
* @todo Make all state methods handle an abort request from abortState
*/
void ADC_IRQHandler();

/**
* Used for an initial menu option, waits for 5 seconds and beeps with ADC
* interrupts enabled. This allows user input for menu mode. Then initialises
* state machine.
*
* @author Lloyd Wallis <lpw503@york.ac.uk>
*/
void waitForInitialInputThenGo();
