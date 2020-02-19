#include "AS5600.h"

volatile long sensor_position = 0;
volatile long last_sensor_position = 0;
volatile long sensor_position_with_rotations = 0;
volatile long motor_rotation_count = 0;

volatile long motor_position_without_offset = 0;
volatile long motor_position_steps = 0;
volatile long offset = 0;

void init_position_sensor(){
    Wire.beginTransmission(AS5600_ADDRESS);
    Wire.write(AS5600_REG_ANGLE_H);
    Wire.endTransmission();
    delay(50);
}

void speed_up_position_sensor_response_time(){
    Wire.beginTransmission(AS5600_ADDRESS);
    Wire.write(AS5600_REG_CONF);
    Wire.write(0x1F);// WD : 0, FTH : 111, SF : 11 : 0x1f
    Wire.endTransmission();
    delay(50);
}

int read_encoder(){
    int angle;
    Wire.requestFrom(AS5600_ADDRESS,2);
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    angle = ((msb & 0b00001111) << 8) + lsb;

    return angle;
}

void update_current_position(int microsteps){
    sensor_position = read_encoder();

    if (sensor_position - last_sensor_position < -AS5600_CPR_HALF)
    {
        ++motor_rotation_count;
    } else if (sensor_position -last_sensor_position > AS5600_CPR_HALF)
    {
        --motor_rotation_count;
    }
    
    sensor_position_with_rotations = sensor_position + AS5600_CPR * motor_rotation_count;
    last_sensor_position = sensor_position;

    motor_position_without_offset = (sensor_position_with_rotations * microsteps * STEPPER_CPR) / AS5600_CPR;
    motor_position_steps = motor_position_without_offset - offset;
}