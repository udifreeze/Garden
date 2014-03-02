#pragma once

#include <Wire.h>
#include <inttypes.h>

const int KEYPAD_ADDRESS = B0100000;

class Keypad 
{
public:
  Keypad();
  char get_key();
  
private:
  char sample_keypad();
  char code_to_char(byte code);

};

Keypad::Keypad()
{
  #define I2C_MASTER
  Wire.begin(I2C_MASTER);
}

char Keypad::code_to_char(byte code)
{
  switch(code)
  {
    case 0xBE: return '0';
    case 0x77: return '1'; 
    case 0xB7: return '2'; 
    case 0xD7: return '3'; 
    case 0x7B: return '4'; 
    case 0xBB: return '5'; 
    case 0xDB: return '6'; 
    case 0x7D: return '7'; 
    case 0xBD: return '8'; 
    case 0xDD: return '9'; 
    case 0xE7: return 'A'; 
    case 0xEB: return 'B'; 
    case 0xED: return 'C'; 
    case 0xEE: return 'D'; 
    case 0x7E: return '*'; 
    case 0xDE: return '#'; 
    default:   return  0 ;
  };
}

char Keypad::sample_keypad()
{
  Wire.beginTransmission(KEYPAD_ADDRESS);
  Wire.write(0xF0);
  Wire.endTransmission();
  
  Wire.beginTransmission(KEYPAD_ADDRESS);
  Wire.requestFrom(KEYPAD_ADDRESS,1);
  byte code1 = Wire.read();
  Wire.endTransmission();
  
  Wire.beginTransmission(KEYPAD_ADDRESS);
  Wire.write(0x0F);
  Wire.endTransmission();
  
  Wire.beginTransmission(KEYPAD_ADDRESS);
  Wire.requestFrom(KEYPAD_ADDRESS,1);
  byte code2 = Wire.read();
  Wire.endTransmission();
  
  return code_to_char(code1+code2);
}

char Keypad::get_key()
{  
  char key_pressed = sample_keypad();
  
  if(0 != key_pressed)
  {
     while(sample_keypad() != 0 ){}
     Serial.print("Key Pressed: ");
     Serial.println(key_pressed);
  }
    
  return key_pressed;
}

