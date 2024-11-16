#include "main.h"
#include <Arduino.h>
#include "WiFi.h"

Ticker ticker;

void setup()
{
  Serial.begin(115200);
  // bluetooth_Setup();
  smartConfig_Setup();
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.psk());

  Serial.printf("Connection status: %d\n", WiFi.status());
  if (WiFi.SSID() != "")
  { // Kết nối tới SSID đã lưu trước đó
    WiFi.begin();
    Serial.println("Connecting Wifi...");
    ticker.attach(0.1, tick); // LED chớp nhanh
    int cntimer = millis();
    // Đợi 10s để kết nối
    while (WiFi.status() != WL_CONNECTED && (millis() - cntimer) < 10000)
    {
      delay(500);
    }
    if (WiFi.isConnected())
    {
      strcpy(ssid, WiFi.SSID().c_str());
      strcpy(pass, WiFi.psk().c_str());
      ticker.detach();
      LED_OFF();
      Serial.printf("\nConnection status: %d\n", WiFi.status());
      Serial.println("WiFi Connected.");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      // Nếu kết nối thành công, Khởi tạo kết nối tới Blynk
      // Blynk.begin(auth, ssid, pass);
    }
    else
    {
      // Nếu kết nối không thành công, LED chớp chậm
      Serial.println("Wifi connecting failed!!!");
      ticker.attach(1, tick);
      WiFi.disconnect();
    }
  }
  else
  {
    Serial.println("No wifi configuration.");
    ticker.attach(1, tick);
  }
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