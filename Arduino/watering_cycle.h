#pragma once
#include "time.h"

struct WATERING_CYCLE
{
  WATERING_CYCLE* Next;
  WATERING_CYCLE* Before;
  TIME OpenTime;
  TIME CloseTime;
};

void new_watering_cycle( WATERING_CYCLE* head )
{
  if( !head )
  {
    head = alloc_new_watering_cycle();
    return;
  }
  
  WATERING_CYCLE* current_ws = head;
  WATERING_CYCLE* new_ws = alloc_new_watering_cycle();
  
  while( NULL != current_ws->Next )
    current_ws = current_ws->Next;
    
  current_ws.Next = new_ws;
  new_ws.Before = current_ws;
}

WATERING_CYCLE* alloc_new_watering_cycle()
{
  WATERING_CYCLE* new_ws = malloc( sizeof(WATERING_CYCLE) );
  if( !head )
    return new_ws;
    
  head->Next = NULL;
  head->Before = NULL;
  return new_ws;
}

int count_watering_cycles( WATERING_CYCLE* head )
{
  int i = 0;
  while( NULL != current_ws->Next )
  {
    current_ws = current_ws->Next;
    i++;
  }
  
  return i;
}

void remove_watering_cycle( WATERING_CYCLE* head, unsigned int index )
{
  if( !head )
    return;
  
  WATERING_CYCLE* ws = head;
  for( int i = 0 ; i < index ; ++i )
  {
    ws = ws->Next;
  }
  
  ws->Before->Next = ws->Next;
  ws->Next->Before = ws->Before;
  
  free(ws);
}


