#include <M5StickCPlus.h>

#include "M5StickOSC.h"
#include "M5StickWiFi.h"
#include "PrivateVariables.h"

int counter = 0;

ReceiveOSC osc;

void setup()
{
  M5.begin();

  connectToWifi(NETWORK_NAME, NETWORK_PASSWORD);
  M5.Lcd.print(WiFi.localIP());
  
  osc.init(7375);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
}

void loop()
{
  osc.getFloat("/M5Stick");
}