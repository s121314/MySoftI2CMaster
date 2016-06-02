#include <Wire.h>

void setup()
{

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

bool ss = false;
void receiveEvent(int howMany)
{

  /*
    while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    }
  */
  for (int i = 0; i < howMany; i++)
  {
    int x = Wire.read();    // receive byte as an integer
    Serial.println(x);         // prin
  }
}

void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
