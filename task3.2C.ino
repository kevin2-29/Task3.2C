#include <WiFiNINA.h>

int ldrpin = 7;

//please enter your sensitive data in the Secret tab
char ssid[] = "iPhone";
char pass[] = "lucky3400";

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/kevin/with/key/hU9NwHfiHuhVAoIzM4xXZhWKLAu8-L9is4QbOsji5S-"; // change your EVENT-NAME and YOUR-KEY
String queryString = "";

int ldrvalue = 0;
bool change = false;
bool same = false;

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);

  pinMode(ldrpin, INPUT);

  Serial.begin(9600);
  while (!Serial);

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  }
  else {// if not connected:
    Serial.println("Connection failed");
  }
}

void loop() {

    ldrvalue = digitalRead(ldrpin);

    if((ldrvalue == 1 && digitalRead(ldrpin) == 0) || (ldrvalue == 0 && digitalRead(ldrpin) == 1))
    {
	    change = true;
    }
    else
    {
	    change = false;
    }

    if(change) {
    queryString = "?value1=" + String(digitalRead(ldrpin));

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header


    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
    change = false;
   
    //Adding a line to indicate that the email has been sent successfully:
    Serial.println("Email sent successfully to the user");
  }
}