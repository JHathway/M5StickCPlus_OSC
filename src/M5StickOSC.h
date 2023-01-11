
#include <WiFiUdp.h>
#include <OSCMessage.h> // Adrien Freed
#include <OSCBundle.h>
#include <OSCData.h>

#define PRINT(x) M5.Lcd.print(x);
#define PRINT_LN(x) M5.Lcd.println(x);
#define PRINT_F(x, y) M5.Lcd.printf(x, y);

class SendOSC
{
    WiFiUDP udp;

    const char *udpAddress;
    int udpPort;

public:
    template <typename T>
    void sendOscMessage(const char *address, T message)
    {
        OSCMessage oscPitchMsg(address); // First argument is OSC address
        oscPitchMsg.add((T)message);     // Then append the data
        udp.beginPacket(udpAddress, udpPort);
        oscPitchMsg.send(udp); // send the bytes to the SLIP stream
        udp.endPacket();       // mark the end of the OSC Packet
        oscPitchMsg.empty();   // free space occupied by message
    }

    void sendTo(const char *address, int port)
    {
        udpAddress = address;
        udpPort = port;

        PRINT_LN("Sending to:");
        PRINT_LN("IP: " + String(udpAddress));
        PRINT_F("Port: %i", udpPort);
    }
};

class ReceiveOSC
{
private:

    OSCErrorCode error;
    WiFiUDP Udp;
    static float output;

public:

    void init(int localPort)
    {
        Udp.begin(localPort);
    }

    void getFloat(const char *address)
    {
        OSCMessage msg;
        int size = Udp.parsePacket();

        if (size > 0)
        {
            while (size--)
            {
                msg.fill(Udp.read());
            }
            if (!msg.hasError())
            {
                msg.dispatch(address, led);
            }
            else
            {
                error = msg.getError();
                M5.Lcd.print("error: ");
                M5.Lcd.println(error);
            }
            
        }

        //return output;
    }

    static void led(OSCMessage &msg)
    {
        float messageIn = msg.getFloat(0);

        output = messageIn;

        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.println(messageIn);
    }
};