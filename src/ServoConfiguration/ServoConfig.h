//
// Created by ngoc1 on 1/1/2026.
//

#ifndef FSZ_ARDUINOUNOR3_SERVOCONFIG_H
#define FSZ_ARDUINOUNOR3_SERVOCONFIG_H
#include <Servo.h>

namespace ServoConfiguration {
    class ServoConfig {
        int pin = 0;        // Chân điều khiển servo
        int angleIdle = 0;  // Góc ban đầu của servo
        int anglePush = 0;   // Góc để loại bỏ vật thể không đạt
        Servo servo;        // Đối tượng servo điều khiển thực tế
        int delayTime = 200; // Thời gian delay khi servo hoạt động
    public:
        ServoConfig(int pin, int angleIdle, int anglePush, int delayTime = 200);

        // Getters
        int getPin() const;

        int getAngleIdle() const;

        int getAnglePush() const;

        int getDelayTime() const;

        // Setters
        void setPin(int newPin);

        void setDelayTime(int newDelayTime);

        void setAngleIdle(int newAngleIdle);

        void setAnglePush(int newAnglePush);

        void goIdle();
    };
}

#endif // FSZ_ARDUINOUNOR3_SERVOCONFIG_H
