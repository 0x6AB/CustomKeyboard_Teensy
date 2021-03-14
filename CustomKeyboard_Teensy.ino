#include "Keyboard.h"

#define ACCESS_KEY 1234

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200); // устанавливаем последовательное соединение
}

int i=0;
byte data[1024];

struct base_data
{
   byte type;
   word key;
   word timing;
   byte floating_border;
   byte arg[512];
};
typedef struct base_data Base_data;

void loop() {
  i=0;
  if (Serial.available() > 0) 
  { 
    memset(data, 0, 511);
    while(Serial.available() > 0) {
      data[i] = Serial.read();
      i++;
    }
    Base_data *sdata = (Base_data*)data; 
    
    

    if((sdata->type == 0) && (sdata->key == ACCESS_KEY)) {
      Serial.print("type = ");
      Serial.println(sdata->type);

      Serial.print("key = ");
      Serial.println(sdata->key);
      
      Serial.print("timing = ");
      Serial.println(sdata->timing);
  
      Serial.print("floating_border = ");
      Serial.println(sdata->floating_border);
    }
    
    if((sdata->type == 1) && (sdata->key == ACCESS_KEY)) {
      Serial.println((char*)sdata->arg);
      Keyboard.print((char*)sdata->arg);
    }

    if((sdata->type == 2) && (sdata->key == ACCESS_KEY)) {
      Keyboard.press((sdata->arg)[0]);
      delay(sdata->timing);
      Keyboard.release((sdata->arg)[0]);
    }
    
    if((sdata->type == 3) && (sdata->key == ACCESS_KEY)) {
      int i = 0;
      while( sdata->arg[i]!=0 ) {
        Keyboard.press((sdata->arg)[i]);
        delay(sdata->timing+random(sdata->floating_border));
        Keyboard.release((sdata->arg)[i]);
        delay(sdata->timing+random(sdata->floating_border));
        i++;
      }
    }

    if((sdata->type == 4) && (sdata->key == ACCESS_KEY)) {
      int i = 0;
      while( sdata->arg[i]!=0 ) {
        Keyboard.press((sdata->arg)[i]);
        delay(sdata->timing+random(sdata->floating_border));
        Keyboard.release((sdata->arg)[i]);
        delay(sdata->timing+random(sdata->floating_border));
        i++;
        Serial.println("w");
      }
      Serial.println("e");
    }
    
    Serial.flush();
  }
}
