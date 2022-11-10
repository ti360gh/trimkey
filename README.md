# trimkey

Sketch for Digispark to assign Saitek Trim Axis to GamePad buttons.

The idea for the project came entirely from the following video:

[Hacking the Saitek Trim Wheel (Twin Otter Cockpit Build - Part 11)](https://youtu.be/SSh6FKWpMg0)

## Description
It has already been said 200 times that Saitek Trim is an Axis and therefore does not sync with the state in simulator.

Any autopilot, digital trim, or other background change of state will cause an abrupt attitude change on the next SaitekTrim input.

As a countermeasure, the output of SaitekTrim is hijacked and input to the microcontroller, and V-USB is used as the input for USB HID.

He programmed it using an ATtiny85, but we can use Digispark and DigiJoystick libraries.

## Getting Started

### Prerequisite

**Wiring to hacked Saitek Trim and Digispark is required.**

See the video [Hacking the Saitek Trim Wheel (Twin Otter Cockpit Build - Part 11)](https://youtu.be/SSh6FKWpMg0)


We need just two wires from the SaitekTrim's encoder pins to the Digispark input pins.

One for PIN0 or PIN1 (depending on your device) and the other for PIN2.

### Installing

Load this sketch to your Arduino IDE and transfer to your Digispark device.


## Help

* You can change PIN assign for your own Digispark models.

http://digistump.com/wiki/digispark/tutorials/modelbi2c

Mine has a built-in LED on pin 1, but if yours is pin 0, please swap the PIN_A and PIN_LED assignments (and also the wiring).

```
const uint8_t PIN_LED = 1;
const uint8_t PIN_A = 0;   
```

* You can change button release interval
```
const uint8_t BUTTON_WAIT = 17;  // in milliseconds. 60fps=16.66ms
```


## Author

ti360✍ https://twitter.com/ti360

## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

## Acknowledgments

Inspiration
* [Hacking the Saitek Trim Wheel (Twin Otter Cockpit Build - Part 11)](https://youtu.be/SSh6FKWpMg0)
* [Project – Saitek Trim Wheel Internals Replacement](https://www.newioit.com.au/archives/66)
