#pragma once

#include <EEPROM.h>

class Config
{
public:
  Solenoid get_solenoid(int solenoid_number);
  void set_solenoid(Solenoid* solenoid, int solenoid_number);
  
private:
  Time get_time_from_eeprom(unsigned int* starting_address);
  void write_time_to_eeprom(const Time& time, unsigned int* starting_address);
    
};

Solenoid Config::get_solenoid(int solenoid_number)
{
 unsigned int address = sizeof(Solenoid) * solenoid_number;
 char open_pin = EEPROM.read(address);
 address += sizeof(open_pin);
 char close_pin = EEPROM.read(address);
 address += sizeof(close_pin);
 char days_of_week = EEPROM.read(address);
 address += sizeof(days_of_week);
  
 Time open_time = get_time_from_eeprom(&address);
 Time close_time = get_time_from_eeprom(&address);
  
 char label[LINE_LEN+1] = {0};
 for(int i = 0 ; i < LINE_LEN ; ++i, ++address)
 {
   label[i] = EEPROM.read(address);
 } 
  
  return Solenoid(open_pin, close_pin, days_of_week, open_time, close_time, label);
}

void Config::set_solenoid( Solenoid* solenoid, int solenoid_number )
{
  unsigned int address = sizeof(Solenoid) * solenoid_number;
  
  EEPROM.write(address, solenoid->get_open_pin());
  address += sizeof(solenoid->get_open_pin());
  EEPROM.write(address, solenoid->get_close_pin());
  address += sizeof(solenoid->get_close_pin());
  EEPROM.write(address, solenoid->get_days_of_week());
  address += sizeof(solenoid->get_days_of_week());
  
  write_time_to_eeprom(solenoid->get_open_time(), &address);
  write_time_to_eeprom(solenoid->get_close_time(), &address);
 
  char label[LINE_LEN+1] = {0};
  solenoid->get_label(label);
  for(int i = 0 ; i < LINE_LEN ; ++i, ++address)
  {
    EEPROM.write(address, label[i]);
  } 
  
}

void Config::write_time_to_eeprom(const Time& time, unsigned int* starting_address)
{
  EEPROM.write(*starting_address, time._hour);
  *starting_address += sizeof( time._hour);
  EEPROM.write(*starting_address, time._minute);
  *starting_address += sizeof( time._minute);
  EEPROM.write(*starting_address, time._second);
  *starting_address += sizeof( time._second);
  EEPROM.write(*starting_address, time._day);
  *starting_address += sizeof( time._day);
  EEPROM.write(*starting_address, time._date);
  *starting_address += sizeof( time._date);
  EEPROM.write(*starting_address, time._month);
  *starting_address += sizeof( time._month);
  EEPROM.write(*starting_address, time._year);
  *starting_address += sizeof( time._year);
}

Time Config::get_time_from_eeprom(unsigned int* starting_address)
{
  Time time;
  time._hour =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._hour );
  time._minute =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._minute );
  time._second =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._second );
  time._day =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._day );
  time._date =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._date );
  time._month =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._month );
  time._year =  EEPROM.read(*starting_address);
  *starting_address += sizeof( time._year );
  return time;
}
