#include <DNSServer.h>
#include <ESPUI.h>
#include "time.h"
#include "esp_system.h"
#include <OneWire.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


#define SUN  0
#define SUN_CLOUD  1
#define CLOUD 2
#define RAIN 3
#define THUNDER 4

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 26, /* data=*/ 27);   // ESP32 Thing, HW I2C with pin remapping
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g21(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 26, /* data=*/ 27);   // ESP32 Thing, HW I2C with pin remapping
OneWire  ds(5);  // on pin 10 (a 4.7K resistor is necessary)

const char* ssid       = "gdzhanghome";
const char* password   = "gdzhang@xyzhang";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 10000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
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


void drawWeather(uint8_t symbol, float degree)
{
  u8g2.setFont(u8g2_font_open_iconic_thing_4x_t);
  u8g2.drawGlyph(0, 32, 78); 

   
  u8g2.setFont(u8g2_font_logisoso24_tf);
  u8g2.setCursor(28, 32);
  u8g2.print(degree);
  u8g2.print("°C");   // requires enableUTF8Print()
}

/*
  Draw a string with specified pixel offset. 
  The offset can be negative.
  Limitation: The monochrome font with 8 pixel per glyph
*/
void drawScrollString(int16_t offset, const char *s)
{
    u8g2.setFont(u8g2_font_8x13_mf);
    u8g2.drawStr(0, 62, s);
}
void draw(const char *s, uint8_t symbol, float degree)
{
  int16_t offset = -(int16_t)u8g2.getDisplayWidth();
  int16_t len = strlen(s);
  for(;;)
  {
    u8g2.firstPage();
    do {
      drawWeather(symbol, degree);
      drawScrollString(offset, s);
    } while ( u8g2.nextPage() );
    delay(20);
    offset+=2;
    if ( offset > len*8+1 )
      break;
  }
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
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt
  initWeb();
 

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use .beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */

  
  ESPUI.begin("gdzhang的壁挂炉！！");
    u8g2.begin();  
  u8g2.enableUTF8Print();
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
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  
  if ( !ds.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
  
  Serial.print("ROM =");
  for( i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return;
  }
  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(100);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  //Serial.print("  Data = ");
  //Serial.print(present, HEX);
  //Serial.print(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  //  Serial.print(data[i], HEX);
  //  Serial.print(" ");
  }
  //Serial.print(" CRC=");
  //Serial.print(OneWire::crc8(data, 8), HEX);
  //Serial.println();

  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  //fahrenheit = celsius * 1.8 + 32.0;
  Serial.print("  Temperature = ");
  Serial.print(celsius);
  Serial.print("Celsius, ");




  draw("测试", SUN, celsius);

}
