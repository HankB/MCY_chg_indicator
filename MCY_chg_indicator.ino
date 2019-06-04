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

const int high = 1000;
const int good = 921;
const int marginal = 887;
const int bad = 682;
const int spread = good - bad;

int sensorPin =   A0;   // select the input pin for the potentiometer
int redPin =      11;   // select the pin for the LED
int sensorValue = 0;    // variable to store the value coming from the sensor
int greenpin =    10;

const int red_pct = 50;
int green_pct = 50;
int max_DAC   = 255;

static const int analog_repeat =        4;  // consedutive analog readings to sum to reduce noise
static const int analog_repeat_delay =  4;  // delay in ms between consecutive analog readings

#define SERIAL_OUT  1

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(redPin, OUTPUT);
  pinMode(greenpin, OUTPUT);
#if SERIAL_OUT
  Serial.begin(9600);
#endif //SERIAL_OUT
}

void loop() {
  // read the value from the sensor:
  sensorValue = 0;
  for(int i=0; i<analog_repeat; i++) {
    sensorValue += analogRead(sensorPin);
    delay(analog_repeat_delay);
  }
#if SERIAL_OUT
    Serial.print("raw ");
    Serial.print(sensorValue);
#endif //SERIAL_OUT
  sensorValue = (sensorValue + analog_repeat/2)/analog_repeat;
#if SERIAL_OUT
    Serial.print(" rounded ");
    Serial.print(sensorValue);
#endif //SERIAL_OUT
  if(sensorValue >= good) {
    analogWrite(greenpin, (max_DAC*green_pct)/100);
    analogWrite(redPin, 0);
#if SERIAL_OUT
    Serial.print(" good ");
    Serial.println(sensorValue);
#endif //SERIAL_OUT
    }
  else if(sensorValue < bad) {
    analogWrite(greenpin, 0);
    analogWrite(redPin, (max_DAC*red_pct)/100);
#if SERIAL_OUT
    Serial.print(" bad  ");
    Serial.println(sensorValue);
#endif //SERIAL_OUT
  }
  else {
    unsigned int blend = (sensorValue-bad)*100/spread;  // calculate blend percent
    unsigned int green = blend*max_DAC/100*green_pct/100;
    unsigned int red = (100-blend)*max_DAC/100*red_pct/100;
    analogWrite(greenpin, green);
    analogWrite(redPin, red);
#if SERIAL_OUT
    Serial.print(" betw ");   Serial.print(sensorValue);
    Serial.print(" blend ");  Serial.print(blend);
    Serial.print(" green ");  Serial.print(green);
    Serial.print(" red ");    Serial.print(red);
    Serial.print(" sum ");    Serial.println(green+red);
#endif //SERIAL_OUT
  }
#if SERIAL_OUT
  delay(1000);
#else //SERIAL_OUT
  delay(10);
#endif //SERIAL_OUT
}
