#include <dht.h>
#include <SoftwareSerial.h>
#define WIFI_TX_PIN 8
#define WIFI_RX_PIN 7 
SoftwareSerial wifiSerial(WIFI_TX_PIN, WIFI_RX_PIN); 
dht DHT;
const int DHT11_PIN= 4;
String comdata = "";
int i;
int j;
char comdataa[600];
const String OK = "OK";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifiSerial.begin(9600);
  wifiSerial.println("AT");
  delay(1000);
  Serial.println("start");
  i=0;
  while (wifiSerial.available() > 0)  
    {
        comdataa[i] = char(wifiSerial.read());
        delay(2);
        i++;
    }
    comdata=String(comdataa[7])+String(comdataa[8]);
    Serial.println(comdata);
  if(comdata==OK){
    comdata = "";
    Serial.println("ok");
    wifiSerial.println("AT+CWJAP=\"joe\",\"jyl1105.\"");
    delay(8000);
    wifiSerial.println("AT+CIPSTART=\"TCP\",\"172.20.10.3\",9000");
    delay(5000);
  }
  
}

void loop()
{
  D: int chk = DHT.read11(DHT11_PIN);//read the value returned from sensor
  switch (chk)
  {
  case DHTLIB_OK:  
    //Serial.println("OK!"); 
    break;
  case DHTLIB_ERROR_CHECKSUM: 
    //goto D;
    //Serial.print("Checksum error,\t"); 
    break;
  case DHTLIB_ERROR_TIMEOUT: 
      goto D;
    //Serial.print("Time out error,\t"); 
    break;
  default: 
     // goto D;
    //Serial.print("Unknown error,\t"); 
    break;
  }
  wifiSerial.println("AT+CIPSTART=\"TCP\",\"172.20.10.3\",9000");
  delay(3000);
  wifiSerial.println("AT+CIPSEND=12");
  wifiSerial.println(String(DHT.temperature)+","+String(DHT.humidity));
  
  Serial.println("temperature: "+String(DHT.temperature)+"°C");
  Serial.println("humidity: "+String(DHT.humidity)+"%");

  delay(7000);

  
 }
