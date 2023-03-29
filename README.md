# Arduino library for TBS CrossFire

Read CRSF channel on Arduino Pro Micro (a32u4).
Draft code for making TBS Crossfire simulator usb dongle.

example/FlightSimulatorTBS
- TBS Crossfire simulator usb dongle.
- Joystick Library : https://github.com/MHeironimus/ArduinoJoystickLibrary
- a32u4 based Arduino board is used to config USB HID.
- Youtube : https://www.youtube.com/watch?v=gVdIRlaZiAA

## Basic Installation

```
$ cd <arduino-sketchbook>/libraries
$ git clone https://github.com/enordlab/Arduino_Crossfire.git
```

## About SBUS, CSRF Protocol

SBUS protocol baud rate is 100,000. and signal is inverted.

SBUS frame is 25bytes.

- Byte[0]: SBUS header, 0x0F
- Byte[1 -22]: 16 servo channels, 11 bits each
- Byte[23]
  - Bit 0: channel 17 (0x01)
  - Bit 1: channel 18 (0x02)
  - Bit 2: frame lost (0x04)
  - Bit 3: failsafe activated (0x08)
- Byte[24]: SBUS footer

CrossFire Protocol baud rate is 420,000. not inverted.

CSRF frame length depends on Framd ID : 26bytes fpr CHANNELS_ID, 12bytes for LINK_ID.

CSRF protocol is used for both RX and TX : radio and telemetry.

- Byte[0]: Device Address
  - BROADCAST ADDRESS: 0x00
  - FLIGHT CONTROLLER ADDRESS : 0xC8
  - RADIO ADDRESS: 0xEA
  - MODULE ADDRESS: 0xEE
- Byte[1]: Length
- Byte[2]: Frame ID
  - GPS_ID: 0x02
  - CF_VARIO_ID: 0x07
  - BATTERY_ID: 0x08
  - LINK_ID: 0x14
  - CHANNELS_ID: 0x16
  - ATTITUDE_ID: 0x1E
  - FLIGHT_MODE_ID: 0x21
  - PING_DEVICES_ID: 0x28
  - DEVICE_INFO_ID: 0x29
  - REQUEST_SETTINGS_ID: 0x2A
- Byte[3 -(length-1)]
- Byte[length] : CRC8


The program filters the RX stream starting with C8 18 16 as address, length, frame id.

Others are ignored.

The program ignores CRC8 value.

