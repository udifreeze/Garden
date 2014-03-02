#pragma once

#define LINE_LEN 16

extern RTC _rtc;
extern Keypad _keypad;
extern Config _config;
extern Temperature _temperature;
extern LCD _LCD;
extern Solenoid* _solenoids[];
extern const unsigned int NUMBER_OF_SOLENOIDS;

void show_idle_screen()
{
  char top_string[LINE_LEN+1] = "Time: ";
  char bottom_string[LINE_LEN+1] = "Date: ";
  
  Time now = _rtc.get_time();  
  now.time_string(&top_string[6]);
  now.date_string(&bottom_string[6]);

  _LCD.Print(top_string, bottom_string);
  //Serial.println(time_string);
  //Serial.println(date_string);
  delay(2000);
  
  strcpy(top_string,"Temp(c) ");
  strcpy(bottom_string,"Humidity(%) ");
  
  char temp_string[5] = {0}; 
  itoa( _temperature.get_temp(), temp_string, 10 );
  strcat(top_string, temp_string);
  
  memset(temp_string,0,5);
  itoa( _temperature.get_humidity(), temp_string, 10 );
  strcat(bottom_string, temp_string);
  
  _LCD.Print(top_string, bottom_string);

  delay(2000);
  
}

boolean show_yes_no_screen()
{
  _LCD.Print("Save?", "*-Yes #-No");
  while(true)
  {
    if(_keypad.get_key() == '*')
    {
      return true;
    }
    else if(_keypad.get_key() == '#')
    {
       return false;
    }
  }
}

void show_set_selo_label(int selo)
{
  char top_string[LINE_LEN+1] = "Label ";
  char bottom_string[LINE_LEN+1] = "__________";
  char temp_buffer[3] = {0};

  strcat(top_string, "S");
  strcat(top_string, itoa(selo,temp_buffer,10));
  _LCD.Print(top_string, bottom_string);
}

void show_configured_solenoids()
{
    char top_string[LINE_LEN+1] = {0};
    char bottom_string[LINE_LEN+1] = {0};
    char temp_buffer[3] = {0};
    char label[LINE_LEN+1] = {0};
    
    for(int i = 0 ; i < NUMBER_OF_SOLENOIDS ; ++i )
    {
      
      strcpy(top_string, "Showing ");
      strcpy(bottom_string, "Any key...");
      
       strcat(top_string, "S");
       strcat(top_string,itoa(i,temp_buffer,10));
       _LCD.Print(top_string, bottom_string);
       while(!_keypad.get_key()){}
       
       _solenoids[i]->get_label(label);
       _LCD.Print("Label", label);
       while(!_keypad.get_key()){}
       
       char dow = _solenoids[i]->get_days_of_week();
       memset(bottom_string,0,LINE_LEN+1);
       for(int i = 1 ; i <= 7 ; ++i)
       {
         Serial.println();
         if(bitRead(dow,i-1))
           bottom_string[i-1] = 48+i;
         else
           bottom_string[i-1] = 'X';
       }

       _LCD.Print("Days", bottom_string);
       while(!_keypad.get_key()){}
       
       Time time = _solenoids[i]->get_open_time();
       strcpy(top_string, "OPEN ");
       
       if(time._hour < 10)
         strcat(top_string, "0");
       strcat(top_string, itoa(time._hour,temp_buffer,10));
       strcat(top_string, "-");
       if(time._minute < 10)
         strcat(top_string, "0");
       strcat(top_string, itoa(time._minute,temp_buffer,10));
      
       time = _solenoids[i]->get_close_time();
       strcpy(bottom_string, "CLOS ");
     
       if(time._hour < 10)
         strcat(bottom_string, "0");
       strcat(bottom_string, itoa(time._hour,temp_buffer,10));
       strcat(bottom_string, "-");
       if(time._minute < 10)
         strcat(bottom_string, "0");
       strcat(bottom_string, itoa(time._minute,temp_buffer,10));
       
       _LCD.Print(top_string, bottom_string);
       while(!_keypad.get_key()){}
    }
}

void show_selo_open_screen(const char* label)
{    
    char top_line[LINE_LEN] = {0};
    strcat(top_line, "Solenoid:");
    strcat(top_line, label);
    _LCD.Print(top_line, "Is open");
    delay(1000);
}

void show_set_rtc_screen()
{
  char current_top_string[LINE_LEN+1];
  strcpy(current_top_string, "Hour: __-__");
  char current_bottom_string[LINE_LEN+1];
  strcpy(current_bottom_string, "Date: __/__/__");
  int i = 6;
  
  _LCD.Print(current_top_string,current_bottom_string);

  while( i < strlen(current_top_string))
  {
    char key = _keypad.get_key();
    if( ('0' <= key) && ('9' >= key) )
    {
      current_top_string[i] = key;
      ++i;
      
      if(current_top_string[i] == '-')
        ++i;
        
      _LCD.Print(current_top_string,current_bottom_string);
    }
  }
  
  i = 6;
  
  while(i < strlen(current_bottom_string))
  {
    char key = _keypad.get_key();
    if( ('0' <= key) && ('9' >= key) )
    {
      current_bottom_string[i] = key;
        ++i;
      
      if(current_bottom_string[i] == '/')
        ++i;
        
      _LCD.Print(current_top_string,current_bottom_string);
    }
  }
  
  char time_string[20] = {0};
  strcat(current_top_string,"-00 ");
  memcpy(time_string, current_top_string+6,9);
  memcpy(time_string+9, current_bottom_string+6,8);
  
  Serial.println(time_string);
    
  Time user_time(time_string);
  
  if(show_yes_no_screen())
    _rtc.set_time(user_time);
}

void show_set_selo_days(int selo)
{
    char dow = 0;
    char current_top_string[LINE_LEN+1] = {0};
    strcpy(current_top_string, "S");
    itoa(selo,&current_top_string[1],10);
    strcat(current_top_string, " days");    
    
    char current_bottom_string[LINE_LEN+1] = {0};
    strcpy(current_bottom_string, "_______");
    int i = 0;
    
    _LCD.Print(current_top_string,current_bottom_string);
    
    while(i < strlen(current_bottom_string))
    {
      char key = _keypad.get_key();
      if( ('1' <= key) && ('7' >= key) )
      {
        current_bottom_string[i] = i + '0' + 1;
        bitSet(dow, i);
        i++;
        _LCD.Print(current_top_string,current_bottom_string);
      }
      else if( '*' == key )
      {
        current_bottom_string[i] = 'x';  
        i++;
        _LCD.Print(current_top_string,current_bottom_string);    
      }
    }
    
    _solenoids[selo]->set_days_of_week(dow);
    delay(500);
}

void show_set_selo_times(int selo)
{
    const char* EMPTY_TIME_STRING = "__-__";
    char current_top_string[LINE_LEN+1] = {0};
    char current_bottom_string[LINE_LEN+1] = {0};
    
    int start = 5;
    int i = start;
    strcpy(current_top_string, "OPEN ");
    strcat(current_top_string, EMPTY_TIME_STRING);
    
    strcpy(current_bottom_string, "CLOS ");
    strcat(current_bottom_string, EMPTY_TIME_STRING);
        
    _LCD.Print(current_top_string, current_bottom_string);

    while(i < strlen(EMPTY_TIME_STRING) + start)
    {
      char key = _keypad.get_key();
      if( ('0' <= key) && ('9' >= key) )
      {
        current_top_string[i] = key;
        ++i;
        _LCD.Print(current_top_string, current_bottom_string);

        
        if(current_top_string[i] == '-')
          ++i;
      }
    }
    
    i = start;
    while(i < strlen(EMPTY_TIME_STRING) + start)
    {
      char key = _keypad.get_key();
      if( ('0' <= key) && ('9' >= key) )
      {
        current_bottom_string[i] = key;
        ++i;
        _LCD.Print(current_top_string, current_bottom_string);

        
        if(current_bottom_string[i] == '-')
          ++i;
      }
      
      delay(500);
    }
 
    char time_string[20] = {0};
    strcpy(time_string, &current_top_string[5]);
    strcat(time_string, "-00 ");
    strcat(time_string, "00/00/00");
    Time open_time(time_string);
    _solenoids[selo]->set_open_time(open_time);
        
    strcpy(time_string, &current_bottom_string[5]);
    strcat(time_string, "-00 ");
    strcat(time_string, "00/00/00");
    Time close_time(time_string);
    _solenoids[selo]->set_close_time(close_time);
}

void show_set_selos_screen()
{
  for(int selo = 0 ; selo < NUMBER_OF_SOLENOIDS ; ++selo)
  {
    show_set_selo_days(selo);
    show_set_selo_times(selo);
   // show_set_selo_label(selo);
    _config.set_solenoid(_solenoids[selo],selo);
  }
}

