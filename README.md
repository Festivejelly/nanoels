**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

[🇷🇺 перевод на русский](https://translate.google.com/translate?hl=en&sl=en&tl=ru&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)

# NanoEls

90€ DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

![NanoEls explosion diagram](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/h1-exploded-view.png)

# Features

- Positive and negative screw pitches
  - From -10mm to 10mm
  - Resolution 0.01mm
- Automatic lead screw stops
- Independent carriage moves without losing the thread

# Limitations

- Nema 23 stepper usable maximum is ~600 RPM, here a 1:1 stepper to leadscrew ratio is used. In practice this means that cutting e.g. 2mm thread with a 2mm leadscrew spindle top speed should stay under 600 RPM.
  - This can be mitigated to some extent by using e.g. 40 tooth gear on the leadscrew and 60 tooth gear on the motor at the expense of the maximum leadsrew torque

# Hardware overview

- 5 plastic 3D-printed parts (gears, mounts)
- Uses readily available hardware
  - 52€ Nema 23 stepper and driver
  - 10€ 24V 5A power supply
  - 9€ printed curcuit board (PCB)
  - 9€ rotary encoder
  - 3€ Arduino Nano
  - 3€ push buttons
  - 2€ OLED display
  - 5V power supply e.g. an old phone charger
  - 8 bolts, 2 nuts, 2 washers and a few wires
- Does not require metalworking
- Does not require drilling holes in the lathe

# Other hardware required

- Soldering iron, solder
- Hex and screwdrivers
- Soft hammer or a woodworking clamp
- 50T metal gear that your lathe came with
- Grease for the gears

# Supported lathe models

As long as you can securely connect the rotary encoder to the spindle and stepper motor to the leadscrew, most lathes are supported.

3D printed gears and mounts are available for the following models:

- WM210 or WM210V

Please note that sometimes 2 lathes of the same model have different dimensions and 3D printed parts might not fit. Please share with us your 3D models if you made new ones.

# Instructions

We've tried to simplify the process as much as possible but building NanoEls is still going to take considerable time and effort, basic mechanical and electrical knowledge.

You might need to design your own mounts and gears if the ones we have don't fit. If you need help designing a 3D printed part, please open a GitHub Issue with exact dimensions of the part that you need.

## Parts

### Stepper and driver

I used the following one but most Nema 23 or higher steppers should work.

- Nema 23 Stepper Motor Bipolar 1.8deg 3.0 Nm 4.2A 57x57x113mm 4 Wires Open Loop
- DM556Y Driver 1.7-5.6A DC20V~50V

DM556Y is 118.5mm wide which fits the case 3D model. Other drivers might not fit into it.

Closed Loop stepper might be nice to have but not necessary for NanoEls to work on small lathes. For bigger lathes or heavy cuts, closed loop system would be better.

It's entirely reasonable to locate the driver in the electrical cabinet and not under the lathe as shown above - but make sure to get the stepper with a shielded cable in that case.

It's suggested to run the stepper in the 200 steps mode, microstepping will reduce the torque and will make Arduino spend more time issuing steps, potentially lowering the maximum usable rpm.

### Encoder

Tested with the [following 600 steps encoder](https://www.amazon.de/-/en/gp/product/B015GYY7XU) but 200 and 400 step encoders will also work. It's possible to salvage one of these from an old printer, they are also readily available on AliExpress as "optical rotary encoder".

### Arduino Nano

The code was tested using an Arduino Nano V3 clone.

### OLED display

SSD1306 monochrome 4-pin I2C OLED 128x64 display.

### Buttons

Using 6x6x13mm switches. 13mm is the optimal height for the provided case, if you're using a different case, desired height might be different. AliExpress has very convenient 200 button sets of different height for a few euros.

### 24V power supply

[24V 5A power supply](https://www.ebay.com/itm/173522502114) worked well. Stepper driver allows picking the current, 2A current was so far sufficient for my small lathe so power supply is running in the light mode.

### 5A power supply

Arduino Nano doesn't draw much current so 0.5A phone charger would work.

### PCB

![NanoEls H1 PCB](https://github.com/kachurovskiy/nanoels/blob/main/h1/pcb/nanoels-pcb-h1.png)

[Gerber ZIP for production](https://github.com/kachurovskiy/nanoels/blob/main/h1/pcb/nanoels-pcb-h1.zip)

It's a 70mm by 90mm board with holes for M3 mounting bolts, 1.6mm thick. You will need clearance above, below and on the sides of the board for the through-hole components, their pins (legs) and wires coming into the PCB.

PCB is best placed away from the electromagnetic noise sources such as lathe motor wires. Grounded metal housing is ideal.

**Some PCB production techniques use lead and other nasty stuff. Order at your own risk and dispose properly.**

Ordering it from JLCPCB takes just a few clicks - upload the ZIP file, use all default settings, choose shipping and checkout.

#### Leadscrew gear

Ideally, a 50 tooth metal gear (~8mm thick) from the original lathe gear set would be used.

### 3D-printed parts

#### Case

![Case](https://github.com/kachurovskiy/nanoels/raw/main/h1/case/case-120mm-2m6-2m5-4m3.png)

[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/case/case-120mm-2m6-2m5-4m3.stl)

This case is designed for the 120mm wide lathe base with two holes for M5 bolts on the bottom plate.

Stepper driver DM556Y is mounted onto the case with 2 M6 bolts, washers and nuts.

PCB is mounted onto the case with 4 M3 bolts.

Case is covering the stepper from the metal chips.

#### Stepper mount

![Stepper mount](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-mount-nema23-28mm-hole.png)

[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-mount-nema23-28mm-hole.png)

Dimensions of the lead screw front bearing housing for the provided 3D-printed part to fit: 28mm outside diameter, 12mm wide.

Stepper should rest on e.g. a piece of rubber when attached to the lathe - provided 3D printed part is only held by friction and is not designed to hold the full weight of the stepper long term.

#### Stepper gear

![Stepper gear](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-gear-nema23-50t-10mm-10mm.png)

[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-gear-nema23-50t-10mm-10mm.png)

This gear is designed to fit the NEMA 23 shaft (10mm diameter / 9.5mm narrow dimension) without any set screws. Gear is 10mm wide, entire part is 20mm wide.

Using this gear can be very noisy on certain RPMs.

##### Alternative: adapter for lathe gear

![Stepper gear adapter](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-to-gear-adapter-12mm-10mm.png)
[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/stepper/stepper-to-gear-adapter-12mm-10mm.png)

If you have 2 metal gears that add up to 100 tooth together (e.g. 2x50 tooth gears) that came with the lathe, it's possible to simply use one of them on the leadscrew and one on the stepper with the help of the adapter above. It can be somewhat noisy on certain RPMs but otherwise works well.

##### Alternative: 2 printed 20 tooth pulleys with a 300mm HTD 5M belt

I'm exploring this option to reduce the gear noise, will update once I have the results.

#### Encoder base

![Encoder base](https://github.com/kachurovskiy/nanoels/raw/main/h1/encoder/encoder-base-38.5mm-hole-m4-screw.png)

[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/encoder/encoder-base-38.5mm-hole-m4-screw.png)

To be glued to the lathe wall with the double-sided carpet sticky tape. Holds well if surfaces are properly cleaned with e.g. Acetone.

Using an M4 set screw is optional.

#### Encoder gear

![Encoder gear](https://github.com/kachurovskiy/nanoels/raw/main/h1/encoder/encoder-gear-60t-6.1mm-bore.png)

[STL file](https://github.com/kachurovskiy/nanoels/raw/main/h1/encoder/encoder-gear-60t-6.1mm-bore.png)

Check the distance between the spindle gear and the lathe housing: for the provided conical gear to fit, it has to be 23mm.

Encoder gear should fit loosely to the spindle allowing for it to move ~1 degree back and forth when the spindle is idle - it reduces the noise and forces applied to the encoder.

## Assembly

**Working with electrical wiring is dangerous, unplug the lathe. Proceed at your own risk.**

Connect the 24V and 5V power supplies to the lathe power so that the lathe on/off and safety switches cut off the power for the ELS too.

Make sure Arduino Nano is working before soldering it on, unsoldering it without a desoldering station is very hard.

Carefully solder 10 buttons (6X6X11 switches to fit the provided case), OLED 128x64 4-pin display and an Arduino Nano onto it.

![Assembly](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/h1-assembly.jpg)

Solder 5V/GND wires to the PCB. At this point it can be powered up, display should work.

Solder encoder and stepper driver wires to the PCB according to the input/output labels on the PCB.

## Gears

When connecting the gears, make sure to leave ~0.5mm space between them for optimal threading. This can be achieved e.g. by temporarily placing a piece of paper between them. Add grease and spread it between the gear teeth, remove the excess.

## Programming the Arduino

- Download the Arduino IDE
- Install `Adafruit_SSD1306` library via the Library Manager in the Arduino IDE
- Download and open [NanoEls.ino](https://github.com/kachurovskiy/nanoels/raw/main/h1/NanoEls.ino)
- Check the top 7 constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Upload the sketch to your Arduino Nano
- Swap D2 and D3 pins in the code if carriage direction is inverted, re-upload

# Operating the ELS

## Safety

- Make sure that stepper motor and ELS are turned off using the lathe emergency power off switch
- Test the automatic stop and other ELS functionality before relying on it
- **In case of unexpected movements, disengage the half-nut or use the emergency power off switch**
- **ELS buttons might not respond when stepper is working**

## Turning

- Select the desired pitch using `-` and `+` buttons or `0.05mm`, `1mm` and `2mm` shortcut buttons in the top row
- Turn on the lead screw using the `ON` button
- Start the lathe spindle
- **Warning: it's not currently possible to turn `OFF` the ELS while spindle is running due to Arduino Nano limitations**
- Stop the lathe spindle when done
- Turn off the lead screw using the `ON` button

## Automatic stops

- Move the carriage with the help of ELS to the desired stop position
  - Moving the carriage manually may introduce a small error due to backlash
- Set the stop using the `L STOP` button
- Use ELS to move to another stop position and press `R STOP`

Now you can:

- Use lathe forward/reverse spindle movements to move the carriage between the stops
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more when required to stay on the thread) within the stops in either direction when spindle is not turning
  - Moving exactly onto the stop with `LEFT` and `RIGHT` buttons is not currently supported, carriage will only go to the closest thread position to the stop

Setting only one stop is also supported. Stops aren't lost when `ON` button is clicked or pitch is changed.

## Carriage movements

- Make sure the cutting tool is not goign to contact the material and there's room to move the carriage physically
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more when required to stay on the thread) when spindle is not turning
- If stops are set, they will be respected

Using `LEFT` and `RIGHT` buttons when ELS is ON and spindle is turning is undefined

## Losing the thread

The spindle and stepper positions are reset to 0 every time one of the following happens:

- `ON` button is pressed (including long press for reset)
- Pitch is changed e.g. by pressing `-` or `+`
- Stepper is not in the desired position when ELS is powered up
  - Results in `LTW` lost thread warning
  - Can happen e.g. if spindle was running above max rpm supported by ELS and/or shutdown abruptly

Thread is **not** lost when ELS is simply powered off.

## Out-of-sync situations

It's possible for the lead screw to go out of sync with the spindle by removing the `L STOP` or `R STOP` while the carriage is standing on it. It's indicated by the `SYN` word on the display.

This situation should resolve itself once the spindle makes a full turn.

## Resetting ELS and viewing the software version

ELS remembers all the positions and ON/OFF status when powered off.

- Hold `ON` button for 6 seconds
  - Reset stepper and spindle positions to 0
  - Resets pitch to 0
  - Removes stops
  - Removes out-of-sync state
  - Shows NanoEls version

# Contributing to the project

- Questions: please file a GitHub Issue
- Successful/failed builds: please file a GitHub Issue with explanations and photos
- Code changes: please only make the necessary minimal edits
  - Split unrelated changes into separate PRs
- PCB changes: incompatible changes (move button / display / Arduino / change PCB size / change used pin purpose) will require making `h2` folder with another hardware version of the project, please file an Issue first to confirm. Backward-compatible PCB changes are cool.
- 3D models: in most cases, don't edit the model, add a new file. Also include the PNG preview and a dimension drawing if possible.

# Example builds

[![NanoEls demo video](https://img.youtube.com/vi/9uTdDk2EqG4/0.jpg)](https://www.youtube.com/watch?v=9uTdDk2EqG4?t=272)