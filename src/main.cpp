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
const char *network = "JoesPhone";
const char *password = "12345678";

const char *ip = "10.126.176.199";
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
// LOOP
void loop()
{
  //============================================
  // HOME BUTTON PRESSED 
  // M5_BUTTON_RST for reset button
  if (digitalRead(M5_BUTTON_HOME) == LOW)
  {
    // increment counter, print, send osc
    counter++;

    // clear screen
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(counter);

    // SEND OSC MESSAGE
    osc.sendOscMessage<int>("/count", counter);
    osc.sendOscMessage<>("/count", counter);

    while (digitalRead(M5_BUTTON_HOME) == LOW) {}
  }
}