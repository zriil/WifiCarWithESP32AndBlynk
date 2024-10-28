#define BLYNK_TEMPLATE_ID "TMPL6ZN0QdfoU" //Blynk Template ID
#define BLYNK_TEMPLATE_NAME "Wifi Car"    //Blynk Template Name

#define BLYNK_PRINT Serial
#include <WiFi.h>               // Library WiFi untuk ESP32
#include <BlynkSimpleEsp32.h>  // Library Blynk untuk ESP32

// Motor PINs (sesuaikan dengan GPIO ESP32)
#define ENA 18    // Pin Enable untuk Motor A
#define IN1 2     // Pin Input 1 untuk Motor A
#define IN2 4     // Pin Input 2 untuk Motor A
#define IN3 16    // Pin Input 1 untuk Motor B
#define IN4 17    // Pin Input 2 untuk Motor B
#define ENB 5     // Pin Enable untuk Motor B
// int siren = 12;  // Pin Enable untuk Siren

// Variabel untuk kontrol arah motor
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed = 255;  // Nilai default kecepatan motor (0 - 255)

char auth[] = "HeR-Ws1udySY-CTBeywQ6yQ8SGHp63hl"; // Masukkan Blynk Auth Token
char ssid[] = "NS";                           // Masukkan SSID WiFi
char pass[] = "niken123";                    // Masukkan Password WiFi

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}

void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
