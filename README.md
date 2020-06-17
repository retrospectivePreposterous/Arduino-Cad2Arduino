![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Cad2Arduino-logo.png?raw=true)

# Cad2Arduino
> Arduino core to allow Cad software to interact with hardware devices and IoT systems.

## Table of Contents

- [Requirements](#requirements)
- [Installation](#installation)
- [Wiring](#wiring)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)


# Requirements
**Software**

- Arduino IDE. Download for free at https://www.arduino.cc/
- Windows OS (Tested on Windows 8 and higher versions).
- Powershell ISE.
- Cad software compatible with AutoLISP scripting. 
  - Autocad or any of its verticals (Tested on Autocad 2019 and Civil 3D 2019).
  - BricsCad.
  - BabaCad.
  - Archicad.

**Hardware**

Cad2Arduino is an extensible core designed to allow more than the suggested hardware. However, the default version is assemblied with the following hardware:
- Arduino Mega 2560. Arduino Nano or Uno are suitable.
- 0.96 Inch Oled display.
- 8x8 Led Matrix Module MAX7219.
- SG90 Microservo.
- 3V-12V Passive buzzer.
- 5mm LED.
- 220Ω resistor.
- Wire jumpers.
- Mini breadboard.

# Setup
1. Do the wiring of your Arduino device. 
> If not having the Arduino Mega 2506 you can test Cad2Arduino in different boards by respecting the I/O pins.
> No need to have all components to run Cad2Arduino. The library can be extended.
2. Start Arduino IDE and install the following libraries:
  - Adafruit GFX.
  - Adafruit SSD1306.
  - Pitches.
  - Servo. By Michael Margolis.
  - Ledcontrol. By Eberhard Fahle.
3. Run Cad2Arduino in Arduino IDE and upload it into your board.
4. From now on you will be able to test it into Arduino Serial Monitor or Powershell `HandyCommandLine-ed01.ps1`.
5. Run your Cad software and upload the AutoLISP tools. 
6. Call AutoLISP functions by your Cad command line.

# Wiring Diagram

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/Graphic/Autocad2Arduino-WiringDiagram.png?raw=true)

# Commands
The Cad2Arduino library contains the following commands:
* text
* point
* circle
* fcircle
* line
* rectangle
* frectangle
* invert
* clear
* matrix
* servo
* sound
* 12on
* 12off



# HandyCommandLine setup

```powershell
$port = New-Object System.IO.Ports.SerialPort
$port.PortName = "COM7" #RENAME TO YOUR CURRENT PORT.
$port.BaudRate = "9600"
$port.open() 

Start-Sleep -Milliseconds 500
Write-Host " [HandyCommandLine 1.0 -- by retrospectivePreposterous]"
Write-Host " Enter EXIT to close. Readlines are disabled in this feature"
Write-Host "----------------------------------------------------------------"
do {
$codeline = Read-Host 
if ($codeline -ne "exit") {
$port.Write("$codeline`r") 
Start-Sleep -Milliseconds 500
}
} until ( $codeline -eq "exit" ) 

$port.close() 
```

# HandyCommandLine example

```shell
$ brew update
$ brew install fvcproductions
```

# Test samples

**Led Matrix:**
- The Led Matrix shows the Cad Object Entity as a common symbol.
- `EntityToMatrix_ETM.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/LedMatrix.gif?raw=true)

**Oled Display:**
- Property data of selected object is shown in the Oled Display.
- `PropertyToOled_PTO.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Oled.gif?raw=true)

**Servo:**
- Block orientation property is assimilated by the servo.
- `BlockAngleToServo_ATS.lsp` was used in this case.

![alt text](https://github.com/retrospectivePreposterous/Arduino-Cad2Arduino/blob/master/TestGIF/Servo.gif?raw=true)

