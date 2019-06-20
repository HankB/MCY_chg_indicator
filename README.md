# Control RGB color based on input voltage

## Motivation

When the electrical charging system on a motorcycle is heavily loaded, it may not keep the battery fully charged. The first symptom of that is that voltage will drop continuously until it is no longer sufficient to keep the engine running. The second symptom is that the motorcycle will stop running and/or may not restart. If there is an indication of system voltage, the issue can be dealt with (by shedding load) before the moto stops running. This project will produce an indication using an Arduino/AVR to monitor voltage and transition an RGB LED from green through yellow and to red to indicate charging status.

Secondary motivation is to help mark the passage of time. Many traffic lights won't detect the presence of a motorcycle and after some time it is allowed to proceed when traffic permits. Flash one, two, three and four times to mark passage of a minute. (15 second intervals.)

## Functionality

* Vary the color of the RGB LED from red -> yellow -> green to indicate system voltage.
* Flash (blip) the LED periodically to mark the passage of time.

## Hardware

* Arduino Pro Mini. (Or bare ATMEGA328P chip on PCB)
* Voltage regulator and filtering capacitors to convert nominal 12V power to 5.0V to power the system. L7805CV regulator with 0.47µF input and 0.22µF output filtering capacitors.
* Resistor voltage divider to reduce the moto system voltage to <5.0V needed for the ADC on the AVR. (1x 2.4KΩ and 1x 1.2KΩ resistors to provide a divider that will produce 5.0V from 15.0V.)
* Input protection for the ADC consisting of 1N5231B (5.1V) Zener diode with 820Ω resistor. [0]
* RGB LED with 3 2KΩ series resistors. That's fairly high resistance but otherwise the LED will be excessively bright during the day. ()

Connect the middle leg of the volume fader to A0 with outer legs connected to ground and 5V to provide a 0-5V analog input.
Connect the longest leg of the RGB LED to ground. When the ground is toward the left, the remaining pins are red, green and blue left to right respectively. Connect the LED inputs to the digital outputs indicated in the code.


## Other information

General description https://docs.google.com/document/d/1oGInpiPI6TI1JvXcmjz_O_Tvbv5o_kn_NtnWW1Aht5o/edit?usp=sharing
Resistor vs. ADC reading calculations https://docs.google.com/spreadsheets/d/1I-rtjzvy2xRRpHdrsMQctPhc0Ry49aa2tnfBnYBoY4o/edit?usp=sharing

## TODO

* Average several input readings for better noise rejection. - done
* Develop scaled analog input with protection - done on mock-up.
* Develop VR to power board from ~12V auto power - done on mock-up.
* Build a custom board with Pro Mini, power supply, analog input conditioning and outputs for the RGB LED. 

## Errata

When using the Inland Pro Mini 5V and providing it with 5V to Vcc, it reads full scale at ~4.7V. Treating the ADC as if it has a reference voltage of 4.7V produces readings over the range more closely match what is read using a DVM.

[0]I've studied the data sheet for the Zener diode and have no idea if the paired resistor is the right value to provide protection.