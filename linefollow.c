#include "motors.h"
#include "uart.h"
#include "linefollow.h"

void useRawSensors(void)
{
  unsigned char *buf[10];
  uint32_t status = cmdRawSens(*buf);
}

void useCalibratedSensors(void)
{
  unsigned char *buf[10];
  uint32_t status = cmdCalSens(*buf);
}
