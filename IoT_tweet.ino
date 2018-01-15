#include <SoftwareSerial.h>
#include <stdlib.h>
#include <dht.h>
#define DHT11_PIN 5
dht DHT;
int ledPin = 13;
String getStr;
String ssid="ghostpro";
String pass="winterishere!";
// replace with your channel's thingspeak API key
String apiKey = "C40ZCUVMXT9Z3JFR";
String APIKEY="NY51Q9Q4UXOLWUDJ";

// connect 10 to TX of ESP8266
// connect 11 to RX of ESP8266
//SoftwareSerial ser(10, 11); // RX, TX
int k=0;
void setup() {
  // put your setup code here, to run once:
 pinMode(ledPin, OUTPUT);    
 Serial.begin(115200);
 //ser.begin(115200);
/* String cmd="AT";
 ser.println(cmd);
 if(ser.find("OK"))
  Serial.println("OK");
 ser.write("AT+CWMODE=3\r\n");
 if (ser.available()) {
    Serial.write(ser.read());
  }
 String cmd="AT+CWJAP=";
 cmd+=ssid;
 cmd+=",";
 cmd+=pass;
 ser.println(cmd);
 if (ser.available()) {
    Serial.write(ser.read());
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:
 String cmd="AT+RST";
 Serial.println(cmd);
 delay(15000);
  // part 1 glow check
  digitalWrite(ledPin, HIGH);   
  delay(200);               
  digitalWrite(ledPin, LOW);
  DHT.read11(DHT11_PIN);
  //temp and humidity read
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(2000);
  /*cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "api.thingspeak.com"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  if(ser.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(DHT.temperature);
  //getStr +="&field2=";
  //getStr += String(DHT.humidity);
  getStr += "\r\n\r\n";
  //print values in server
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(16000);*/
  // part 2 glow check
  digitalWrite(ledPin, HIGH);   
  delay(200);               
  digitalWrite(ledPin, LOW);
  //tweet
  cmd="AT+RST";
  Serial.println(cmd);
  delay(15000);
  cmd="AT+CIPMODE=0";
  Serial.println(cmd);
  cmd="AT+CIPMUX=1";
  Serial.println(cmd);
  cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "api.thingspeak.com"; // api.thingspeak.com
  cmd += "\",80";
  Serial.println(cmd);
  if(Serial.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
  getStr = "GET /apps/thingtweet/1/statuses/update?api_key=";
  getStr += APIKEY;
  getStr +="&status=";
  //getStr="hello";
  getStr += "#";
  getStr +=String(k);
  getStr +="Temperature=";
  getStr +=String(DHT.temperature);
  getStr +=",Humidity";
  getStr +=String(DHT.humidity);
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial.println(cmd);
  delay(2000);
  if(Serial.find(">")){
    k++;
    Serial.print(getStr);
  }
  else{
    Serial.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(16000);
   // part 3 glow check
  digitalWrite(ledPin, HIGH);   
  delay(200);               
  digitalWrite(ledPin, LOW);
}  
