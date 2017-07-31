#include <IRremote.h>
//433MHz Libraries
#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
//IR Receiver libraries
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
//Declaration of pins
char tmp[2] = {1};
int analogVal;
const int tempPin = A0;


void setup()
{
    pinMode(10, OUTPUT);
    Serial.begin(9600); 
    irrecv.enableIRIn();
    if (!driver.init()) Serial.println("init failed");
}

void loop()
{
   float voltage;
   float temperature;
   int tmp10;
   analogVal = analogRead (tempPin);
   temperature =(((5000.0/1024.0)*analogVal)-500)/10;
   Serial.println(temperature);
   tmp10 = temperature*5;
   Serial.println(tmp10);
   tmp[1] = char (tmp10);
   if (irrecv.decode(&results))
   {
    Serial.println(results.value, HEX);
    switch (results.value)
    {
      case 0x885B30D5:{tmp[0] = 1;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();
      break;}//Channel 1
      case 0xE7E0CFB1:{tmp[0] = 2;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();  
      break;}//Channel 2
      case 0xA34F5A01:{tmp[0] = 3;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();  
      break;}//Channel 3
      case 0xC7E0BECF:{tmp[0] = 10;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();  
      break;}//Menu=Temp
      case 0x28CBA803:{tmp[0] = 11;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();  
      break;}//Mute=Urgent
      case 0xCC00A5B7:{tmp[0] = 12;
      driver.send((uint8_t *)tmp, strlen(tmp));
      driver.waitPacketSent();
      char msg[] = "Lim";
      Serial.println((char*)msg);
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      break;}//AV=Normal text
    }
    irrecv.resume();
   }  
   digitalWrite(10, HIGH); //LED Pin
   delay(500);
}
