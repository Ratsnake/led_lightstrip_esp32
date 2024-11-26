#include <Adafruit_NeoPixel.h>
#include <WiFi.h>

#define SIZE 60

Adafruit_NeoPixel strip(SIZE, 13, NEO_RGB + NEO_KHZ800);

const char *ssid = "stellarcielo-g";
const char *password = "tensor_pa";

WiFiServer server(80);

String header;

bool bool_strip = false;
bool worning =false;

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
            else if(header.indexOf("GET /brightness=") >= 0){
              unsigned short brightness = header.substring(16).toInt();
              
              if(0 <= brightness && brightness <= 100){

                worning = false;
                Serial.print("Brightness set : ");
                Serial.println(brightness);

                for(int i = 0; i < SIZE; i++){
                  strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
                }
                strip.show();
              }
              else{
                Serial.println("Value is too large.");
                worning = true;
              }

              
            }
            else if(header.indexOf("GET /blue") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(0, 0, 50));
              }
              strip.show();
            }
            else if(header.indexOf("GET /red") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(0, 50, 0));
              }
              strip.show();
            }
            else if(header.indexOf("GET /green") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(50, 0, 0));
              }
              strip.show();
            }
            else if(header.indexOf("GET /purple") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(0, 30, 30));
              }
              strip.show();
            }
            else if(header.indexOf("GET /yellow") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(30, 30, 0));
              }
              strip.show();
            }
            else if(header.indexOf("GET /cyan") >= 0){
              for(int i = 0; i < SIZE; i++){
                strip.setPixelColor(i, strip.Color(30, 0, 30));
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
            client.println(".button2 {background-color: #FF5555;}");

            client.println(".container { max-width: 500px; max-width: 500px; padding: 20px; font-family: sans-serif;}");
            client.println(".slider-group { margin-bottom: 30px; }");
            client.println("input[type=\"range\"] { -webkit-appearance: none; width: 100%; background: transparent; }");
            client.println("input[type=\"range\"]::-webkit-slider-runnable-track { width: 100%; height: 8px; background: #ddd; border-radius: 4px; cursor: pointer; }");
            client.println("input[type=\"range\"]::-webkit-slider-thumb { -webkit-appearance: none; height: 20px; width: 20px; border-radius: 50%; background: #007bff; cursor: pointer; margin-top: -6px; transition: background 0.2s; }");
            client.println(".value-display { margin: 10px 0; font-size: 16px; }");
            client.println(".send-link { display: inline-block; padding: 10px 20px; background-color: #007bff; color: white; text-decoration: none; border-radius: 4px; margin-top: 10px;}");
            client.println(".send-link:hover { background-color: #0056b3}");

            client.println("</style></head>");

            client.println("<body><h1>ESP32_Test</h1>");

            if(bool_strip == false){
              client.println("<p>strip is OFF</p>");
              client.println("<p><a href = \"on\"><button class = \"button\">change on?</button></a></p>");
            }
            else{
              client.println("<p>strip is ON</p>");
              if(worning == true){
                client.println("<p>value error!</p>");
              }
              client.println("<p><a href = \"off\"><button class = \"button button2\">change off?</button></a></p>");
              client.println("<div class=\"container\"><div class=\"slider-group\"><div class=\"value-display\">brightness:<span id=\"currentValue\">50</span></div><input type=\"range\" id=\"slider\" min=\"0\" max=\"100\" value=\"50\" oninput=\"updateValue()\"><div><a href=\"brightness=50\" id = \"sendLink\" class = \"send-link\">send data</a></div></div>");
            }

            client.println("<script>function updateValue() { const slider = document.getElementById('slider'); const value = slider.value; const link = document.getElementById('sendLink'); const display = document.getElementById('currentValue'); display.textContent = value; link.href = `brightness=${value}`; }</script>");

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
