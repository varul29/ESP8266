#include <Wire.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

// SHT31 I2C address is 0x44(68)
#define Addr 0x44

//Thingspeak API
String apiKey = "API Write Key"; //using write API key
const char* hostid = "api.thingspeak.com";

// Replace with your network credentials
const char* ssid     = "SSID";
const char* password = "Password";
float Ctemp,Ftemp,humid;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void setup() 
{
  Wire.begin(2,14);
  Serial.begin(115200);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  
  temptask();
    
  WiFiClient client = server.available();   // Listen for incoming clients
  
  thing();

  if (client) 
   {                             // If a new client connects,

    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the 
       client;
       String c = client.readStringUntil('\r');             // read a byte, then
       Serial.println(c);
     }                    // print it out the serial monitor
       // if the current line is blank, you got two newline characters in a row.
       // that's the end of the client HTTP request, so send a response:
        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
        // and a content-type so the client knows what's coming, then a blank line:
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

          String PAGE2 = 
 "<!DOCTYPE html>"
 "<html>"
 "<head>"
 "<meta charset=\"utf-8\">"
 "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0\">"
 "<title> My first HTML page</title>"
 "</head>"
 "<body style= \"background-color:#EDEEF2\">"
 "<h1 style= \"color:blue\">Temperature and Humidity</h1>"
 "<h3 style= \"font-family:verdana; color:blue\">Temperature in Celcius:</h3>"
 "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(Ctemp,1)+
 "</p>"
 "<h3 style= \"font-family:verdana; color:blue\">Temperature in Fahrenheit:</h3>"
 "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(Ftemp,1)+
 "</p>"
 "<h3 style= \"font-family:verdana; color:blue\">Humidity:</h3>"
 "<p style=\"font-size:160%; font-family:Lucida Console\">"+String(humid,1)+
 "</p>"
 "</body>"
 "</html>";
 break;
 // Display the HTML web page
 client.println(PAGE2);
      }

}
// Clear the header variable

// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
 }

void thing(){

temptask();

WiFiClient wificlient;

if (wificlient.connect(hostid,80))   //   api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(Ctemp);
                             postStr +="&field2=";
                             postStr += String(Ftemp);
                             postStr +="&field3=";
                             postStr += String(humid);
                             postStr += "\r\n\r\n";
 
                            wificlient.print("POST /update HTTP/1.1\n");
                              wificlient.print("Host: api.thingspeak.com\n");
                              wificlient.print("Connection: close\n");
                              wificlient.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                              wificlient.print("Content-Type: application/x-www-form-urlencoded\n");
                              wificlient.print("Content-Length: ");
                              wificlient.print(postStr.length());
                              wificlient.print("\n\n");
                              wificlient.print(postStr);
 
                             Serial.print("Temperature in celcius: ");
                             Serial.print(Ctemp);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(Ftemp);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(humid);
                             Serial.println("%. Send to Thingspeak.");
                        }
          wificlient.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}

void temptask(){
  unsigned int data[6];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Send 16-bit command byte
  Wire.write(0x2C);
  Wire.write(0x06);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

 // Read 6 bytes of data
 // temp msb, temp lsb, temp crc, hum msb, hum lsb, hum crc
 if (Wire.available() == 6)
 {
   data[0] = Wire.read();
   data[1] = Wire.read();
   data[2] = Wire.read();
   data[3] = Wire.read();
   data[4] = Wire.read();
   data[5] = Wire.read();
  }
  // Convert the data
  int temp = (data[0] * 256) + data[1];
  float cTemp = -45.0 + (175.0 * temp / 65535.0);
  float fTemp = (cTemp * 1.8) + 32.0;
  float humidity = (100.0 * ((data[3] * 256.0) + data[4])) / 65535.0;  
  Ctemp = cTemp;
  Ftemp = fTemp;
  humidity = humid;

  Serial.print("Temperature in C:\t");
  Serial.println(String(cTemp,1));
  Serial.print("Temperature in F:\t");
  Serial.println(String(fTemp,1));
  Serial.print("Humidity:\t ");
  Serial.println(String(humidity,1));
}
