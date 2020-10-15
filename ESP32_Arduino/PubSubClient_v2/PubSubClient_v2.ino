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
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));

  Serial.println("Serial Txd2 is on pin: "+String(TXD2));
  Serial.println("Serial Rxd2 is on pin: "+String(RXD2));

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

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
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte ind = 0; // Index into array; where to store the character

void loop() {
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  // long now = millis();
  // if (now - lastMsg > 5000) 
  // lastMsg = now;
  
  ind = 0;
  
  while (Serial2.available()) 
  {
//    Serial.print(char(Serial2.read()));
    
//    if(ind < 19) // One less than the size of the array
//        {
//            inChar = Serial2.read(); // Read a character
//            inData[ind] = inChar; // Store it
//            ind++; // Increment where to write next
//            inData[ind] = '\0'; // Null terminate the string
//        }
    if(ind < 19) // One less than the size of the array
        {
            inChar = Serial2.read(); // Read a character
            inData[ind] = inChar; // Store it
            ind++; // Increment where to write next
            inData[ind] = '\0'; // Null terminate the string
        }
        
    // // Temperature in Celsius
    // temperature = 98;

    
    // // Convert the value to a char array
    //     char tempString[16]=Serial2.read();
    // dtostrf(temperature, 1, 2, tempString);
    // Serial.print("Temperature: ");
    // Serial.println(tempString);
    client.publish("esp32/temperature", inData );
  }
}
