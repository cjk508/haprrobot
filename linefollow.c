#include "motors.h"
#include "uart.h"
#include "linefollow.h"

void useRawSensors(void)
{
  cmdRawSens();
}

void useCalibratedSensors(void)
{
  cmdCalSens();
}
