//
// Created by ngoc1 on 1/1/2026.
//

#include "ServoConfig.h"
#include <Servo.h>
#include <Arduino.h>

namespace ServoConfiguration {
    /**
     * Khởi tạo cấu hình servo
     * @param pin Chân điều khiển servo
     * @param angleIdle Góc chờ của servo
     * @param anglePush Góc gạt bỏ vật thể không đạt
     * @param delayTime Thời gian delay khi servo hoạt động
     * @brief Khởi tạo cấu hình servo và đặt servo khởi động servo (Test servo) và đưa về góc chờ
     * @return void
     */
    ServoConfig::ServoConfig(int const pin, int const angleIdle, int const anglePush, unsigned long const delayTime)
        : pin(pin), angleIdle(angleIdle), anglePush(anglePush), delayTime(delayTime) {
        // servo.attach(pin); // Gắn servo vào chân điều khiển - REMOVED: Should be in init()
    }

    /**
     * Hàm lấy chân điều khiển servo
     * @return int Chân điều khiển servo
     */
    int ServoConfig::getPin()  {
        return pin;
    }

    /**
     * Hàm khởi tạo servo, đưa servo về góc chờ
     */
    void ServoConfig::init() {
        servo.attach(pin);          // Gắn chân servo
        goPush();                  // Test servo
        goIdle();                  // Đưa về góc chờ
    }

    /**
     * Hàm lấy góc ban đầu của servo (khi không có vật thể hoặc vật thể đạt)
     * @return int Góc ban đầu của servo
     */
    int ServoConfig::getAngleIdle()  {
        return angleIdle;
    }

    /**
     * Hàm lấy góc để loại bỏ vật thể không đạt
     * @return int Góc để loại bỏ vật thể không đạt
     */
    int ServoConfig::getAnglePush()  {
        return anglePush;
    }

    /**
     * Hàm lấy thời gian delay khi servo hoạt động
     * @return int Thời gian delay khi servo hoạt động
     */
    unsigned long ServoConfig::getDelayTime()  {
        return delayTime;
    }

    /**
     * Hàm lấy góc hiện tại của servo
     * @return int Góc hiện tại của servo
     */
    void ServoConfig::setPin(int const newPin) {
        pin = newPin;
        servo.attach(pin);
    }

    /**
     * Hàm đặt góc ban đầu của servo
     * @param newAngleIdle Góc ban đầu của servo
     */
    void ServoConfig::setAngleIdle(int  newAngleIdle) {
        angleIdle = newAngleIdle;
    }

    /**
     * Hàm đặt góc để loại bỏ vật thể không đạt
     * @param newAnglePush Góc để loại bỏ vật thể không đạt
     */
    void ServoConfig::setAnglePush(int newAnglePush) {
        anglePush = newAnglePush;
    }

    /**
     * Hàm di chuyển servo về góc ban đầu
     */
    void ServoConfig::goIdle() {
        servo.write(angleIdle);
        delay(delayTime); // Chờ servo di chuyển
    }

    /**
     * Hàm di chuyển servo đến góc gạt vật thể
     */
    void ServoConfig::goPush() {
        servo.write(anglePush);
        delay(delayTime); // Chờ servo di chuyển
    }

    /**
     * Hàm đặt thời gian delay khi servo hoạt động
     * Khi được gọi, hàm sẽ tạm dừng thực thi trong khoảng thời gian đã định trước khi tiếp tục thực thi các lệnh tiếp theo.
     */
    void ServoConfig::delayAction() {
        unsigned long currentTime = millis();
        while (millis() - currentTime < delayTime) {
            // Chờ đợi
        }
    }

    /**
     * Hàm đặt thời gian delay khi servo hoạt động
     * @param newDelayTime Thời gian delay khi servo hoạt động
     */
    void ServoConfig::setDelayTime(unsigned long const newDelayTime) {
        delayTime = newDelayTime;
    }
}
