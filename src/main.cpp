#include "main.h"
#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  // bluetooth_Setup();
  smartConfig_Setup();
}

void loop()
{


  smartConfig_Proc();
}

// put function definitions here:

bool longPress(void) // kiểm tra nhấn nút 3s
{
  static int lastPress = 0;
  if (millis() - lastPress > 3000 && digitalRead(PIN_BUTTON) == 0)
  {
    return true;
  }
  else if (digitalRead(PIN_BUTTON) == 1)
  {
    lastPress = millis();
  }
  return false;
}

void tick(void) // Hàm chuyển trạng thái LED
{
    // toggle state
    int state = digitalRead(PIN_LED); // get the current state of GPIO1 pin
    digitalWrite(PIN_LED, !state);    // set pin to the opposite state
}