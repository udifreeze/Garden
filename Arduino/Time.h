#pragma once

#include "Arduino.h"


class Time
{
public:
  Time();
  Time( char Hour, char Minute, char Seconds, char Day, char Date, char Month, char Year );
  Time(const char* time_string);
  Time( const Time& original_time );
  void time_string(char* time_string);
  void date_string(char* date_string);
  void day_string(char* day_string);
    
public:
  char _hour;
  char _minute;
  char _second;
  char _day;
  char _date;
  char _month;
  char _year;
  
};

Time::Time( char Hour, char Minute, char Second, char Day, char Date, char Month, char Year ) :
_hour(Hour), _minute(Minute), _second(Second), _day(Day), _date(Date), _month(Month), _year(Year)
{
}

Time::Time(const char* time_string)
{  
  char* fmt = "hh:mm:ss dd-mm-yy";
    
  if(strlen(time_string) != strlen(fmt))
    return;
  
  char num_buf[3] = {0};
  num_buf[0] = time_string[0];
  num_buf[1] = time_string[1];
  _hour = atoi(num_buf);
  
  num_buf[0] = time_string[3];
  num_buf[1] = time_string[4];
  _minute = atoi(num_buf);

  num_buf[0] = time_string[6];
  num_buf[1] = time_string[7];  
  _second = atoi(num_buf);
  
  num_buf[0] = time_string[9];
  num_buf[1] = time_string[10];
  _date = atoi(num_buf);
  
  num_buf[0] = time_string[12];
  num_buf[1] = time_string[13];
  _month = atoi(num_buf);

  num_buf[0] = time_string[15];
  num_buf[1] = time_string[16];  
  _year = atoi(num_buf);
}

Time::Time() :
_hour(0), _minute(0), _second(0), _day(1), _date(1), _month(1), _year(1)
{ 
}

Time::Time( const Time& original_time )
{
  _hour = original_time._hour;
  _minute = original_time._minute;
  _second = original_time._second;
  _day = original_time._day;
  _date = original_time._date;
  _month = original_time._month;
  _year = original_time._year;
}

void Time::time_string(char* time_string)
{
  int index = 0;
  
  if( _hour < 10 )
  {
    time_string[index] = '0';
    index++;
  }
  
  itoa( _hour, &time_string[index], 10 );
  index = 2;
  time_string[index] = ':';
  index++;
  
  if( _minute < 10 )
  {
     time_string[index] = '0';
     index++;
  }
  itoa( _minute, &time_string[index], 10 );
  index = 5;
  time_string[index] = ':';
  index++;
  
  if( _second < 10 )
  {
    time_string[index] = '0';
    index++;
  }
  itoa( _second, &time_string[index], 10 );
}

void Time::date_string(char* day_string)
{
  int index = 0;
  
  if( _date < 10 )
  {
    day_string[index] = '0';
    index++;
  }
  
  itoa( _date, &day_string[index], 10 );
  index = 2;
  day_string[index] = '/';
  index++;
  
  if( _month < 10 )
  {
     day_string[index] = '0';
     index++;
  }
  itoa( _month, &day_string[index], 10 );
  index = 5;
  day_string[index] = '/';
  index++;
  
  if( _year < 10 )
  {
    day_string[index] = '0';
    index++;
  }
  itoa( _year, &day_string[index], 10 );
}

void Time::day_string(char* day_string)
{
  switch(_day)
  {
    case 1: strcpy(day_string, "Sun"); break;
    case 2: strcpy(day_string, "Mon"); break;
    case 3: strcpy(day_string, "Tue"); break;
    case 4: strcpy(day_string, "For"); break;
    case 5: strcpy(day_string, "Thu"); break;
    case 6: strcpy(day_string, "Fri"); break;
    case 7: strcpy(day_string, "Sat"); break;
    default: strcpy(day_string, "ERR"); break;
  };
}
