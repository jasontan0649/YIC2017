#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver(2000,2,12,8,false);//constructor to change any default setting/pins
#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
const int Tone =7;
float temp;
float tmpswitch;


void setup()
{
  pinMode(3, OUTPUT);
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
  lcd.begin(16,2);
}

void loop()
{
   digitalWrite(3, HIGH);
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
       Serial.println(buf[0]);
        tone (Tone,659,250);
        delay(250);
        tone (Tone,440,250);
        delay(250);
    }
    int Data =(buf[0] - 0);
    if (Data == 1)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Tingkatan 1 ke");
    lcd.setCursor(0,1);
    lcd.print("tpk perhimpunan");
    delay(100);
    }
    else if (Data == 2)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Tingkatan 2 ke");
    lcd.setCursor(0,1);
    lcd.print("tpk perhimpunan");
    delay(100);
    }
    else if (Data == 3)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Tingkatan 3 ke");
    lcd.setCursor(0,1);
    lcd.print("tpk perhimpunan");
    delay(100);
    }
    else if (Data == 10)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Outdoor Tempt.");
    lcd.setCursor(0,1);
    tmpswitch = (buf[1] - 0);
    temp = (tmpswitch/5)+0.20;
    lcd.print(temp);
    lcd.setCursor(6,1);
    lcd.print("Celcius");
    delay(100);
    }
    else if (Data == 11)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Kebakaran");
    lcd.setCursor(0,1);
    lcd.print("Fire case");
    tone (Tone,659,1000);
    delay(1000);
    tone (Tone,440,1000);
    delay(1000);
    }
    else if (Data == 12)
    {
    lcd.clear();
    lcd.home();
    lcd.print("Guru bertugas");
    
    if (driver.recv(buf, &buflen))
      {
       lcd.setCursor(0,1);
       Serial.println((char*)buf);
       lcd.print((char*)buf);
      }
    delay(100);
    }
    
}
