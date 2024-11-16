/*Header file*/
#define PIN_LED 2
#define PIN_BUTTON 0
#define LED_ON() digitalWrite(PIN_LED, LOW)
#define LED_OFF() digitalWrite(PIN_LED, HIGH)

#include "bluetooth.h"
#include "smartconfig.h"

extern bool longPress(void);
extern void tick(void);