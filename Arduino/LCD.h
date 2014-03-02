#pragma once

#include "Arduino.h"
#include <Wire.h>
#include <SoftwareSerial.h>

#define DISPLAY_CLEAR 88
#define DISPLAY_LINE 71
#define DISPLAY_WRAP 67

class LCD
{
public:
  LCD();
  void Print(const char* line1, const char* line2);
  void send_char_to_lcd(char letter);
  void send_command_to_lcd(int command);
  void send_command_to_lcd(int command1,int command2, int command3);
  void write_string_to_lcd(const char* string);
  
private:
  SoftwareSerial _serial;
};

LCD::LCD() : _serial(12,13)
{
  _serial.begin(19200); 
 // send_command_to_lcd(DISPLAY_WRAP);
 // send_command_to_lcd(DISPLAY_CLEAR);
 // Print("Hello", "Garden");
}

void LCD::Print(const char* line1, const char* line2)
{
  send_command_to_lcd(DISPLAY_CLEAR);
  send_command_to_lcd(DISPLAY_LINE,0,0);
  write_string_to_lcd(line1);
  send_command_to_lcd(DISPLAY_LINE,0,1);
  write_string_to_lcd(line2);
}

void LCD::send_char_to_lcd(char letter)
{
  _serial.print(letter);
  delay(10); 
}

void LCD::write_string_to_lcd(const char* string)
{
  int strSize = strlen(string);
  for(int i = 0 ; i < strSize ; ++i)
    send_char_to_lcd(string[i]);
}

void LCD::send_command_to_lcd(int command1,int command2, int command3)
{
  send_char_to_lcd(0xfe); 
  send_char_to_lcd(command1);
  send_char_to_lcd(command2);
  send_char_to_lcd(command3);
  send_char_to_lcd(0xfd);
}

void LCD::send_command_to_lcd(int command)
{
  send_char_to_lcd(0xfe); 
  send_char_to_lcd(command);
  send_char_to_lcd(0xfd);
}
