# Control RGB color based on input voltage

## Motivation

When the electrical charging system on a motorcycle is heavily loaded, it may not keep the battery fully charged. The first symptom of that is that voltage will drop continuously until it is no longer sufficient to keep the engine running. The second symptom is that the motorcycle will stop running and/or may not restart. If there is an indication of system voltage, the issue can be dealt with (by shedding load) before the moto stops running. This project will produce an indication using an Arduino/AVR to monitor voltage and transition an RGB LED from green through yellow and to red to indicate charging status.


## Hardware

* Arduino Pro Mini. (Or bare ATMEGA328P chip on PCBTODO")
* Voltage regulator and filtering capacitors to convert nominal 12V power to 5.0V to power the system. L7805CV regulator with 0.47µF input and 0.22µF output filtering capacitors.
* Resistor voltage divider to reduce the moto system voltage to <5.0V needed for the ADC on the AVR. (1x 2.4KΩ and 1x 1.2KΩ resistors to provide a divider that will produce 5.0V from 15.0V.)
* Input protection for the ADC consisting of 1N5231B (5.1V) Zener diode with 820Ω resistor. [0]
* RGB LED with 3 2KΩ series resistors. That's fairly high resistance but otherwise the LED will be excessively bright during the day. ()

Connect the middle leg of the volume fader to A0 with outer legs connected to ground and 5V to provide a 0-5V analog input.
Connect the longest leg of the RGB LED to ground. When the ground is toward the left, the remaining pins are red, green and blue left to right respectively. Connect the LED inputs to the digital outputs indicated in the code.

## TODO

* Average several input readings for better noise rejection.
* Develop scaled analog input with protection - done on mock-up.
* Develop VR to power board from ~12V auto power - done on mock-up.
* Develop 

[0]I've studied the data sheet for the Zener diode and have no idea if the paired resistor is the right value to provide protection.