#pragma once

#include <Wire.h>

const char TEMPERATURE_ADDRESS = 0x27;
const char TEMPERATURE_REGISTER = 0;

class Temperature
{
  public:
    Temperature();
    
  public:
    int get_temp();
    int get_humidity();
};

Temperature::Temperature()
{
  #define I2C_MASTER
  Wire.begin(I2C_MASTER);
}

int Temperature::get_temp()
{
  Wire.beginTransmission( TEMPERATURE_ADDRESS );  
  Wire.endTransmission();
  delay(100);
  
  Wire.requestFrom(TEMPERATURE_ADDRESS, 4 );
  byte H_MSB = Wire.read();
  byte H_LSB = Wire.read();
  byte T_MSB = Wire.read();
  byte T_LSB = Wire.read();
  Wire.endTransmission();
   
  unsigned int humidity = (((unsigned int)H_MSB) << 8) | H_LSB;
  
  long temperature = 0;
  temperature = H_MSB << 8;
  temperature = temperature | H_LSB;    
  temperature = temperature * 165;  
  temperature = temperature / 16382;
  temperature = temperature - 40;  
  
  return temperature;
}


int Temperature::get_humidity()
{
  Wire.beginTransmission( TEMPERATURE_ADDRESS );  
  Wire.endTransmission();
  delay(100);
  
  Wire.requestFrom(TEMPERATURE_ADDRESS, 4 );
  byte H_MSB = Wire.read();
  byte H_LSB = Wire.read();
  byte T_MSB = Wire.read();
  byte T_LSB = Wire.read();
  Wire.endTransmission();
   
  long humidity = (((unsigned int)H_MSB) << 8) | H_LSB;
  humidity = humidity * 100;
  humidity = humidity / 16382;
  
  return humidity;
}
