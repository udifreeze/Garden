#pragma once

#include "Time.h"

//Based on the DS3231

#include <Wire.h>

const int HOURS_24_BIT  = 0b00111111;
const int EOSC_BIT      = 0b01111111;
const char RTC_ADDRESS = 0x68;

class RTC
{
  public:
    RTC();
    void init();
    Time get_time();
    void set_time(Time& time);

  private:
    void set_24_hours();
    void set_battery_on();
       
    char read_address( int address );
    char write_address( int address, char data );
    char bcd_to_dec( char val );
    char dec_to_bcd( char val );
    
};

#include "RTC.h"

RTC::RTC()
{ 
  #define I2C_MASTER
  Wire.begin(I2C_MASTER);
  //init();
}

void RTC::init()
{
  delay(1000);
  set_24_hours();
  set_battery_on();
}

char RTC::bcd_to_dec( char val )
{
  return ( (val/16*10) + (val%16) );
}

char RTC::dec_to_bcd( char val )
{
  return ( (val/10*16) + (val%10) );
}

char RTC::read_address( int address )
{  
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 1);
  Wire.endTransmission();
  char ret = Wire.read(); 
  return ret;
}

char RTC::write_address( int address, char data )
{  
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}


Time RTC::get_time()
{
 
  Wire.beginTransmission(RTC_ADDRESS);
  
  Wire.write(0);  
  Wire.requestFrom(RTC_ADDRESS, 7);
  byte seconds = bcd_to_dec(Wire.read());
  byte minutes = bcd_to_dec(Wire.read());
  byte hours = bcd_to_dec(Wire.read());
  byte day = bcd_to_dec(Wire.read());
  byte date = bcd_to_dec(Wire.read());
  byte month = bcd_to_dec(Wire.read());
  byte year = bcd_to_dec(Wire.read());
  Wire.endTransmission();
  
  return Time(hours, minutes, seconds, day, date, month, year);

}

void RTC::set_time( Time& time )
{
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0);

  Wire.write( dec_to_bcd(time._second) );
  Wire.write( dec_to_bcd(time._minute) );
  Wire.write( dec_to_bcd(time._hour) & HOURS_24_BIT );
  Wire.write( dec_to_bcd(0) );
  Wire.write( dec_to_bcd(time._date) );
  Wire.write( dec_to_bcd(time._month) );
  Wire.write( dec_to_bcd(time._year) );
  Wire.endTransmission();
}

void RTC::set_24_hours()
{
  const int RTC_HOURS_ADDRESS = 0x2;
  char hours = read_address(RTC_HOURS_ADDRESS);  
  write_address( RTC_HOURS_ADDRESS, hours & HOURS_24_BIT );
}

void RTC::set_battery_on()
{
  const int RTC_CONTROL_ADDRESS = 0xE;
  char control = read_address(RTC_CONTROL_ADDRESS);  
  write_address( RTC_CONTROL_ADDRESS, control & EOSC_BIT );
}
