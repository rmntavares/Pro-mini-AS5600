#include <Arduino.h>
#include <Wire.h>
#include "AS5600.h"

#define MOTOR_ID   1

void debug_serial(){
  Serial.print("Sensor position : ");
  Serial.println(sensor_position);
}

long time_begin_debug_serial = micros();

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("-------------- START --------------");
  Wire.begin();
  Wire.setClock(1000000); // 1 Mbits
  delay(100);

  init_position_sensor();
  time_begin_debug_serial = micros();
  Serial.println("-------------- SETUP FINISHED --------------");
}

bool action_available = true;

void loop() {
  action_available = true;
  update_current_position(1000);

  // FOR DEBUG ONLY
  if (micros()-time_begin_debug_serial > 500000)
  {
    time_begin_debug_serial = micros();
    debug_serial();
  }
  
}