#ifndef CRSF_h
#define CRSF_h

#include "Arduino.h"

#define CSRF_ADDRESS        0xC8 // 0xEE
#define CSRF_LENGTH         0x18
#define CSRF_FRAMEID        0x16

class CRSF {
    public:
        CRSF(HardwareSerial & serial) : _serial (serial) {}
        void begin();
        void process();
        volatile int _channels[18];
    private:
        HardwareSerial & _serial;
};

#endif

//
// == sbus
// 0    1            22   23      24
// 0x0F -- 22 bytes --            footer
// head
// Byte[23]
//       Bit 7: channel 17 (0x80)
//       Bit 6: channel 18 (0x40)
//       Bit 5: frame lost (0x20)
//       Bit 4: failsafe activated (0x10)

//
// == crsf
// Address
//     BROADCAST ADDRESS: 0x00
//     FLIGHT CONTROLLER ADDRESS : 0xC8
//     RADIO ADDRESS: 0xEA
//     MODULE ADDRESS: 0xEE
// Frame id
//     GPS_ID: 0x02
//     CF_VARIO_ID: 0x07
//     BATTERY_ID: 0x08
//     LINK_ID: 0x14
//     CHANNELS_ID: 0x16
//     ATTITUDE_ID: 0x1E
//     FLIGHT_MODE_ID: 0x21
//     PING_DEVICES_ID: 0x28
//     DEVICE_INFO_ID: 0x29
//     REQUEST_SETTINGS_ID: 0x2A

// 16ch * 11bit = 176bit = 22bytes

//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
// C8 18 16 F0 00 1F F8 C0 C7 0A 56 80 0F 7C C0 00 06 30 80 01 3E F0 81 0F 7C AA 26bytes CHANNELS_ID
// C8 0C 14 22 00 4B 5B 00 01 03 1B 64 62 C5                                     12bytes LINK_ID
