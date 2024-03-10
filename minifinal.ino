#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include  <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeMonoOblique9pt7b.h>
#include  <DFRobot_DHT11.h>
#define SCREEN_WIDTH 128
#define  SCREEN_HEIGHT 64 

#define OLED_RESET     4 
Adafruit_SSD1306 display(SCREEN_WIDTH,  SCREEN_HEIGHT,&Wire,OLED_RESET);

#define sensor    A0 
#define DHTPIN  8 

int gasLevel  = 0;    
String quality =""; 
DFRobot_DHT11 dht;

void sendSensor()
{
  dht.read(DHTPIN);
  float h = dht.humidity;
  float t = dht.temperature;

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed  to read from DHT sensor!");
    return;
  }
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont();
  display.setCursor(0, 43);
  display.println("Temp  :");
  display.setCursor(80, 43);
  display.println(t);
  display.setCursor(114, 43);
  display.println("C");
  display.setCursor(0,  56);
  display.println("RH    :");
  display.setCursor(80, 56);
  display.println(h);
  display.setCursor(114, 56);
  display.println("%");
}

void air_sensor()
{
  gasLevel = analogRead(sensor);

  if(gasLevel<300){
    quality = "  GOOD!";
  }
  else if (gasLevel >301 && gasLevel<350){
    quality =  "  Poor!";
  }
  else{
    quality = "BAD";   
  }
  
  display.setTextColor(WHITE);
  display.setTextSize(1);  
  display.setCursor(1,5);
  display.setFont();
  display.println("Air Quality:");
  display.setTextSize(1);
  display.setCursor(20,23);
  display.setFont(&FreeMonoOblique9pt7b);
  display.println(quality);  
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor,INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address  0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
}
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  display.setTextSize(2);
  display.setCursor(50, 0);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(23, 20);
  display.println("Qulaity monitor");
  display.display();
  delay(1200);
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(50,5);
  display.println("BY");
  display.setCursor(20, 20);
  display.println("Team-17");
  display.display();
  delay(2000);
  display.clearDisplay();    
}

void loop() {
display.clearDisplay();
air_sensor();
sendSensor();
display.display();  
}

