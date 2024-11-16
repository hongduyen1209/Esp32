#include "BluetoothSerial.h"
// #include "NimBLEDevice.h"
BluetoothSerial BT;

void bluetooth_Setup(void)
{
    BT.begin();
    Serial.println("Bluetooh started! Ready to pair....");
    // NimBLEDevice :: init("ESP32");
    // NimBLEServer *server = NimBLEDevice::createService();
    // NimBLEService *service = server->createService("ABCD");
    // NimBLECharacteristic *ch = service->createCharacteristic("1234");
    // service->start();
    // ch->setValue("Hello BLE");

    // NimBLEAdvertising *ads = NimBLEDevice::getAdvertising();
    // ads->addServiceUUID("ABCD");
    // ads->start();
}

void bluetooth_Proc(void)
{
    if (Serial.available())
    {
        BT.write(Serial.read());
    }
    if (BT.available())
    {
        Serial.write(BT.read()+"\n");
    }
}