#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define CH_TEMP 1
#define FIELD_TEMP 1

// const char* ssid = "AntonIngeVibevej";
// const char* pass = "kodenerkode";

const char* ssid = "Telenor4788sne";
const char* pass = "Y2jSx3BYq";

int adcPin = A0;
int adcRaw = 0;
double voltage = 0;
double temp = 0;
double tempavg = 0;
uint16_t count = 0;
double readback = 0;



WiFiClient client;

unsigned long channelID = 2396833; //your TS channal
const char * writeAPIKey = "NFNJ7HJDLO7EJ5BA"; //your TS API
const char * readAPIKey = "705CUDM1OMAPKG03";
const char* server = "api.thingspeak.com";
const int postDelay = 20 * 1000; //post data every 20 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
}

float data; //measured data

void loop() {
  uint16_t statusCode = 0;
  if (count % 100 == 0)
  {
    adcRaw = analogRead(adcPin);
    voltage = adcRaw*3270/1024;
    temp = ((voltage-100)/10)-40;
    tempavg = 0.95*tempavg + 0.05*temp;
  }
  if (count % 2000 == 0)
  {
    Serial.print("Temperature is: ");
    Serial.print(tempavg);
    Serial.println(" °C");
    data = tempavg;
  }
  if (count % 20000 == 0) // 20 sec
  {
    Serial.print("Posting temperature: ");
    Serial.print(tempavg);
    Serial.println(" °C");
    ThingSpeak.begin(client);
    client.connect(server, 80); //connect(URL, Port)
    ThingSpeak.setField(CH_TEMP, data); //set data on the X graph
    ThingSpeak.writeFields(channelID, writeAPIKey);//post everything to TS
    client.stop();
  }
  if (count % 20000 == 0) // 10 sec
  {
    ThingSpeak.begin(client);
    client.connect(server, 80); //connect(URL, Port)
    //ThingSpeak.setField(CH_TEMP, data); //set data on the X graph
    //ThingSpeak.writeFields(channelID, writeAPIKey);//post everything to TS
    readback = ThingSpeak.readFloatField(channelID,FIELD_TEMP, readAPIKey);
    statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200)
    {
      Serial.print("Reading back temperature value: ");
      Serial.print(readback);
      Serial.println(" °C");
    }
    Serial.print("StatusCode: ");
    Serial.println(statusCode);

    client.stop();
  }
  count++;
  delay(1); // tick
}








