#include <DNSServer.h>
#include <ESPUI.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

#if defined(ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

const char *ssid = "ESPUI";
const char *password = "";

long oldTime = 0;
bool switchi = false;
bool gas_on = false;
bool loop_on = false;
int max_on_time = 2;
int open1_gas_begin=6;
int open1_continue=2;
int open2_gas_begin=17;
int open2_continue=2;


void manual_con_Call(Control sender, int type) { 
  max_on_time = sender.value.toInt();
  
  Serial.println(sender.value); }

void number1Call(Control sender, int type) {
  Serial.println(sender.value); 
  }
void number1_con_Call(Control sender, int type) {
  Serial.println(sender.value); 
  }
void number2Call(Control sender, int type) {
  Serial.println(sender.value); 
  }
void number2_con_Call(Control sender, int type) { 
  Serial.println(sender.value); 
  }


void switch_gas(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("gas on\n");
      gas_on = true;
      ESPUI.print(0, "状态: 开");

      break;
    case S_INACTIVE:
      Serial.print("gas off");
      gas_on = false;
      ESPUI.print(0, "状态: 关闭");

      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void switch_loop(Control sender, int value) {
  switch (value) {
    case S_ACTIVE:
      Serial.print("loop on");

      loop_on = true;
      ESPUI.print(1, "按天循环状态: 开");

      break;
    case S_INACTIVE:
      Serial.print("loop off");
      loop_on = true;
            ESPUI.print(1, "按天循环状态: 关闭");


      break;
  }
  Serial.print(" ");
  Serial.println(sender.id);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  /*
  #if defined(ESP32)
    WiFi.setHostname(ssid);
  #else
    WiFi.hostname(ssid);
  #endif
  */

  WiFi.softAP(ssid);
  // WiFi.softAP(ssid, password);
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

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

  ESPUI.number("循环开启时间1", &number1Call, COLOR_ALIZARIN, 5, 0, 10);
  ESPUI.number("循环开启时间1持续时间", &number1_con_Call, COLOR_ALIZARIN, 5, 0, 10);

  ESPUI.number("循环开启时间2", &number2Call, COLOR_WETASPHALT, 5, 0, 10);
  ESPUI.number("循环开启时间2持续时间", &number2_con_Call, COLOR_WETASPHALT, 5, 0, 10);
  ESPUI.switcher("开启壁挂炉按天循环", true, &switch_loop, COLOR_NONE);
  ESPUI.number("手动开启壁挂炉持续时间(小时)", &manual_con_Call, COLOR_WETASPHALT, 5, 0, 10);
  ESPUI.switcher("手动开启壁挂炉", false, &switch_gas, COLOR_ALIZARIN);
  

  /*
     .begin loads and serves all files from PROGMEM directly.
     If you want to serve the files from SPIFFS use .beginSPIFFS
     (.prepareFileSystem has to be run in an empty sketch before)
   */

  dnsServer.start(DNS_PORT, "*", apIP);
  ESPUI.begin("ESPUI Control");
}

void loop(void) {
  dnsServer.processNextRequest();

 /* if (millis() - oldTime > 5000) {
    ESPUI.print("Millis:", String(millis()));
    switchi = !switchi;
    ESPUI.updateSwitcher("Switch one", switchi);
    oldTime = millis();
  }
  */
}
