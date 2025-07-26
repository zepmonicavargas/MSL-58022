#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 // Define the Slave Select Pin (SS)
#define RST_PIN 9 // Define the Reset Pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance 

#define LED_PIN 4 // Define the LED Pin
#define GREEN_LED_PIN 5 // Define another LED Pin
#define BUZZER_PIN 6 // Define the Buzzer Pin

void setup() {
  Serial.begin(9600); // Initialize serial communication 
  SPI.begin(); // Initialize SPI bus
  mfrc522.PCD_Init(); // Initialize MFRC522 RFID reader 

  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  pinMode(GREEN_LED_PIN, OUTPUT); // Set another LED pin as output
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
}

void loop() {
// Look for new RFID cards
if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) { 
  // If a card is present, print UID to serial monitor
  Serial.print ("Card UID: ");
  String tagID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
      if (mfrc522.uid.uidByte[i] < 0x10) {
        tagID += "0";
      }
      tagID += String(mfrc522.uid.uidByte[i], HEX);
  }
  tagID.toUpperCase();
  Serial.println(tagID);

  // Check if the tag ID matches a predefined value
  if (tagID == "3CFCB389") {
    // If tag matches, turn on LED
    digitalWrite(LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH); // turn off the green led
    noTone(BUZZER_PIN);
  } else {
    // If tag doesn't match, turn off LED
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW); // turn on the green led
    tone(BUZZER_PIN, 2000); // Turn on the buzzer at 1000 Hz
    delay(500); // Wait for 0.5 seconds
    noTone(BUZZER_PIN);
  }
  delay(1000); // Delay to prevent reading multiple times
 }
}
