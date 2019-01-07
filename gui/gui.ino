#include <DNSServer.h>
#include <ESPUI.h>
#include "time.h"
#include "esp_system.h"
#include <OneWire.h>

#include <DallasTemperature.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 26, /* data=*/ 27);   // ESP32 Thing, HW I2C with pin remapping
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g21(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 26, /* data=*/ 27);   // ESP32 Thing, HW I2C with pin remapping
OneWire  oneWire(5);  // on pin 10 (a 4.7K resistor is necessary)

const char* ssid       = "gdzhanghome";
const char* password   = "gdzhang@xyzhang";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 0;
const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 10000;  //time in ms to trigger the watchdog
hw_timer_t * timer = NULL;

hw_timer_t *watchdogtimer = NULL;
DeviceAddress insideThermometer = { 0x28, 0x8F, 0xB2, 0x2B, 0x0, 0x0, 0x80, 0x74 };
///28 8F B2 2B 0 0 80 74
int RS=11;
float celsius=10;

DallasTemperature ds(&oneWire);

void IRAM_ATTR resetModule() {
  ets_printf("watchdog reboot\n");
  esp_restart();
}


#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

long oldTime = 0;
bool switchi = false;
bool gas_on = false;
bool loop_on = false;
int max_on_time = 2;
int open_counter= max_on_time *3600;
int open1_gas_begin=6;
int open1_continue=2;
int open2_gas_begin=17;
int open2_continue=2;
int control_pin = 2;
String cur_time = "0000000000000000";
struct tm timeinfo;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void printLocalTime()
{
  struct tm timeinfo1;
  if(!getLocalTime(&timeinfo1)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo1, "%A, %B %d %Y %H:%M:%S");

}
void manual_con_Call(Control sender, int type) { 
  max_on_time = sender.value.toInt();
  
  Serial.println(sender.value); }

void number1Call(Control sender, int type) {
  open1_gas_begin = sender.value.toInt();

  Serial.println(sender.value); 
  }
void number1_con_Call(Control sender, int type) {
  open1_continue = sender.value.toInt();

  Serial.println(sender.value); 
  }
void number2Call(Control sender, int type) {
  open2_gas_begin = sender.value.toInt();

  Serial.println(sender.value); 
  }
void number2_con_Call(Control sender, int type) {
  open2_continue = sender.value.toInt();
 
  Serial.println(sender.value); 
  }


void switch_gas(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("gas on\n");
      gas_on = true;
      digitalWrite(control_pin, HIGH);
      ESPUI.print(0, "开");
      open_counter=max_on_time * 3600;
      break;
    case S_INACTIVE:
      Serial.print("gas off");
      gas_on = false;
      digitalWrite(control_pin, LOW);
      ESPUI.print(0, "关闭");

      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void buttonCallback(Control sender, int type) {
  switch (type) {
    case B_DOWN:
      Serial.println("Button DOWN");
      break;
    case B_UP:
      Serial.println("Button UP");
      break;
  }
}

void switch_loop(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("loop on");

      loop_on = true;
      ESPUI.print(1, "开");

      break;
    case S_INACTIVE:
      Serial.print("loop off");
      loop_on = false;
      if( gas_on == false ){
          digitalWrite(control_pin, LOW);
          ESPUI.print(0, "关");

        }
      ESPUI.print(1, "关");


      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}
void show(){
  Serial.print("showtimer\n");
  u8g21.clearBuffer();          // clear the internal memory
  u8g21.setFont(u8g2_font_wqy12_t_gb2312);
  u8g21.drawUTF8(0, 62, asctime(&timeinfo));
  u8g21.setFont(u8g2_font_open_iconic_thing_6x_t);
  u8g21.drawGlyph(0, 50, 78);  
  u8g21.sendBuffer(); 
   
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_logisoso38_tf);
  u8g2.setCursor(0, 44);
        portENTER_CRITICAL(&timerMux);

  u8g2.print(celsius,1);
      portEXIT_CRITICAL(&timerMux);

  u8g2.print("°C");   // requires enableUTF8Print()
  u8g2.sendBuffer(); 

}
void  gettemp(){
      ds.setResolution(RS);
    ds.requestTemperaturesByAddress(insideThermometer);
    //ds.getTempC(insideThermometer);
    celsius = ds.getTempC(insideThermometer);
  }
void startTimer() {
  timer = timerBegin(0, 80, true); // timer_id = 0; divider=80; countUp = true;
  timerAttachInterrupt(timer, &gettemp, true); // edge = true
  timerAlarmWrite(timer, 1000000, true);  //1000 ms
  timerAlarmEnable(timer);
}

void endTimer() {
  timerEnd(timer);
  timer = NULL; 
}


void initWeb(){
  ESPUI.label("状态:", COLOR_TURQUOISE, "关");
  ESPUI.label("按天循环状态:", COLOR_TURQUOISE, "关");

  ESPUI.number("（1）每天开启时间（24小时制）", &number1Call, COLOR_ALIZARIN, open1_gas_begin, 0, 24);
  ESPUI.number("（1）每天开启时长（小时）", &number1_con_Call, COLOR_ALIZARIN, open1_continue, 0, 5);

  ESPUI.number("（2）每天开启时间（24小时制）", &number2Call, COLOR_WETASPHALT, open2_gas_begin, 0, 24);
  ESPUI.number("（2）每天开启时长（小时）", &number2_con_Call, COLOR_WETASPHALT, open2_continue, 0, 10);
  ESPUI.switcher("壁挂炉按天循环开启", false, &switch_loop, COLOR_NONE);
  ESPUI.number("手动开启壁挂炉持续时间(小时)", &manual_con_Call, COLOR_WETASPHALT, max_on_time, 0, 5);
  ESPUI.switcher("手动开启壁挂炉", false, &switch_gas, COLOR_ALIZARIN);
  ESPUI.label("当前时间:", COLOR_TURQUOISE, "当前时间");
  ESPUI.label("手动开启壁挂路自动关闭剩余时间:", COLOR_TURQUOISE, "自动关闭");
  ESPUI.begin("gdzhang的壁挂炉！！");

}

void setupwatchdog()
{
  watchdogtimer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(watchdogtimer, &resetModule, true);  //attach callback
  timerAlarmWrite(watchdogtimer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(watchdogtimer);                          //enable interrupt
}
void  setupOLED()
{ 
  
  u8g2.setI2CAddress(0x78);
  u8g2.begin();  
  u8g2.enableUTF8Print();
  u8g21.setI2CAddress(0x7a);
  u8g21.begin();  
  u8g21.enableUTF8Print();
}

void setupWifi(){
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
   
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  }
void setup(void) {
  Serial.begin(115200);
  //connect to WiFi
  setupWifi();
   pinMode(control_pin, OUTPUT);           // set pin to input
   digitalWrite(control_pin, LOW);       // turn on pullup resistors

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  setupwatchdog();
  initWeb();
  setupOLED();
  //startTimer();
}

void loop(void) {
      //ESPUI.updateSwitcher("Switch one", switchi);

  int ti;
  int ttc_hour,ttc_min,ttc_sec;
  ttc_hour=open_counter/3600;
  ttc_min=(open_counter%3600)/60;
  ttc_sec=(open_counter%3600)%60;
  String ttc_hour_s,ttc_min_s,ttc_sec_s;

  char toshow[32];
  //dnsServer.processNextRequest();
  timerWrite(timer, 0); //reset timer (feed watchdog)

  if ((loop_on == true) && (gas_on == false )){
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
      return;
    }else{

      ti = (timeinfo.tm_hour + 8)%24 -1 ;
            Serial.println("tm_hour");
      Serial.println(timeinfo.tm_hour);
      Serial.println(ti);

      Serial.println(open1_gas_begin);
      Serial.println(open1_continue);
      Serial.println(open2_gas_begin);
      Serial.println(open2_continue);
      if (( ti >= open1_gas_begin && 
           ti <= open1_gas_begin + open1_continue)||
           
         ( ti >= open2_gas_begin && 
           ti <= open2_gas_begin + open2_continue))
           {
           digitalWrite(control_pin, HIGH);
           ESPUI.print(0, "开");
           Serial.println("in loop gas on ");
           }else{
           digitalWrite(control_pin, LOW);
           ESPUI.print(0, "关");
           Serial.println("in loop gas off ");

            
            } 
    }
  }
  if ( gas_on == true ){
    open_counter=open_counter-1;
    ttc_hour=open_counter/3600;
    ttc_min=(open_counter%3600)/60;
    ttc_sec=(open_counter%3600)%60;
    ttc_hour_s=String(ttc_hour);
    ttc_min_s=String(ttc_min);
    ttc_sec_s=String(ttc_sec);
    String show=ttc_hour_s + "小时" + ttc_min_s + "分" + ttc_sec_s +"秒";
    show.toCharArray(toshow,32);
    Serial.print("opencounter:");
    Serial.println(open_counter);
    ESPUI.print(10, toshow);
    if (open_counter  < 0){
           gas_on = false;
           digitalWrite(control_pin, LOW);
           ESPUI.print(0, "关");
      }
  }
 /* if (millis() - oldTime > 5000) {
    ESPUI.print("Millis:", String(millis()));
    switchi = !switchi;
    ESPUI.updateSwitcher("Switch one", switchi);
    oldTime = millis();
  }
  */
    getLocalTime(&timeinfo);
    ESPUI.print(9, asctime(&timeinfo));

  Serial.print("  Temperature = ");
      portENTER_CRITICAL(&timerMux);

  Serial.print(celsius);
      portEXIT_CRITICAL(&timerMux);

  Serial.print(" Celsius\n");


   // String part01 = getValue(application_command,' ',3);
    //String part02 = getValue(application_command,';',0);
  
    delay(1000);
  gettemp();
  show();
}
