// TMP 36
// ------
// scale factor = 10 mV/C
// 750 mV @ 25 C
//
// mV = 750 + 10 * (C - 25)
// C = (mV - 750)/10 + 25


// Temp (C) mV     Raw
// 25.0     801.5  164
//  5.0     601.2  123
// 95.0    1500.5  307

long update_rate = 500; // ms

int temp_pin = A0;

double get_temp(const int& analog_val) {
    // convert an analogRead value to a temperature
    // according to datasheet for TMP 36 sensor
    double mV = 1000.0 * 5.0 * analog_val / 1023.0;
    return 25.0 + (mV - 750.0) / 10.0;
}

double c2f(double c) {
    // convert Celsius to Fahrenheit
    return 9.0/5.0 * c + 32.0;
}

long t; // keep track of loop timer

void setup() {
    pinMode(temp_pin, INPUT_PULLUP);

    Serial.begin(9600);
    t = millis();
}

void loop() {
    // read the sensor and print the raw and temp values

    if (millis() - t > update_rate) {
        t = millis();

        // read temp sensor
        int    raw  = analogRead(temp_pin);
        float  mv   = 1000.0 * 5.0 * raw / 1023.0;
        double temp = get_temp(raw);

        Serial.print(raw);
        Serial.print("  ");
        Serial.print(mv);
        Serial.print("  ");
        Serial.print(temp);
        Serial.print("  ");
        Serial.print(c2f(temp));
        Serial.print('\n');
    }
}
