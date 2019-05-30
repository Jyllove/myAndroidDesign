#include <dht.h>
#include <SoftwareSerial.h>
#define WIFI_TX_PIN 8
#define WIFI_RX_PIN 7 
#define rank1 150
#define rank2 200
#define rank3 250
SoftwareSerial wifiSerial(WIFI_TX_PIN, WIFI_RX_PIN); 
dht DHT;
const int DHT11_PIN= 4;
const int motorIn1 = 9;
const int motorIn2 = 10;
int stat = 0; 
String comdata = "";
int i;
int j;
char comdataa[600];
const String OK = "OK";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorIn1,OUTPUT);
  pinMode(motorIn2,OUTPUT);
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
  if (DHT.humidity>50 and DHT.humidity<=70)
  {
    stat = 1;
   }
   else if (DHT.humidity>70 and DHT.humidity<=90)
   {
      stat = 2;
    }
    else if(DHT.humidity>90)
    {
      stat = 3;
     }
    else
    {
      stat = 0;
     }
  switch(stat)
  {
  case 1:
    clockwise(rank1);// When stat=1, set the rotate speed of the motor as rank1=150
    break;
  case 2:
    clockwise(rank2);// When stat=2, set the rotate speed of the motor as rank1=200
    break;
  case 3:
    clockwise(rank3);// When stat=3, set the rotate speed of the motor as rank1=250
    break;
  default:
    clockwise(0);// else, set the rotate speed of the motor as rank1=150
  }
  delay(5000);
}

void clockwise(int Speed)//
{
  analogWrite(motorIn1,0);
  analogWrite(motorIn2,Speed);
}


