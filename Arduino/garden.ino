//Garden V1.0 

#include <EEPROM.h>
#include <Wire.h>
#include <SoftwareSerial.h>


#include "RTC.h"
#include "Time.h"
#include "Keypad.h"
#include "Solenoid.h"
#include "Config.h"
#include "Temperature.h"
#include "LCD.h"
#include "Screens.h"

const unsigned int NUMBER_OF_SOLENOIDS = 2;

RTC _rtc;
Keypad _keypad;
Config _config;
Temperature _temperature;
LCD _LCD;

Solenoid* _solenoids[NUMBER_OF_SOLENOIDS];

void close_solenoids()
{
  for(int i = 0 ; i < NUMBER_OF_SOLENOIDS ; ++i)
    _solenoids[i]->close_solenoid();
}

void init_open_close_pins()
{
    _solenoids[0]->set_open_pin(8);
    _solenoids[0]->set_close_pin(9);
    _solenoids[1]->set_open_pin(10);
    _solenoids[1]->set_close_pin(11);
}

void init_hardware()
{
    init_open_close_pins();
      
    for( int i = 0 ; i < NUMBER_OF_SOLENOIDS ; ++i )
    {        
      pinMode( _solenoids[i]->get_open_pin(), OUTPUT );
      digitalWrite(_solenoids[i]->get_open_pin(), LOW);
      pinMode( _solenoids[i]->get_close_pin(), OUTPUT );
      digitalWrite(_solenoids[i]->get_close_pin(), LOW);
    }
    
    close_solenoids();
}


boolean is_time_to_open( Solenoid& solenoid )
{
    Time now = _rtc.get_time();
  
  if( ( solenoid.get_open_time()._hour == now._hour ) && 
    ( solenoid.get_open_time()._minute == now._minute ) &&
    ( 1 == bitRead(solenoid.get_days_of_week(), now._day ) ) &&
    ( !solenoid.is_open() ) )
    {
      return true;
    }
    
    return false;
}

boolean is_time_to_close( Solenoid& solenoid )
{
  Time now = _rtc.get_time();
  
 if( ( solenoid.get_close_time()._minute == now._minute ) && 
     ( solenoid.get_close_time()._minute == now._minute ) &&
     ( 1 == bitRead(solenoid.get_days_of_week(), now._day ) ) &&
     ( solenoid.is_open() ) )
    {
      return true;
    }
    
    return false;
}

void setup()
{
  Serial.begin(9600); 
  
  for( int i = 0 ; i < NUMBER_OF_SOLENOIDS ; ++i )
  {
    Solenoid* solenoid = new Solenoid(_config.get_solenoid(i));
    _solenoids[i] = solenoid;
  }
  init_hardware();
  
  Serial.println("Done init");
}

void idle_menu()
{    
  switch(_keypad.get_key())
  {
    case 'A':
      show_set_rtc_screen();
    break;
    
    case 'B':
      show_set_selos_screen();
    break;
    
    case 'C':
      show_configured_solenoids();
    break;
    
    case 'D':

    break;
    
    default:
    break;
  };
}

void loop()
{    
  show_idle_screen();
  idle_menu();
  
  for(int i = 0 ; i < NUMBER_OF_SOLENOIDS ; ++i)
  {
    if( is_time_to_open(*_solenoids[i]) )
      _solenoids[i]->open_solenoid();
      
     if( is_time_to_close(*_solenoids[i]) )
       _solenoids[i]->close_solenoid();
       
     if(_solenoids[i]->is_open())
     {
       char label[LINE_LEN+1];
       //_solenoids[i]->get_label(label);
       char selo[3] = {0};
       strcpy(selo, "S");
       itoa(i,&selo[1],10);
       show_selo_open_screen(selo);
     }
  }
}


