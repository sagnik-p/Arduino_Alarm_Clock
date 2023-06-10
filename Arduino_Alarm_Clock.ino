/*

######################################################
Author: sagnik-p
######################################################




HERE ARE THE CONNECTIONS:

LCD Connections 
rs = 2
en = 3
d4 = 4
d5 = 5
d6 = 6
d7 = 7

Buttons
Set Alarm/View Alarm = 8
Set Minute (increments by one everytime the button is pressed) = 10
Set Hours (increments by one everytime the button is pressed) = 9
Exit Button = 11

DHT11 Sensor
output = 12

DS3231 RTC
SCL of DS3231 = A5 of Arduino
SDA of DS3231 = A4 of Arduino

Buzzer/led for the alarm
output = 13
*/


// Include the libraries required
#include <Wire.h>
#include <dht.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

// Define symbolic constants and create objects
dht DHT;
#define DHT11_PIN 12
LiquidCrystal lcd(2,3,4,5,6,7);
DS3231 rtc(SDA,SCL);


String dayshort="",day="",dates="",dateshort="",times="";
long ahours=0,amins=0;
void setup() {
  pinMode(13,OUTPUT);
  lcd.begin(16, 2);
  Wire.begin();  


  /*
    *************************VERY IMPORTANT***********************
    When Setting the time for the rtc, FOLLOW THESE STEPS:

    Uncomment the lines below, set the values to current time and upload
    Then, comment these lines again and upload again so that the real time clock does not set its time to the mentioned value whenever it boots 
  */

  //rtc.setDOW(WEDNESDAY);     
  //rtc.setTime(21, 20, 0);     
  //rtc.setDate(26, 9, 2018);

}
void loop() {
  lcd.setCursor(0,0);
  dayshort=rtc.getDOWStr();
  day=dayshort.substring(0,3);
  lcd.print(day);
  lcd.print(" ");
  dates=rtc.getDateStr();
  dateshort = dates.substring(0,6)  +  dates.substring(8);
  lcd.print(dateshort);
  lcd.setCursor(0,1);
  times=rtc.getTimeStr();
  lcd.print(times.substring(0,5));
  int dr8=digitalRead(8);
  if(dr8 == HIGH)
  {
    
    
    
    if(amins == 0 && ahours == 0 )
    {
      lcd.clear();
      lcd.print("   SET ALARM!   ");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALARM AT :");
      lcd.setCursor(7,1);
      if(ahours<10){
        lcd.print("0");
        lcd.print(ahours);
      }else{
        lcd.print(ahours);
      }
      if(amins<10)
      {
        lcd.print("0");
        lcd.print(amins);
        
      }
      else
      {
        lcd.print(amins);
      }
      lcd.print(" Hrs");
    } 
    gotolabel:   
    int dr9=digitalRead(9);
    if(dr9 == HIGH)
    {
       ahours++;
       delay(200);
       if(ahours >= 24)
       {
          ahours=00;
       }
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("hour:");
       lcd.print(ahours);
     }
     int dr10=digitalRead(10);
     if(dr10 == HIGH)
     {
        amins++;
        delay(150);
        if(amins>=60)
        {
          amins=00;
          lcd.clear();
        }
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("minutes:");
        lcd.print(amins);
     }
     int  exitbuttonstatus= digitalRead(11);
     if(exitbuttonstatus == LOW)
     {
      goto gotolabel;
     }
     else
     {
      lcd.clear();
     }
  }
  if(amins!=0 || ahours!=0)
  {
    lcd.setCursor(10,1);
    lcd.print("A");
  }
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(13,0); 
  lcd.print(DHT.temperature);
  lcd.setCursor(15,0);
  lcd.print(char(223));
  lcd.setCursor(13,1);
  lcd.print(DHT.humidity);
  lcd.setCursor(15,1);
  lcd.print("%");
  delay(2000); 
  String currenttime=rtc.getTimeStr();
  String cm=currenttime.substring(3,5),ch=currenttime.substring(0,2);
  long currentmins = cm.toInt();
  long currenthours= ch.toInt();
  if(amins==currentmins && ahours==currenthours)
  {
      digitalWrite(13,HIGH);
      lcd.clear();
      lcd.print("   ALARM ALARM   ");
      delay (5000);
      lcd.clear();
      digitalWrite(13,LOW);
      amins=0,ahours=0;     
  }
}