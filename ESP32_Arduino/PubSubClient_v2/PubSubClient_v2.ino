/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>

#define RXD2 5
#define TXD2 4

// Replace the next variables with your SSID/Password combination
const char* ssid = "shivam";
const char* password = "12345678";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "192.168.43.26";
//const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

float temperature = 0;

// LED Pin
const int ledPin = 4;

void setup() 
{
 // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  Serial2.begin(921600, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

  Serial.println("Serial Txd2 is on pin: "+String(TXD2));
  Serial.println("Serial Rxd2 is on pin: "+String(RXD2));

  setup_wifi();
  client.setServer(mqtt_server, 1883);
//  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) 
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe commented by Manoj
      // client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

int var1 = 4900;
int var2 = 9216;
int var3 = 25600;
int var4 = 50176;
int var5 = 129600;
int var6 = 193600;
int var7 = 262144;
int var8 = 360000;
int var9 = 480000;
int var10 = 560000;
int var11 = 640000;
int var12 = 720000;
int var13 = 810000;
int var14 = 880000;
int var15 = 960000;


char inData[60000]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte ind = 0; // Index into array; where to store the character
byte test_flag = 0;// Raise test flag whenever serial data is received

void loop() {
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop(); 
  ind = 0;

  test_flag = 0;
  while (Serial2.available()) 
  {

    if(ind < 60000) // One less than the size of the array
        {
            inChar = Serial2.read(); // Read a character
            inData[ind] = inChar; // Store it
            ind++; // Increment where to write next
            inData[ind] = '\0'; // Null terminate the string
        }
    test_flag = 1;  
  }      
  if(test_flag == 1)
  {
    client.publish("esp32/temperature", inData );
  }
 
}
