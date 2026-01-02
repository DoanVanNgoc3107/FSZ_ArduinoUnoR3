//
// Created by ngoc1 on 1/1/2026.
//

#ifndef FSZ_ARDUINOUNOR3_SERVOCONFIG_H
#define FSZ_ARDUINOUNOR3_SERVOCONFIG_H
#include <Servo.h>

namespace ServoConfiguration {
    class ServoConfig {
        int pin = 0;         // Chân điều khiển servo
        int angleIdle = 0;   // Góc ban đầu của servo
        int anglePush = 0;   // Góc để loại bỏ vật thể không đạt
        Servo servo;         // Đối tượng servo điều khiển thực tế
        unsigned long delayTime = 200; // Thời gian delay khi servo hoạt động
    public:
        ServoConfig(int pin, int angleIdle, int anglePush, unsigned long delayTime = 200);

        void init();

        // Getters
        int getPin() ;

        int getAngleIdle() ;

        int getAnglePush() ;

        unsigned long getDelayTime() ;

        // Setters
        void setPin(int newPin);

        void setDelayTime(unsigned long newDelayTime);

        void setAngleIdle(int newAngleIdle);

        void setAnglePush(int newAnglePush);

        void goIdle();

        void delayAction();

        void goPush();
    };
}

#endif // FSZ_ARDUINOUNOR3_SERVOCONFIG_H
