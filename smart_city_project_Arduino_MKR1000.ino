#include <ArduinoHttpClient.h>
#include <WiFi101.h>
#include <PMS5003.h>
// MKR1000 Pins setup
const int SLEEP_PIN = 6; // this pin is for setting the sensor to sleep while it is not taking the data.
const String uuid = ""; // This is the place where you should put your UUID. It is also fro future application.

// method setup
const String content_type = "application/x-www-form-urlencoded";// this is for POST method

// Your WiFi setup
String postData ="";
char serverAddress[] = "107.170.217.4";// This is the website of Smart City Project
int port = 8080;// port number of the website

// WiFi Login Data
String ssid = "Name of Your Wifi";
String password ="Password of Your Wifi";

// initialize your variable value
PMS5003 pms5003;
String PM1 = "N/A";
String PM2_5 = "N/A";
String PM10 = "N/A";
String temperature = "N/A";
String humadity = "N/A";

// HTTP Connection
WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;
String response;
int statusCode = 0;

void setup() 
{
  Serial.begin(9600); // Serial for serial monitor. If the sensor is successfully sending data to website, this can be comment out
  Serial1.begin(9600);// Serial1 port for PMS5006
  pinMode(SLEEP_PIN,OUTPUT); // Setup Pin 6 as output pin
  digitalWrite(SLEEP_PIN,HIGH); // Let the sensor start working as default
  while(status != WL_CONNECTED) { // start connection
    Serial.print("Attempting to connect to your wifi: " + ssid + "\n");
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, password);
  }
  // print the SSID of the your WiFi
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  // print your WiFi Module's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");Serial.println(ip);
}

void loop() {
  Serial.println("PMS5003 Data on Process");
  
  //digitalWrite(SLEEP_PIN,HIGH);
  //delay(20000);
  for(;;){
    pms5003.processDataOn(Serial1);
    PM1 = String(pms5003.getPM1(),DEC);
    PM2_5 = String(pms5003.getPM25(),DEC);
    PM10 = String(pms5003.getPM10(),DEC);
    if (PM1 !="-1" && PM2_5 !="-1" && PM10 != "-1"){
      break;
    }
  }
  
  
  postData ="uuid=" + uuid + "&PM1=" + PM1 + "&PM2_5=" + PM2_5 + "&PM10=" + PM10 + "&Temperature=" + temperature + "&Humadity=" + humadity;
  
  Serial.println("making POST request");
  client.post("/",content_type,postData);// the conntent in content_type is for doing POST method.

  statusCode = client.responseStatusCode(); // response code from server
  response = client.responseBody(); // messages that is responed by server

  // Serial Monitor output.(can be comment out when the data is sending to server correctly)
  Serial.print("Status Code: ");Serial.println(statusCode);
  Serial.print("Response: ");Serial.println(response);
  
  Serial.print("PM1:\t");Serial.println(PM1);
  Serial.print("PM2.5:\t");Serial.println(PM2_5);
  Serial.print("PM10:\t");Serial.println(PM10);
}


