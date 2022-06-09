

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//********************************************************************

#define ENA   14          // Enable/sag motor hizi        GPIO14(D5)
#define ENB   12          // Enable/sol motor hizi         GPIO12(D6)
#define IN_1  15          // L298N in1 sag motor           GPIO15(D8)
#define IN_2  13          // L298N in2 sag motor          GPIO13(D7)
#define IN_3  2           // L298N in3 sol motor            GPIO2(D4)
#define IN_4  0  
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;
char command;
//**********************************************************************
// Agımıza uygun degerlerin yuklenmesi

const char* ssid     = "CIHANHPG5 2316"; // wifi ag adi
const char* password = "7o652E@5"; // wifi ag parolasi
const char* mqtt_server = "raspberrypi.local";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];



void setup_wifi() {
  

  delay(10);
  // Ag baglanti ayarlarina basliyoruz.
  Serial.println();
  Serial.print("Baglaniyor ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi baglanildi");
  Serial.println("IP addres: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mesaj dondu [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if((String)topic=="akilliarac")
  {

    
  command=(char)payload[0];

      if (command =='F')  goAhead();
      else if (command == 'B') goBack();        
      else if (command == 'L') goLeft();
      else if (command == 'R') goRight();
      else if (command == 'I') goAheadRight();
      else if (command == 'G') goAheadLeft();
      else if (command == 'J') goBackRight();
      else if (command == 'H') goBackLeft();
      else if (command == '0')
      {       
        client.publish("arachiz","400");
        speedCar = 400;
      }
      else if (command == '1'){
        client.publish("arachiz","470");
        speedCar = 470;
      }
      else if (command == '2'){
        client.publish("arachiz","540");
        speedCar = 540;
      }
      else if (command == '3'){
        client.publish("arachiz","610");
        speedCar = 610;
      }
      else if (command == '4'){
        client.publish("arachiz","680");
        speedCar = 680;
      }
      else if (command == '5'){
        client.publish("arachiz","750");
        speedCar = 750;
      }
      else if (command == '6'){
        client.publish("arachiz","820");
        speedCar = 820;
      }
      else if (command == '7'){
        client.publish("arachiz","890");
        speedCar = 890;
      }
      else if (command == '8'){
        client.publish("arachiz","960");
        speedCar = 960;
      }
      else if (command == '9'){
        client.publish("arachiz","1023");
        speedCar = 1023;
      }
      else if (command == 'S'){
        client.publish("arachiz","0");
        stopRobot();
      }

    
 /*   if((char)payload[0]=='r')
        hangisi=kirmizi;
    else if((char)payload[0]=='g')
        hangisi=yesil;
    else if((char)payload[0]=='b')
        hangisi=mavi;
    Serial.println(payload[1]);
    
    if((char)payload[1]=='1')
      digitalWrite(hangisi, HIGH);
     else
      digitalWrite(hangisi, LOW);
      */
  }


}

void reconnect() {
  // tekrar baglanana kadar bekliyoruz
  while (!client.connected()) {
    Serial.print("MQTT dogrulamasi saglaniyor...");
    // rasgele kullanici id 
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // baglanti dogrulamasi
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // bir kez baglandiktan sonra yayinlanacak mesaj...
      client.publish("outTopic", "selam");
      
      // ... ve abonelik
      client.subscribe("inTopic");
      client.subscribe("espLed");
      client.subscribe("akilliarac");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" 5 saniye sonra tekrar deneyiniz.");
      //5 saniye bekleniyor
      delay(5000);
    }
  }
}

void setup() {
  
  pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
   
   
  }
}
