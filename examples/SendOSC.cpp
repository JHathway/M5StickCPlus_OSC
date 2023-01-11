//=============================================
// SendOSC example
//
// Button A counts up and sends OSC message
// Button B counts down and sends OSC message
// Hold Button A to reset counter
//=============================================

#include <M5StickCPlus.h>

#include "M5StickOSC.h"
#include "M5StickWiFi.h"

//=============================================
// CHANGE THESE VARIABLES
const char *network = "********";
const char *password = "********";

const char *ip = "111.111.111.111";
const unsigned int port = 8000;

//=============================================
// GLOBAL VARIABLES
int counter = 0;

// SendOSC class instance
SendOSC osc;

//=============================================
// SETUP
void setup()
{
  M5.begin();

  // connect to network
  connectToWifi(network, password);
  
  // IP address and port to send to
  osc.sendTo(ip, port);

  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(5);
}

//=============================================
// PRINT OUT DATA
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
  
  // SEND OSC MESSAGE
  osc.sendOscMessage<int>("/count", counter);
}

//=============================================
// LOOP
void loop()
{
  
  //============================================
  // BUTTON B
  if (digitalRead(M5_BUTTON_HOME) == LOW)
  {
    // increment counter, print, send osc
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
        // reset counter, print, send osc
        counter = 0;
        printCountData();
      }
    }
  }

  //============================================
  // BUTTON B
  if (digitalRead(M5_BUTTON_RST) == LOW)
  {
    // decrease counter, print, send osc
    counter--;
    printCountData();

    // pause while button pressed
    while (digitalRead(M5_BUTTON_RST) == LOW) { }
  }
}