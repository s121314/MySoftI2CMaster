#include "MySoftI2CM.h"
#include "Wire.h"

//ArduinoUNO to ArduinoUNO SoftwareI2C Sample

//Master Libary is 
//http://s2jp.com/2013/01/tiny10-i2c-master/
//I change PB0 to PB2 and  PB1 to PB3
//Because PB0 and PB1 has possiblity of TX, RX
//PIN  Map http://brittonkerin.com/cduino/pin_map.html
//SCL = PIN11
//SDA = PIN10

#define LED_PIN 13
int slaveAddr = 8;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  I2C_init();
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  //sendI2C();
  sendI2CTest(); //sucecess
  delay(1000);
  readI2CTest(); //success
  digitalWrite(LED_PIN, LOW);
  delay(300);
}

//Normal Test
byte x = 0;
void sendI2C()
{
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  x++;
}



void sendI2CTest()
{
  //basic format
  I2C_start();
  I2C_write( slaveAddr << 1); //write start address

  for (int i = 0; i < 2; i++)  I2C_clkWait();
  I2C_write(0);  //set register. I don't know detail case of Arduino case
  for (int i = 0; i < 2; i++)  I2C_clkWait();
  I2C_write(x);  //write data
  for (int i = 0; i < 2; i++)  I2C_clkWait();
  I2C_stop();
  x++;
}

void readI2CTest()
{
  //basic format
  //set read register
  I2C_start();
  I2C_write( slaveAddr << 1); //write start address
  I2C_write( 0x00); // set register. I don't know detail case of Arduino case
  I2C_stop();

  //Read Start
  I2C_start();
  I2C_write( 0x08 << 1 | 1); //read start address

  //wait for get correct data (important)
  for (int i = 0; i < 12; i++)
  {
    I2C_clkWait();
  }

  //read data
  int readCount = 5;
  for (int i = 0; i < readCount; i++)
  {
    byte b =  I2C_read(1);
    Serial.print((char)b);
  }
  Serial.println( I2C_read(0) ); //0 is stop read

  I2C_stop();
}


