// Include guard
#ifndef LIB_ULTRASONIC_HEADER_FLAG
#define LIB_ULTRASONIC_HEADER_FLAG

// Include core framework
#include <Arduino.h>

class ultrasonic_sensor
{
    private:
        uint8_t _echo_pin;
        uint8_t _trig_pin;
    public:
        // Initializer
        ultrasonic_sensor
        (
            uint8_t echo_pin,
            uint8_t trig_pin
        )
        {
            _echo_pin = echo_pin;
            _trig_pin = trig_pin;
        }

        // Setup sensor
        void begin()
        {
            pinMode(_echo_pin, INPUT);
            pinMode(_trig_pin, OUTPUT);
        }

        // Get distance data
        uint16_t get_distance()
        {
            digitalWrite(_trig_pin, LOW);
            delayMicroseconds(5);
            digitalWrite(_trig_pin, HIGH);
            delayMicroseconds(10);
            return (pulseIn(_echo_pin, HIGH) / 2) / 29.1;
        }
};
#endif