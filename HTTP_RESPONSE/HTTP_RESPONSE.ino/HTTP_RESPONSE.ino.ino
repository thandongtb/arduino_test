#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid = "Tabbu iPhone";
const char* password = "toan25251325";
const char* api_key = "f3f19dd-fc7593a";

String url = strcat("http://ppowertech.vn/api/v1/channel-detail/", api_key);

void get_data() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    
    Serial.println();
    Serial.println(url);
    http.begin(url);
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println();
      Serial.println(payload);
      // Parsing
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(payload);
  
      // Parameters
      int code = root["code"]; // 1
      int element_id = 0;
      String element_name_id = "";
      const char* message = root["message"]; // Message

      for (JsonObject::iterator it=root.begin(); it!=root.end(); ++it)
      {
          if (!strcmp(it->key, "elements"))
          {
              int tmp_element_id = it->value[0]["id"];
              Serial.println(tmp_element_id);
              String tmp_name_id = it->value[0]["name_id"];
              Serial.println(tmp_name_id);
              if (tmp_element_id != 0){
                  
                  element_id = tmp_element_id;
                  element_name_id = tmp_name_id;
                  
              }
              // ...
          }
      }

      // Output to serial monitor
      Serial.print("Code:");
      Serial.println(code);
      Serial.print("Message:");
      Serial.println(message);
      Serial.print("Element ID:");
      Serial.println(element_id);
      Serial.print("Element Name:");
      Serial.println(element_name_id);
      
//      Serial.print("Element ID:");
//      Serial.println(element_id);
    }
    http.end();   //Close connection
  }  
}

void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");
  }

  get_data();
 
}

void loop() {
  
}
