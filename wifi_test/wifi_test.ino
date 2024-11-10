#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

#define SIZE 60

Adafruit_NeoPixel strip(SIZE, 13, NEO_RGB + NEO_KHZ800);

const char *ssid = "stellarcielo-g";
const char *password = "tensor_pa";

WiFiServer server(80);

String header;

bool bool_strip = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  strip.begin();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();

  if(client){
    Serial.println("New Client.");
    String currentLine = "";

    while(client.connected()){
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;

        if(c == '\n'){
          if(currentLine.length() == 0){
            client.println("Http/1.1 200 OK");
            client.println("Content-type:text/html; charset = utf-8;");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /on") >= 0){
              bool_strip = true;
              Serial.println("ON");
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(50, 50, 50));
              }
              strip.show();
            }
            else if(header.indexOf("GET /off") >= 0){
              bool_strip = false;
              Serial.println("OFF");
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(0, 0, 0));
              }
              strip.show();
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name = \"viewport\" content = \"width = device-width, initial-scale = 1\">");
            client.println("<link rel = \"icon\" href = \"data:,\">");

            client.println("<title>ESP32_IO_Test</title>");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #5555FF; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #FF5555;}</style></head>");

            client.println("<body><h1>ESP32_Test</h1>");

            if(bool_strip == false){
              client.println("<p>strip is OFF</p>");
              client.println("<p><a href = \"on\"><button class = \"button\">change on?</button></a></p>");
            }
            else{
              client.println("<p>strip is ON</p>");
              client.println("<p><a href = \"off\"><button class = \"button button2\">change off?</button></a></p>");
            }

            client.println("</body></html>");

            client.println();

            break;
          }
          else{
            currentLine = "";
          }
        }
        else if(c != '\r'){
          currentLine += c;
        }
      }
    }
    header = "";

    client.stop();
    Serial.println("Client disconnected.");
    Serial.println();
  }
}
