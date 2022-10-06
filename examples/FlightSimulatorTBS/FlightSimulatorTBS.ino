#include "Joystick.h"
#include "crsf.h"

// #define __DEBUG

#define MIN_CH     172
#define MAX_CH     1812

Joystick_ Joystick(
      JOYSTICK_DEFAULT_REPORT_ID,
      JOYSTICK_TYPE_JOYSTICK,       // 0x04
      0,      // button Count
      0,      // hat switch count
      true,   // include X Axis *
      true,   // include Y Axis *
      true,   // include Z Axis
      true,   // include Rx Axis rotation
      true,   // include Ry Axis
      true,   // include Rz Axis
      true,   // include Rudder   *
      true,   // include Throttle *
      true,   // include Accelerator
      true,   // include Brake
      true    // include Steering
);

CRSF crsf(Serial1);

void setup() {
#ifdef __DEBUG
  Serial.begin(9600);
#else
  Joystick.begin(false);
  Joystick.setXAxisRange(MIN_CH, MAX_CH);
  Joystick.setYAxisRange(MIN_CH, MAX_CH);
  Joystick.setZAxisRange(MIN_CH, MAX_CH);

  Joystick.setRxAxisRange(MIN_CH, MAX_CH);
  Joystick.setRyAxisRange(MIN_CH, MAX_CH);
  Joystick.setRzAxisRange(MIN_CH, MAX_CH);

  Joystick.setRudderRange(MIN_CH, MAX_CH);
  Joystick.setThrottleRange(MIN_CH, MAX_CH);

  Joystick.setAcceleratorRange(MIN_CH, MAX_CH);
  Joystick.setBrakeRange(MIN_CH, MAX_CH);
  Joystick.setSteeringRange(MIN_CH, MAX_CH);

#endif
  crsf.begin();
}

void loop() {
  crsf.process();
#ifdef __DEBUG
  for (int i = 0; i < 12; i++) {
    int value = crsf._channels[i];
    Serial.print(value);
    Serial.print(" ");
  }
  Serial.println();
#else

  Joystick.setXAxis      (crsf._channels[0]);
  Joystick.setYAxis      (crsf._channels[1]);
  Joystick.setZAxis      (crsf._channels[2]);
  Joystick.setRxAxis     (crsf._channels[3]);
  Joystick.setRyAxis     (crsf._channels[4]);
  Joystick.setRzAxis     (crsf._channels[5]);

  Joystick.setRudder     (crsf._channels[6]);
  Joystick.setThrottle   (crsf._channels[7]);

  Joystick.setAccelerator(crsf._channels[8]);
  Joystick.setBrake      (crsf._channels[9]);
  Joystick.setSteering   (crsf._channels[10]);

  Joystick.sendState();

#endif
}
