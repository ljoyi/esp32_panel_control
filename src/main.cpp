#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>  //  ESP8266WebServer库
#include <NTPClient.h>
#include <WiFiUdp.h>

Servo myservo;                                            //初始化舵机
ESP8266WebServer esp8266_server(80);                      // 建立ESP8266WebServer对象，对象名称为esp8266_server
WiFiUDP udp;                                              //udp通信
// NTPClient timeClient(udp, "pool.ntp.org", 28800, 60000);  //ntp初始化
const char* STAssid = "iot";
const char* STApassword = "question";

int ServoPin = 14;
int begin_hour = 20;
void setup() {
  Serial.begin(115200);  //初始化串口


  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STAssid, STApassword);
  Serial.print("\r\nConnecting to ");
  Serial.print(STAssid);
  Serial.println("...");
  gotoWifi();
  // put your setup code here, to run once:
  myservo.attach(ServoPin);
  myservo.write(90);
}
void gotoWifi() {
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
    Serial.print("\r\nfailed ");      //连接Wifi失败，LED持续闪烁
  }
  digitalWrite(LED_BUILTIN, HIGH);  //连接成功，led熄灭
  Serial.print("\r\nIP address:");
  Serial.println(WiFi.localIP());  //连接成功，led熄灭，打印自己的IP

  // timeClient.begin();
  // timeClient.update();  // 获取当前时间
  // 获取当前小时和分钟
  // int currentHour = timeClient.getHours();
  // int currentMinute = timeClient.getMinutes();
  // Serial.print("Current Time: ");
  // Serial.print(currentHour);
  // Serial.print(":");
  // Serial.println(currentMinute);
    esp8266_server.begin();                           //  详细讲解请参见太极创客网站《零基础入门学用物联网》
    esp8266_server.on("/", HTTP_GET, handleRoot);     // 设置服务器根目录即'/'的函数'handleRoot'
    esp8266_server.on("/LED", HTTP_POST, handleLED);  // 设置处理LED控制请求的函数'handleLED'
    esp8266_server.onNotFound(handleNotFound);
    Serial.println("HTTP esp8266_server started");  //  告知用户ESP8266网络服务功能已经启动
  // 判断是否在20:00-01:00之间
  // if (currentHour >= begin_hour || currentHour < 1) {
  //   // 如果当前时间在 20:00 到 01:00 之间，启动Web服务
  //   esp8266_server.begin();                           //  详细讲解请参见太极创客网站《零基础入门学用物联网》
  //   esp8266_server.on("/", HTTP_GET, handleRoot);     // 设置服务器根目录即'/'的函数'handleRoot'
  //   esp8266_server.on("/LED", HTTP_POST, handleLED);  // 设置处理LED控制请求的函数'handleLED'
  //   esp8266_server.onNotFound(handleNotFound);
  //   Serial.println("HTTP esp8266_server started");  //  告知用户ESP8266网络服务功能已经启动
  // } else {
  //   // 如果当前时间不在 20:00 到 01:00 之间，进入深度睡眠
  //   Serial.println("Entering deep sleep mode...");
  //   //进入轻度睡眠
  //   ESP.deepSleep(30e9);
  // }
}

void handleRoot() {
  // 修改HTML，增加按钮尺寸并居中显示
  String html = "<html><head><style>"
                "body{display:flex; justify-content:center; align-items:center; height:100vh; margin:0;}"
                "button{padding:20px 40px; font-size:30px; margin:20px; border-radius:10px; border:2px solid #333;}"
                "button:hover{background-color:#4CAF50; color:white;}"
                "</style></head><body>";
  html += "<form action=\"/LED\" method=\"POST\">";
  html += "<button name=\"action\" value=\"on\">Turn On</button>";
  html += "<button name=\"action\" value=\"off\">Turn Off</button>";
  html += "</form></body></html>";

  esp8266_server.send(200, "text/html", html);  // 发送修改后的HTML响应
}

// 设置处理404情况的函数'handleNotFound'
void handleNotFound() {                                      // 当浏览器请求的网络资源无法在服务器找到时，
  esp8266_server.send(404, "text/plain", "404: Not found");  // NodeMCU将调用此函数。
}

//处理LED控制请求的函数'handleLED'
void handleLED() {

  String action = esp8266_server.arg("action");  // 获取按钮提交的值

  if (action == "on") {
    myservo.write(150);              // 打开LED
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW

    delay(1000);
    myservo.write(90);
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off by making the voltage HIGH

  } else if (action == "off") {
    myservo.write(15);                // 打开LED
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);
    myservo.write(90);                // 关闭LED
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off by making the voltage HIGH

    // 改变LED的点亮或者熄灭状态
  }
  esp8266_server.sendHeader("Location", "/");  // 跳转回页面根目录
  esp8266_server.send(303);                    // 发送Http相应代码303 跳转
}
void loop() {
  // // put your main code here, to run repeatedly:
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin(STAssid, STApassword);
    gotoWifi();
  }  //检查wifi连接状态，若断开则重连
esp8266_server.handleClient();
  // timeClient.begin();
  // timeClient.update();  // 获取当前时间
  // 获取当前小时和分钟
  // int currentHour = timeClient.getHours();
  // int currentMinute = timeClient.getMinutes();
  // if (currentHour >= begin_hour || currentHour < 2) {
  //   esp8266_server.handleClient();// 处理http服务器访问
  // } else {
  //   ESP.deepSleep(30e9);
  // }
}