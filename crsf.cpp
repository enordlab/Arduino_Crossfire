#include "crsf.h"
#include <Arduino.h>

void CRSF::begin() {
    for (byte i = 0; i<18; i++) {
        _channels[i]      = 0;
    }
    _serial.begin(420000, SERIAL_8N1);  // for crsf : parity no, stop 1
}

void CRSF::process() {
    static byte buffer[26];
	static byte * frame_buffer = buffer + 2;
    static byte buffer_index = 0;

    while (_serial.available()) {
        byte rx = _serial.read();
        if (buffer_index == 0 && rx != CSRF_ADDRESS) {
            //incorrect start byte, out of sync
            continue;
        }
        if (buffer_index == 1 && rx != CSRF_LENGTH) {
            //incorrect start byte, out of sync
            continue;
        }
        if (buffer_index == 2 && rx != CSRF_FRAMEID) {
            //incorrect start byte, out of sync
            continue;
        }

        buffer[buffer_index++] = rx;

        if (buffer_index == 26) {
            buffer_index = 0;

            _channels[0]  = ((frame_buffer[1]    |frame_buffer[2]<<8)                 & 0x07FF);
            _channels[1]  = ((frame_buffer[2]>>3 |frame_buffer[3]<<5)                 & 0x07FF);
            _channels[2]  = ((frame_buffer[3]>>6 |frame_buffer[4]<<2 |frame_buffer[5]<<10)  & 0x07FF);
            _channels[3]  = ((frame_buffer[5]>>1 |frame_buffer[6]<<7)                 & 0x07FF);
            _channels[4]  = ((frame_buffer[6]>>4 |frame_buffer[7]<<4)                 & 0x07FF);
            _channels[5]  = ((frame_buffer[7]>>7 |frame_buffer[8]<<1 |frame_buffer[9]<<9)   & 0x07FF);
            _channels[6]  = ((frame_buffer[9]>>2 |frame_buffer[10]<<6)                & 0x07FF);
            _channels[7]  = ((frame_buffer[10]>>5|frame_buffer[11]<<3)                & 0x07FF);
            _channels[8]  = ((frame_buffer[12]   |frame_buffer[13]<<8)                & 0x07FF);
            _channels[9]  = ((frame_buffer[13]>>3|frame_buffer[14]<<5)                & 0x07FF);
            _channels[10] = ((frame_buffer[14]>>6|frame_buffer[15]<<2|frame_buffer[16]<<10) & 0x07FF);
            _channels[11] = ((frame_buffer[16]>>1|frame_buffer[17]<<7)                & 0x07FF);
            _channels[12] = ((frame_buffer[17]>>4|frame_buffer[18]<<4)                & 0x07FF);
            _channels[13] = ((frame_buffer[18]>>7|frame_buffer[19]<<1|frame_buffer[20]<<9)  & 0x07FF);
            _channels[14] = ((frame_buffer[20]>>2|frame_buffer[21]<<6)                & 0x07FF);
            _channels[15] = ((frame_buffer[21]>>5|frame_buffer[22]<<3)                & 0x07FF);
        }
    }
}
