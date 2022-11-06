# trimkey

Sketch for Digispark to assign Saitek Trim Axis to GamePad buttons.

The idea for the project came entirely from the following video:

[Hacking the Saitek Trim Wheel (Twin Otter Cockpit Build - Part 11)](https://youtu.be/SSh6FKWpMg0)

## Description
It has already been said 200 times that Saitek Trim is an Axis and therefore does not sync with the state in simulator.

Autopilot, digital trim, or any other state change results in a sudden change in trim.

Peter introduces the idea of hi-jacking the output of the SaitekTrim into a microcontroller and using V-USB as an input for USB HID.

He programmed it using an ATtiny85, but we can use Digispark and DigiJoystick libraries.

## Getting Started

### Prerequisite
**Wiring to hacked Saitek Trim and Digispark is required.**

See the video [Hacking the Saitek Trim Wheel (Twin Otter Cockpit Build - Part 11)](https://youtu.be/SSh6FKWpMg0)

We need just two wires from the SaitekTrim's encoder pins to the Digispark pins.

### Installing
Load this sketch to your Arduino IDE and transfer to your Digispark device.


## Help

* You can change PIN assign for your own Digispark models.
http://digistump.com/wiki/digispark/tutorials/modelbi2c

```
const unsigned char PIN_A = 0;
const unsigned char PIN_B = 2;
```

* And button release interval
```
const unsigned char BUTTON_WAIT = 5;  // in milliseconds.
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
