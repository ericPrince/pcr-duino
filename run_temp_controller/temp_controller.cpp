#include <temp_controller.h>

#include <arduino.h>

TempController::TempController(int   temp_pin,         // pin for temperature sensor
                               int   heat_pin,         // pin for heater
                               int   cool_pin,         // pin for cooler
                               float hysteresis_latch, // temperature range allowable for hysteresis
                               int   n_samples = 8)    // number of analog read samples for temp pin
: 
temp_pin(temp_pin),
heat_pin(heat_pin),
cool_pin(cool_pin),
hysteresis_latch(hysteresis_latch),
n_samples(n_samples),
active(false),
heating(false),
cooling(false)
{
    pinMode(temp_pin, INPUT_PULLUP);
    pinMode(heat_pin, OUTPUT);
    pinMode(cool_pin, OUTPUT);
}

// update the temparature setpoint and activate the controller
void TempController::set_temp(float setpoint) 
{
    temp_setpoint = setpoint;
    activate();
}

// measure the temperature and update the state of the controller
// this function should be called often in a loop
void TempController::update() 
{
    if (active) 
    {
        double temp = get_temp();

        if (temp < temp_setpoint + (heating ? 0 : -hysteresis_latch)) 
        {
            // heater should be on if at less than desired temp (within hysteresis)
            heating = true;
            digitalWrite(heat_pin, HIGH);
            digitalWrite(cool_pin, LOW);
        }
        else if (temp > temp_setpoint + (cooling ? 0 : hysteresis_latch)) 
        {
            // cooler should be on if at greater than desired temp (within hysteresis)
            cooling = true;
            digitalWrite(cool_pin, HIGH);
            digitalWrite(heat_pin, LOW);
        }
        else 
        {
            // heater and cooler should be off if at desired temp within hysteresis
            heating = false;
            cooling = false;
            digitalWrite(heat_pin, LOW);
            digitalWrite(cool_pin, LOW);
        }
    }
    else 
    {
        // not active so don't try to control temperature
        heating = false;
        cooling = false;
        digitalWrite(heat_pin, LOW);
        digitalWrite(cool_pin, LOW);
    }
}

// return true if the temperature is close to the setpoint (within hysteresis limits)
bool TempController::at_temp() 
{
    return abs(get_temp() - temp_setpoint) < hysteresis_latch;
}

// get the measured temperature
double TempController::get_temp() 
{
    // get multiple readings to filter out noise
    double val = 0.0;
    for (int i = 0; i < n_samples; i++)
    {
        val += analogRead(temp_pin); // TODO: need to delay between readings??
    }
    val /= n_samples;

    double mV = 1000.0 * val * 5.0/1023.0;
    // double mV = 1000.0 * analogRead(temp_pin) * 5.0/1023.0;
    return m * mV + b;
}

// use two points to calibrate the temperature sensor
void TempController::calibrate(double t1, double mv1, double t2, double mv2) 
{
    // (t - t1) = (mv - mv1) * (t2 - t1) / (mv2 - mv1)
    // t = m * mv + b
    m = (t2 - t1) / (mv2 - mv1);
    b = t1 - m * mv1;
}

// give slope and y intercept to calibrate the temperature sensor
// exists so calibration can be done with a more complex method
void TempController::calibrate(double m, double b) 
{
    m = m;
    b = b;
}

// activate the temp controller
void TempController::activate() 
{
    active = true;
}

// deactivate the temp controller
void TempController::deactivate() 
{
    active = false;
}

double c2f(double c) 
{
    // convert Celsius to Fahrenheit
    return 9.0/5.0 * c + 32.0;
}

double f2c(double f) 
{
    // convert Fahrenheit to Celsius
    return 5.0/9.0 * (f - 32.0);
}