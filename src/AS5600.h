#include <Arduino.h>
#include <Config.h>
#include <Wire.h>

extern volatile long sensor_position;
extern volatile long last_sensor_position;
extern volatile long sensor_position_with_rotations;
extern volatile long motor_rotation_count;

extern volatile long motor_position_without_offset;
extern volatile long motor_position_steps;

extern volatile long offset;

void init_position_sensor();
void speed_up_position_sensor_response_time();
int read_encoder();
void update_current_position(int microsteps);