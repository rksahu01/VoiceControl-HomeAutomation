#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char *ssid = "Your_SSID";
const char *password = "Your_PASSWORD";

// MQTT broker details (use your laptop's IP)
const char *mqtt_server = "192.168.1.100"; // Replace with your laptop's IP
const char *mqtt_topic = "home/devices";

WiFiClient espClient;
PubSubClient client(espClient);

// Pins for devices
const int hallLightPin = 12;
const int kitchenLightPin = 13;
const int bedroomLightPin = 14;
const int fanPin = 2; // Control a DC motor (Fan)

// Function to handle MQTT messages
void callback(char *topic, byte *payload, unsigned int length)
{
    String command = "";
    for (int i = 0; i < length; i++)
    {
        command += (char)payload[i];
    }
    command.trim();
    Serial.print("Received command: ");
    Serial.println(command);

    // Control devices based on received command
    if (command == "on hall")
    {
        digitalWrite(hallLightPin, HIGH);
        Serial.println("Hall Light turned ON");
    }
    else if (command == "off hall")
    {
        digitalWrite(hallLightPin, LOW);
        Serial.println("Hall Light turned OFF");
    }
    else if (command == "on kitchen")
    {
        digitalWrite(kitchenLightPin, HIGH);
        Serial.println("Kitchen Light turned ON");
    }
    else if (command == "off kitchen")
    {
        digitalWrite(kitchenLightPin, LOW);
        Serial.println("Kitchen Light turned OFF");
    }
    else if (command == "on bedroom")
    {
        digitalWrite(bedroomLightPin, HIGH);
        Serial.println("Bedroom Light turned ON");
    }
    else if (command == "off bedroom")
    {
        digitalWrite(bedroomLightPin, LOW);
        Serial.println("Bedroom Light turned OFF");
    }
    else if (command == "on fan")
    {
        digitalWrite(fanPin, HIGH);
        Serial.println("Fan turned ON");
    }
    else if (command == "off fan")
    {
        digitalWrite(fanPin, LOW);
        Serial.println("Fan turned OFF");
    }
}

void setup()
{
    Serial.begin(115200);

    // Setup device pins
    pinMode(hallLightPin, OUTPUT);
    pinMode(kitchenLightPin, OUTPUT);
    pinMode(bedroomLightPin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");

    // Connect to MQTT broker
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    // Reconnect if necessary
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP32Client"))
        {
            Serial.println("connected");
            client.subscribe(mqtt_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void loop()
{
    client.loop();
}
