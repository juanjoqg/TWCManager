#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "vodafone6352";
const char* password = "XMPTVVKFUMBWDF";
ESP8266WebServer server(80);

WiFiClient client;

String cadena;
String potencia;


void setup() {
   Serial.begin(9600);
   delay(100);


   //connect to your local wi-fi network
   WiFi.begin(ssid, password);

   //check wi-fi is connected to wi-fi network
   while (WiFi.status() != WL_CONNECTED) {
     delay(1000);
    }

   Serial.print("Got IP: "); Serial.println(WiFi.localIP());
   server.on("/", handle_OnConnect);
   server.onNotFound(handle_NotFound);

   server.begin();


}

void loop() {

   while (Serial.available()) {
    cadena = Serial.readStringUntil('\n');
   }
   potencia = cadena; 
   server.handleClient();
  
    delay(1000); 

}

void handle_OnConnect() {

   server.send(200, "text/html", SendHTML());
}

void handle_NotFound(){
   server.send(404, "text/plain", "Not found");
}

String SendHTML(){
   String ptr = "<!DOCTYPE html> <html>\n";
   ptr +="<body>\n";
   ptr +=potencia;
   ptr +="</body>\n";
   ptr +="</html>\n";
   return ptr;
}
