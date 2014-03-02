#pragma once

#include "Time.h"

const unsigned int MAX_NUMBER_OF_DIG_PINS = 13;
#define LINE_LEN 10

class Solenoid
{
  public:
    Solenoid( int open_pin, int close_pin, int days_of_week, const Time& open_time, const Time& close_time, const char* label );
    
    void close_solenoid();
    void open_solenoid();
    void print();
    boolean validate();
    boolean is_open();
    
    void set_label(const char* label);
    void get_label(char* label);
    
    char get_open_pin();
    void set_open_pin(char pin);
    
    char get_close_pin();
    void set_close_pin(char pin);
    
    char get_days_of_week();
    void set_days_of_week(char days_of_week);
    
    Time get_close_time();
    void set_close_time(Time& time);
    
    Time get_open_time();
    void set_open_time(Time& time);

    
  private:
    char _open_pin;
    char _close_pin;
    char _days_of_week;
    Time _open_time;
    Time _close_time;
    char _is_open;
    char _label[LINE_LEN+1];
};


Solenoid::Solenoid( int open_pin, int close_pin, int days_of_week, const Time& open_time, const Time& close_time, const char* label ) : 
                    _open_pin(open_pin),
                    _close_pin(close_pin),
                    _days_of_week(days_of_week),
                    _open_time(open_time),
                    _close_time(close_time),
                    _is_open(false)
{
  strcpy(_label, label);
}

void Solenoid::close_solenoid()
{
  digitalWrite( _close_pin, HIGH );
  delay(200);
  digitalWrite( _close_pin, LOW );
  delay(200);
  
  _is_open = false;
}

void Solenoid::open_solenoid()
{
  digitalWrite( _open_pin, HIGH );
  delay(200);
  digitalWrite( _open_pin, LOW );
  delay(200);
  
  _is_open = true;
}


void Solenoid::print()
{
  //Serial.print( "Solenoid: " );
  //Serial.print( _open_time._hour, DEC );
  //Serial.print( " " );
  //Serial.print( _open_time._minute, DEC );
  //Serial.print( " " );
  //Serial.print( _close_time._hour, DEC );
  //Serial.print( " " );
  //Serial.print( _close_time._minute, DEC );
  //Serial.print( " " );
  //Serial.print( _open_pin, DEC );
  //Serial.print( " " );
  //Serial.print( _close_pin, DEC );
  //Serial.print( " " );
  //Serial.print( _days_of_week, HEX );
  //Serial.print( "\r\n" );
}

boolean Solenoid::validate()
{
  if( _open_pin > MAX_NUMBER_OF_DIG_PINS )
    return false;
    
  if( _close_pin > MAX_NUMBER_OF_DIG_PINS )
    return false;
    
  if( _open_time._hour >= 24 )
    return false;
    
  if( _open_time._minute >= 60 )
    return false;
    
  if( _close_time._hour > 24 )
    return false;
    
  if( _close_time._minute >= 60 )
    return false;
    
  if( 1 == ( bitRead( _days_of_week, 8 ) ) )
    return false;
  
  return true;
}

void Solenoid::set_label(const char* label)
{
  memcpy(_label, label, LINE_LEN);
}

void Solenoid::get_label(char* label)
{
  memcpy(label, _label, LINE_LEN); 
}

char Solenoid::get_open_pin()
{
  return _open_pin;
}

char Solenoid::get_close_pin()
{
  return _close_pin;
}

void Solenoid::set_open_pin(char pin)
{
  _open_pin = pin;
}

void Solenoid::set_close_pin(char pin)
{
  _close_pin = pin;
}

boolean Solenoid::is_open()
{
   return _is_open;
}

char Solenoid::get_days_of_week()
{
  return _days_of_week;
}

void Solenoid::set_days_of_week(char days_of_week)
{
  _days_of_week = days_of_week;
}


Time Solenoid::get_close_time()
{
    return _close_time;
}

void Solenoid::set_close_time(Time& time)
{
  _close_time = time;
}


Time Solenoid::get_open_time()
{
    return _open_time;
}

void Solenoid::set_open_time(Time& time)
{
  _open_time = time;
}
