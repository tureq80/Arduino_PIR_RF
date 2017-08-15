/*
 * PIR sensor tester
 */
#include <RCSwitch.h> 
RCSwitch mySwitch = RCSwitch();

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  
  mySwitch.enableTransmit(10);  // declare PIN RF modul
 
  Serial.begin(57600);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("on");
      // We only want to print on the output change, not state
      pirState = HIGH;
      mySwitch.sendTriState("FFF11FF0FFF0");
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      
      Serial.println("OFF");
      // We only want to print on the output change, not state
      pirState = LOW;
      mySwitch.sendTriState("FFF11FF0FF0F");
    }
  }
}
