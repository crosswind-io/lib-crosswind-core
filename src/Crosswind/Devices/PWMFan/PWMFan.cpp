#include "PWMFan.h"

#if defined(DEVICE_PWM_FAN)

#include "Crosswind/Core/AnalogWrite/AnalogWrite.h"
#include "Crosswind/Core/Arduino/Arduino.h"

PWMFan::PWMFan(int pwm_pin, uint16_t max_rpm) : pwmPin(pwm_pin), maxRpm(max_rpm) {
  pinMode(pwmPin, OUTPUT);
  turnOff();
}

void PWMFan::turnOff() {
  setPWM(0);
}

uint16_t PWMFan::getMaxRPM() {
  return maxRpm;
}

uint16_t PWMFan::getRPM() {
  return static_cast<uint16_t>((currentPwm / 255) * maxRpm);
}

void PWMFan::setRPM(uint16_t rpm) {
  if (rpm == MAX_RPM || rpm >= maxRpm) {
    setPWM(255);
  } else {
    setPWM((rpm / maxRpm) * 255);
  }
}

double PWMFan::getSpeed() {
  return static_cast<double>((currentPwm / 255) * 100.0);
}

void PWMFan::setSpeed(double speed) {
  if (speed >= 100.0) {
    setPWM(255);
  } else {
    setPWM((speed / 100) * 255);
  }
}

void PWMFan::setPWM(uint8_t pwm) {
  currentPwm = pwm;
  analogWrite(pwmPin, currentPwm);
}

#else
  #pragma message("Feature [Device/PWMFan]: DISABLED")
#endif // DEVICE_PWM_FAN
