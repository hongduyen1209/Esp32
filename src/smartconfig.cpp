#include "smartconfig.h"
#include "main.h"
#include <WiFi.h>

static void startSmartConfig(void);
static void exitSmartConfig(void);



static bool smartConfigFlag = false; // flag trạng thái smart config

void smartConfig_Setup(void)
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
}

void smartConfig_Proc(void)
{
    if (longPress())
    {
        startSmartConfig();        
    }
    // Thoát chế độ Smart Config sau khi kết nối tới Wifi
    if (WiFi.status() == WL_CONNECTED && smartConfigFlag && WiFi.smartConfigDone())
    {
        exitSmartConfig();
        WiFi.hostname("esp32");
        WiFi.setAutoReconnect(true);
        // Serial.printf("Connection status: %d\n", WiFi.status());
        Serial.println("WiFi Connected.");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        LED_OFF();
        // Blynk.begin(auth,ssid,pass);        // Khởi tạo kết nối tới Blynk bằng token xác thực và thông tin Wifi
    }
    else if (WiFi.status() != WL_CONNECTED && !smartConfigFlag)
    {
        if (!ticker.active())
        {
            ticker.attach(1, tick);
        }
    }
}


static void startSmartConfig(void) // bật chế độ smart config
{
    if (smartConfigFlag == false)
    {
        Serial.println("Start SmartConfig.");
        smartConfigFlag = true;
        ticker.attach(0.3, tick); // LED chớp nhanh
        WiFi.beginSmartConfig();
    }
}

static void exitSmartConfig(void) // thoát chế độ smart config
{
    ticker.detach();
    LED_OFF();
    smartConfigFlag = false;
}
