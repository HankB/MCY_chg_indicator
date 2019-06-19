/*
  This sketch began life as the "Analog Input" example. Little of the original remains.
  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput

  Monitor an analog input and illuminate an RGB LED to indicate evaluation of
  the charging voltage. Input volgate is scaled 1:3 so that 15V from the
  charging system would present 5.0V at the analog input.

  See https://docs.google.com/document/d/1oGInpiPI6TI1JvXcmjz_O_Tvbv5o_kn_NtnWW1Aht5o/edit?usp=sharing
  and https://docs.google.com/spreadsheets/d/1I-rtjzvy2xRRpHdrsMQctPhc0Ry49aa2tnfBnYBoY4o/edit?usp=sharing
  for further information.

*/

// thresholds based on apparent 4.7V ADC reference voltage when Pro Mini is provided with Vcc = 5.0V
static const uint16_t high = 1000;
static const uint16_t good = 921;
static const uint16_t marginal = 887;
static const uint16_t bad = 682;
static const uint16_t spread = good - bad;

// I really wish Arduino didn't hide the signatures for library finctions like pinMode()
static const int sensorPin =   A0;   // select the input pin for the potentiometer
static const int redPin =      9;   // select the pin for the LED
static const int greenpin =    10;

static uint16_t sensorValue = 0;    // variable to store the value coming from the sensor

const uint16_t red_pct = 50;
const uint16_t green_pct = 50;
const uint16_t max_DAC   = 255;

#define SERIAL_OUT  1

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(redPin, OUTPUT);
  pinMode(greenpin, OUTPUT);
#if SERIAL_OUT
  Serial.begin(9600);
#endif //SERIAL_OUT
}

uint16_t readVoltage(void) {
  static const uint16_t analog_repeat =        8;  // consedutive analog readings to sum to reduce noise
  static const uint16_t analog_repeat_delay =  4;  // delay in ms between consecutive analog readings
  static uint16_t readings[analog_repeat];
  static uint16_t value;

  for (int i = 0; i < analog_repeat; i++) {
    readings[i] = analogRead(sensorPin);
    value += readings[i];
    delay(analog_repeat_delay);
  }
  value = (value + analog_repeat / 2) / analog_repeat;  // divide with rounding

#if SERIAL_OUT
  for (int i = 0; i < analog_repeat; i++) {
    Serial.print(readings[i]);
    Serial.print(" ");
  }
  Serial.print(" ");
  Serial.print(value);
#endif //SERIAL_OUT
  return value;
}

void loop() {
  // read the value from the sensor:
  sensorValue = readVoltage();

#if SERIAL_OUT
  Serial.print(" rounded ");
  Serial.print(sensorValue);
#endif //SERIAL_OUT
  if (sensorValue >= good) {
    analogWrite(greenpin, (max_DAC * green_pct) / 100);
    analogWrite(redPin, 0);
#if SERIAL_OUT
    Serial.print(" good ");
    Serial.println(sensorValue);
#endif //SERIAL_OUT
  }
  else if (sensorValue < bad) {
    analogWrite(greenpin, 0);
    analogWrite(redPin, (max_DAC * red_pct) / 100);
#if SERIAL_OUT
    Serial.print(" bad  ");
    Serial.println(sensorValue);
#endif //SERIAL_OUT
  }
  else {
    uint16_t blend = (sensorValue - bad) * 100 / spread; // calculate blend percent
    uint16_t green = blend * max_DAC / 100 * green_pct / 100;
    uint16_t red = (100 - blend) * max_DAC / 100 * red_pct / 100;
    analogWrite(greenpin, green);
    analogWrite(redPin, red);
#if SERIAL_OUT
    Serial.print(" betw ");   Serial.print(sensorValue);
    Serial.print(" blend ");  Serial.print(blend);
    Serial.print(" green ");  Serial.print(green);
    Serial.print(" red ");    Serial.print(red);
    Serial.print(" sum ");    Serial.println(green + red);
#endif //SERIAL_OUT
  }
#if SERIAL_OUT
  delay(1000);
#else //SERIAL_OUT
  delay(10);
#endif //SERIAL_OUT
}
