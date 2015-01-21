
//tft screen connections
//+5V:	+5V
//MISO:	pin 12
//SCK:	pin 13
//MOSI:	pin 11
//LCD CS:	pin 10
//SD CS:	pin 4
//D/C:	pin 9
//RESET:	pin 8
//BL:	+5V
//GND:	GND

#include <Time.h>  
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "DHT.h" // sensor lib

//defining tft pins
#define sclk 13
#define mosi 11
#define cs   10
#define dc   9
#define rst  8

#define DHTPIN 3     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by Unix time_t as ten ASCII digits
#define TIME_HEADER  'T'   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

void setup(void) {
  Serial.begin(9600);
  dht.begin();
  tft.initR(INITR_REDTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(tft.getRotation()+1);
  
tftPrintTest(); //Initial introduction text, uncomment to view on screen

tft.fillScreen(ST7735_BLACK); // Clear screen
 
// Printing static Items on display in the setup void in order to speed up the loop void
  
  tft.fillScreen(ST7735_BLACK);
   //  clear screen
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5,5);
  tft.println("Humidity: (%)");
  tft.setCursor(5,40);
  tft.println("Temperature: (C)");
  tft.drawLine(0, 76, tft.width()-1, 76, ST7735_WHITE); //draw line separator
}

void loop() {
  
  if(Serial.available() ) 
  {
    processSyncMessage();
  }
  if(timeStatus() == timeNotSet){
    
    tft.setTextSize(1);
    tft.setTextColor(ST7735_WHITE);
    Serial.println("waiting for sync message");
    tft.setCursor(20, 82);
    tft.println("sync");
    tft.setCursor(20, 95);
    tft.println("for time");
    
  }
  else{
  digitalClockDisplay();
  }
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  int color = setColor();
  
  tft.setTextSize(2);
  tft.setTextColor(color, (0,0,0));
  delay(80);
  tft.setCursor(20,20);
  tft.print(h,2);
  tft.setCursor(20,55);
  tft.setTextColor((100, 27, color), (0,0,0));
  delay(80);
  tft.print(t,2);
  
}

void printDigitsm(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0 (to be used with minutes)
  Serial.print(":");
  tft.print(":");
  if(digits < 10){
    Serial.print('0');
    tft.print('0');
  }
  Serial.print(digits);
  tft.print(digits);
}

void printDigitsh(int digits){
  // utility function for digital clock display: prints leading 0 (to be used with hours)
  if(digits < 10){
    Serial.print('0');
    tft.print('0');
  }
  Serial.print(digits);
  tft.print(digits);
}

void processSyncMessage() {
  // if time sync available from serial port, update time and return true
  while(Serial.available() >=  TIME_MSG_LEN ){  // time message consists of header & 10 ASCII digits
    char c = Serial.read() ; 
    Serial.print(c);  
    if( c == TIME_HEADER ) {       
      time_t pctime = 0;
      for(int i=0; i < TIME_MSG_LEN -1; i++){   
        c = Serial.read();          
        if( c >= '0' && c <= '9'){   
          pctime = (10 * pctime) + (c - '0') ; // convert digits to a number    
        }
      }   
      setTime(pctime);   // Sync Arduino clock to the time received on the serial port
    }  
  }
}

void digitalClockDisplay(){
  // digital clock display of the time
  
  tft.setCursor(20, 82);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
  tft.print(day());
  tft.print(".");
  tft.print(month());
  tft.print(".");
  tft.print(year());
  tft.setTextSize(2);
  tft.setCursor(20, 95);
  printDigitsh(hour());
  printDigitsm(minute());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void tftPrintTest() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(2, 10);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("This device");
  tft.setCursor(2, 33);
  tft.println("will make");
  tft.setCursor(2, 56);
  tft.println("your life");
  tft.setCursor(2, 79);
  tft.println("complete");
  delay(2200);
  }

 int setColor() {
  
  int reading = analogRead(A0);
  int color;
  if (reading >= 0 && reading < 200){
    color = ST7735_YELLOW;
  }
  else if (reading >= 200 && reading < 400){
    color = ST7735_RED;
  }
  else if (reading >= 400 && reading < 600){
    color = ST7735_BLUE;
  }
  else if (reading >= 600 && reading < 800){
    color = ST7735_GREEN;
  }  
  else{color = ST7735_CYAN;
}  
  return color;
}    




