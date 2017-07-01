#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

ESP8266WebServer server(80);

void initWifi() {
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/color", handleColor);

  server.begin();
  Serial.println("HTTP server started");
}

void handleClient() {
  server.handleClient();
}

void handleColor() {
  if (mode != 3) mode = 3;

  if(server.arg("r") != "") desiredColor[R] = server.arg("r").toInt() * 4;
  if(server.arg("g") != "") desiredColor[G] = server.arg("g").toInt() * 4;
  if(server.arg("b") != "") desiredColor[B] = server.arg("b").toInt() * 4;

  server.send(200, "text/plain", "");
}

void handleRoot() {
  String message = "<html>\
  <head>\
    <script type='text/javascript' src='https://cdn.rawgit.com/DavidDurman/FlexiColorPicker/master/colorpicker.min.js'></script>\
    <link rel='stylesheet' type='text/css' href='https://cdn.rawgit.com/DavidDurman/FlexiColorPicker/master/themes.css' />\
  </head>\
  <body>\
    <div id='color-picker' class='cp-default'></div>\
    <script type='text/javascript'>\
      var xhr = new XMLHttpRequest();\
      ColorPicker(\
        document.getElementById('color-picker'),\
        function(hex, hsv, rgb) {\
          xhr.open('GET', 'http://192.168.31.217/color?r=' + rgb.r + '&g=' + rgb.g + '&b=' + rgb.b);\
          xhr.send();\
        });\
    </script>\
    <div>\
      <a href='?mode=0'>Mood</a> |\
      <a href='?mode=1'>Waves</a> |\
      <a href='?mode=2'>White</a>\
    </div>\
  </body>\
</html>";

  if(server.arg("mode") != "") {
    mode = server.arg("mode").toInt();
    Serial.println("New mode: " + (String) mode);
  }

  if (DEBUG) {
    for (int i = 0; i < server.args(); i++) {
      message += "Arg" + (String)i + " -> ";   //Include the current iteration value
      message += server.argName(i) + ": ";     //Get the name of the parameter
      message += server.arg(i) + "\n";              //Get the value of the parameter
    }

    message += "Desired color: " + (String)desiredColor[R] + " " +
                                   (String)desiredColor[G] + " " +
                                   (String)desiredColor[B] + "\n";
  }

  server.send(200, "text/html", message);
}
