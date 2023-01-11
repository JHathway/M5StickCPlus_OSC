//=============================================================
// File:    M5StickCPlus_WiFi.h
// 
// Author:  J. Hathway
//
// Description:
//     - Function for connecting M5StickC Plus to WiFI Network.
//     - Requires nextwork name and password.
//     - Prints out message on LCD when successful/failed.
// 
// Dependencies:
//     - M5StickCPlus (M5Stack)
//     - WiFi.h (Arduino)
//=============================================================

#include <WiFi.h>

#define PRINT(x) M5.Lcd.print(x)
#define PRINT_LN(x) M5.Lcd.println(x)

/// Function for connecting M5 board to WiFi
/// @param myNetwork (const char*) name of network
/// @param myPassword (const char*) network password
/// @param timeout (int) optional - time spent attempting to access network
void connectToWifi(const char* myNetwork, const char* myPassword, int timeout = 20000) {
  
  PRINT("Connecting");

  // initialise - WIFI_STA = Station Mode, WIFI_AP = Access Point Mode 
  WiFi.mode(WIFI_STA);
  WiFi.begin(myNetwork, myPassword);

  // start timer
  unsigned long startAttemptTime = millis();

  // while not connected to WiFi AND before timeout
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    PRINT(".");
    delay(400);
  }

  // if failed, print LCD message
  if (WiFi.status() != WL_CONNECTED) {
    PRINT_LN("\nFailed!");
  }
  // if successful, print LCD message
  else {
    PRINT_LN("\nConnected to:");
    PRINT_LN(myNetwork);
    delay(2000);
  }
}
