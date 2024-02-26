// Include guard
#ifndef LIB_MOVECONTROL_HEADER_FLAG
#define LIB_MOVECONTROL_HEADER_FLAG

// Include core framework
#include <Arduino.h>

class move_control
{
    private:
        uint8_t _speed_pin_l, _dir_pin_l;
        uint8_t _speed_pin_r, _dir_pin_r;
    public:
        move_control(
            uint8_t speed_pin_l, 
            uint8_t dir_pin_l, 
            uint8_t speed_pin_r,
            uint8_t dir_pin_r
        )
        {
            // Initialize variables
            _speed_pin_l = speed_pin_l;
            _dir_pin_l = dir_pin_l;
            _speed_pin_r = speed_pin_r;
            _dir_pin_r = dir_pin_r;
        }

        void begin()
        {
            // Prepare motors
            // Prepare speed direction pins
            pinMode(_dir_pin_l, OUTPUT);
            pinMode(_dir_pin_r, OUTPUT);
            
            // Prepare speed control pins
            pinMode(_speed_pin_l, OUTPUT);
            pinMode(_speed_pin_r, OUTPUT);
        }

        void raw_move(
            uint8_t left_motor_speed, 
            uint8_t right_motor_speed
        )
        {
            analogWrite(_speed_pin_l, left_motor_speed);
            analogWrite(_speed_pin_r, right_motor_speed);
        }

        void set_direction(
            bool left_motor_direction,
            bool right_motor_direction
        )
        {
            digitalWrite(_dir_pin_l, !left_motor_direction);
            digitalWrite(_dir_pin_r, !right_motor_direction);
        }
};
#endif