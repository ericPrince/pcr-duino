#ifndef PCR_TEMP_CONTROLLER_H
#define PCR_TEMP_CONTROLLER_H

#include <arduino.h>

// Celsius to Fahrenheit
double c2f(double c);

// Fahrenheit to Cesuis
double f2c(double f);

// TODO: add maximum switching rate

// Use a heater, cooler, and temp sensor to regulate temperature
class TempController 
{

public:

    TempController(int   temp_pin,         // pin for temperature sensor
                   int   heat_pin,         // pin for heater
                   int   cool_pin,         // pin for cooler
                   float hysteresis_latch, // temperature range allowable for hysteresis
                   int   n_samples = 8);   // number of analog read samples for temp pin

    // update the temparature setpoint and activate the controller
    void set_temp(float setpoint);

    // measure the temperature and update the state of the controller
    // this function should be called often in a loop
    void update();

    // return true if the temperature is close to the setpoint (within hysteresis limits)
    bool at_temp();

    // get the measured temperature
    double get_temp();

    // use two points to calibrate the temperature sensor
    void calibrate(double t1, double mv1, double t2, double mv2);

    // give slope and y intercept to calibrate the temperature sensor
    // exists so calibration can be done with a more complex method
    void calibrate(double m, double b);

    // activate the temp controller
    void activate();

    // deactivate the temp controller
    void deactivate();

private:

    // pins
    int temp_pin; // pin for temperature sensor
    int heat_pin; // pin for heater
    int cool_pin; // pin for cooler

    // temp controller
    float hysteresis_latch; // temperature range allowable for hysteresis
    float m;                // gain for converting millivolts to temperature
    float b;                // offset for converting millivolts to temperature
    int   n_samples;        // number of analog read samples for temp pin

    // setpoint
    float temp_setpoint; // the current temperature setpoint
    bool active;         // flag of whether the system is actively controlling temperature
    bool heating;        // true iff the heater is running
    bool cooling;        // true iff the cooler is running

}; // class TempController

#endif // PCR_TEMP_CONTROLLER_H