#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h> // https://github.com/ArtronShop/IOXhop_FirebaseESP32?tab=readme-ov-file
#include <ArduinoJson.h>

#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"
#define FIREBASE_HOST "host"
#define FIREBASE_AUTH "auth"

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Conectando ao wifi");    
  while (WiFi.status() != WL_CONNECTED)  
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

int i = 0;
void loop() {
  // pegando valores do firebase
  Serial.println();
  Serial.print("get PAS: ");
  Serial.print(Firebase.getInt("/PAS"));
  delay(1000);


  // setando valores no firebase
  Serial.print("set PAS: ");
  Firebase.setInt("/PAS", i);
  if(Firebase.failed()) {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
  } else {
    Serial.println("Updated ");      
  }
  delay(1000);

  i++;
}
