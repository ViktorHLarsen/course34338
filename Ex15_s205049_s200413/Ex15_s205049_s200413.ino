#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define CH_TEMP 1
#define CH_SPL 2

const char* ssid = "AntonIngeVibevej";
const char* pass = "kodenerkode";

int adcPin = A0;
int adcRaw = 0;
double voltage = 0;
double temp = 0;

WiFiClient client;

unsigned long channelID = 2396833; //your TS channal
const char * APIKey = "NFNJ7HJDLO7EJ5BA"; //your TS API
const char* server = "api.thingspeak.com";
const int postDelay = 5 * 1000; //post data every 20 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
}

float data; //measured data

void loop() {
  adcRaw = analogRead(adcPin);
  voltage = adcRaw*3270/1024;
  temp = ((voltage-100)/10)-40;
  data = temp;
  Serial.print("Temperature is: ");
  Serial.print(temp);
  Serial.println(" °C");
  ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  ThingSpeak.setField(CH_TEMP, data); //set data on the X graph
  ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
  client.stop();
  delay(postDelay); //wait and then post again
}








