#include <DNSServer.h>
#include <ESPUI.h>
#include "time.h"


const char* ssid       = "gdzhanghome";
const char* password   = "gdzhang@xyzhang";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;


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

void setup(void) {
  Serial.begin(115200);
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
   
   pinMode(control_pin, OUTPUT);           // set pin to input
   digitalWrite(control_pin, LOW);       // turn on pullup resistors

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        delay(2000);

  printLocalTime();

  // change the beginning to this if you want to join an existing network
  /*
     Serial.begin(115200);
     WiFi.begin(ssid, password);
     Serial.println("");
     // Wait for connection
     while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     }
     Serial.println("");
     Serial.print("IP address: ");
     Serial.println(WiFi.localIP());
   */
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


  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use .beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */

  
  ESPUI.begin("gdzhang的壁挂炉！！");
}

void loop(void) {
  int ti;
  int ttc_hour,ttc_min,ttc_sec;
  ttc_hour=open_counter/3600;
  ttc_min=(open_counter%3600)/60;
  ttc_sec=(open_counter%3600)%60;
  String ttc_hour_s,ttc_min_s,ttc_sec_s;

  char toshow[32];
  //dnsServer.processNextRequest();
  
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

    delay(1000);

}
