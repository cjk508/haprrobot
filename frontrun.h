#ifndef CHRIS_INC
#define CHRIS_INC
/**
 *  When a wall is seen infront of the robot it will run away from the wall
 *  It will turn until it can see the wall on one side, follow it for a while
 *  If after a while it doesn't find open ground then it'll turn and retrace its steps
 *
 * @author Christopher King <cjk508@york.ac.uk>
 */
void runAway(void);
/**
 * Waits for a predefined length of time
 * @author Christopher King <cjk508@york.ac.uk>
 * @return true or false as to whether it has waited for the required length of time or not
 */
void waitForAWhile(void);

#endif
