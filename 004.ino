//ReadTag.ino
#define BLYNK_PRINT Serial
// Allow for receiving messages up to 512 bytes long
//#define BLYNK_MAX_READBYTES 512

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "274827fb258a4d58bc14eef6caac8dc0";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Q6 plus_7546";
char pass[] = "1234567811";
int totalcost=0;
WidgetLCD lcd(V4);
BLYNK_WRITE(V0)
{
  Serial.println("WebHook data:");
  String extractedData=param.asStr();
  String costString=extractedData.substring(37, 40);
  int extractedDataLen=extractedData.length();
  String productName=extractedData.substring(68, extractedDataLen-3);
  int cost=costString.toInt();
  totalcost=totalcost+cost;
  Serial.println(cost);
  Serial.println(" "+productName);
  lcd.print(0,0,productName);
  lcd.print(0,1,cost);
delay(5000);
  lcd.clear();
  lcd.print(0,0,"TOTAL AMOUNT");
   lcd.print(0,1,totalcost);
}

String input;        
int count = 0;        
boolean match = 0;
void setup()
{
  Serial.begin(9600);   
  

  Blynk.begin(auth, ssid, pass);

  
  
}
void loop()
{      
  Blynk.run();
     
  if(Serial.available())// check serial data ( RFID reader)
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
       or till 12 Bytes (the ID size of our Tag) is read */
    while(Serial.available() && count < 12) 
    {
      input = Serial.readString(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    Serial.println(input);
Blynk.virtualWrite(V0, "sheetsu.com/apis/v1.0su/8d614b7ae9ce/search?productid="+input);
 
}
}
