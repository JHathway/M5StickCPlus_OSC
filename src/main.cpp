#include <M5StickCPlus.h>

#include "M5StickOSC.h"
#include "M5StickWiFi.h"
#include "PrivateVariables.h"

int counter = 0;

SendOSC osc;

void setup()
{
  M5.begin();

  M5.Lcd.setRotation(1);

  connectToWifi(NETWORK_NAME, NETWORK_PASSWORD);
  osc.sendTo("10.126.18.105", 7374);
}

void printCountData()
{
  // clear screen
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 0);

  // print count
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("Count is ");

  M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print(counter);

  osc.sendOscMessage<int>("/count", counter);
}





void loop()
{
  if (digitalRead(M5_BUTTON_HOME) == LOW)
  {
    // increment counter, print
    counter++;
    printCountData();

    int time = 0;

    //============================================
    // HOLD BUTTON A
    while (digitalRead(M5_BUTTON_HOME) == LOW)
    {
      // start timer in ms
      time++;
      delay(1);

      // if held for 2 secs
      if (time == 2000)
      {
        // reset counter, print
        counter = 0;
        printCountData();
      }
    }
  }

  //============================================
  // BUTTON B
  if (digitalRead(M5_BUTTON_RST) == LOW)
  {
    // decrease counter, print
    counter--;
    printCountData();

    // pause while button pressed
    while (digitalRead(M5_BUTTON_RST) == LOW)
    {
    }
  }
}