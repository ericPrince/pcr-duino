#include <temp_controller.h>

// CALIBRATION
// Temp (C) mV     Raw
// 25.0     801.5  164
//  5.0     601.2  123
// 95.0    1500.5  307

// RUN CONFIGURATION
// Temp (C)    Duration (s)
// 94          60
// 52          60
// 74         120

// pin assignments
int temp_pin = A0;
int heat_pin =  7;
int cool_pin =  6;

// hysteresis tolerance (Celsius)
float hysteresis = 4.0; 

// range of temps to heat/cool
float temp_denat   = 94.0;
long  millis_denat = 60e3;

float temp_anneal   = 52.0;
long  millis_anneal = 60e3;

float temp_elong   = 74.0;
long  millis_elong = 120e3;

// object that controls system heating/cooling
TempController controller(temp_pin,
                          heat_pin,
                          cool_pin,
                          hysteresis);

void setup()
{
    // use linear fit to calibrate temp controller
    //                    Temp (C)         mV
    controller.calibrate(      5.0,     601.2 , 
                              95.0,    1500.5 );
    
    Serial.begin(9600);
}

long t_saved;

void loop()
{
    // DENATURATION

    controller.set_temp(temp_denat);

    while (!controller.at_temp())
    {
        controller.update();
        Serial.print("SET DENAT  ");
        Serial.println(controller.get_temp());
    }

    t_saved = millis();
    while (millis() - t_saved < millis_denat)
    {
        controller.update();
        Serial.print("AT DENAT  ");
        Serial.println(controller.get_temp());
    }

    // ANNEALING

    controller.set_temp(temp_anneal);

    while (!controller.at_temp())
    {
        controller.update();
        Serial.print("SET ANNEAL  ");
        Serial.println(controller.get_temp());
    }

    t_saved = millis();
    while (millis() - t_saved < millis_anneal)
    {
        controller.update();
        Serial.print("AT ANNEAL  ");
        Serial.println(controller.get_temp());
    }

    // ELONGATION

    controller.set_temp(temp_elong);

    while (!controller.at_temp())
    {
        controller.update();
        Serial.print("SET ELONG  ");
        Serial.println(controller.get_temp());
    }

    t_saved = millis();
    while (millis() - t_saved < millis_elong)
    {
        controller.update();
        Serial.print("AT ELONG  ");
        Serial.println(controller.get_temp());
    }
}