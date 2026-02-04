#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include "RTClib.h"


const char* ssid = "Praga";
const char* password = "pragathi20";


const char* firebaseHost = "https://rfid-44115-default-rtdb.firebaseio.com/";


#define RST_PIN 4
#define SS_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);


RTC_DS1307 rtc;


#include <map>
std::map<String, String> uidToName = {
  { "3D-1B-49-06", "Ragavi" },  
  { "4B-4D-10-05", "Priya" },
  { "2B-DB-E8-00", "Sahana" },
  { "26-5D-8B-E4", "Praga" }
};

std::map<String, bool> insideMap; // UID → inside status


String formatTime(DateTime now) {
  char buf[20];
  sprintf(buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  return String(buf);
}
String formatDate(DateTime now) {
  char buf[15];
  sprintf(buf, "%04d-%02d-%02d", now.year(), now.month(), now.day());
  return String(buf);
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  // WiFi connect
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Init RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("RTC is not running, setting time to compile time...");
    rtc.adjust(DateTime(F(_DATE), F(TIME_))); // set to compile time
  }

  Serial.println("RTC ready. Place your card...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Make UID string
  String uidStr = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (uidStr.length() > 0) uidStr += "-";
    if (mfrc522.uid.uidByte[i] < 0x10) uidStr += "0";
    uidStr += String(mfrc522.uid.uidByte[i], HEX);
  }
  uidStr.toUpperCase();

  // Check if UID is known
  if (!uidToName.count(uidStr)) {
    Serial.print("Unknown card detected: ");
    Serial.println(uidStr);
    mfrc522.PICC_HaltA();
    delay(1000);
    return;
  }

  String personName = uidToName[uidStr];

  // Get current RTC time
  DateTime now = rtc.now();
  String dateStr = formatDate(now);
  String timeStr = formatTime(now);

  // Determine Entry/Exit
  bool isEntry = !insideMap[uidStr];  // if not inside → entry
  String status = isEntry ? "ENTRY" : "EXIT";

 
  if (isEntry && now.hour() >= 9) {
    Serial.println("Denied: Late entry");
    mfrc522.PICC_HaltA();
    return;
  }
  if (!isEntry && now.hour() >=  16) {
    Serial.println("Denied: Exit time exceeded");
    mfrc522.PICC_HaltA();
    return;
  }

  // Update state
  insideMap[uidStr] = isEntry;

  // Build JSON payload
  String payload = "{";
  payload += "\"uid\":\"" + uidStr + "\",";
  payload += "\"name\":\"" + personName + "\",";
  payload += "\"date\":\"" + dateStr + "\",";
  payload += "\"" + status + "\":\"" + timeStr + "\"";
  payload += "}";

  Serial.println("Payload: " + payload);

  // Send to Firebase
  String url = String(firebaseHost) + "/attendance/" + dateStr + "/" + uidStr + ".json";
  if (strlen(authToken) > 0) url += "?auth=" + String(authToken);

  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.PUT(payload);

  if (httpCode > 0) {
    Serial.printf("Firebase HTTP %d\n", httpCode);
    Serial.println("Response: " + http.getString());
  } else {
    Serial.printf("Error sending to Firebase: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

  delay(1500);
  mfrc522.PICC_HaltA();
}