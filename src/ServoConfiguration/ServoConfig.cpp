//
// Created by ngoc1 on 1/1/2026.
//

#include "ServoConfig.h"
#include <Arduino.h>
#include <Servo.h>

namespace ServoConfiguration {
    /**
     * Khởi tạo cấu hình servo
     * @param pin Chân điều khiển servo
     * @param angleHome Góc ban đầu của servo
     * @param angleBad Góc để loại bỏ vật thể không đạt
     * @param delayTime Thời gian delay khi servo hoạt động
     * @brief Khởi tạo cấu hình servo và đặt servo khởi động servo (Test servo) và đưa về góc ban đầu
     * @return void
     */
    ServoConfig::ServoConfig(int const pin,int const angleHome, int const angleBad, int const delayTime)
            : pin(pin), angleHome(angleHome), angleBad(angleBad), delayTime(delayTime) {
        servo.attach(pin);     // Gắn servo vào chân điều khiển
        servo.write(angleBad); // Chạy servo đến góc loại bỏ vật thể không đạt
        delay(delayTime);      // Chờ servo di chuyển
        servo.write(angleHome);// Đặt servo về góc ban đầu
    }

    /**
     * Hàm lấy chân điều khiển servo
     * @return int Chân điều khiển servo
     */
    int ServoConfig::getPin() const {
        return pin;
    }

    /**
     * Hàm lấy góc ban đầu của servo (khi không có vật thể hoặc vật thể đạt)
     * @return int Góc ban đầu của servo
     */
    int ServoConfig::getAngleHome() const {
        return angleHome;
    }

    /**
     * Hàm lấy góc để loại bỏ vật thể không đạt
     * @return int Góc để loại bỏ vật thể không đạt
     */
    int ServoConfig::getAngleBad() const {
        return angleBad;
    }

    /**
     * Hàm lấy thời gian delay khi servo hoạt động
     * @return int Thời gian delay khi servo hoạt động
     */
    int ServoConfig::getDelayTime() const {
        return delayTime;
    }

    /**
     * Hàm lấy góc hiện tại của servo
     * @return int Góc hiện tại của servo
     */
    void ServoConfig::setPin(int const newPin) {
        pin = newPin;
    }

    /**
     * Hàm đặt góc ban đầu của servo
     * @param newAngleHome Góc ban đầu của servo
     */
    void ServoConfig::setAngleHome(int const newAngleHome) {
        angleHome = newAngleHome;
    }

    /**
     * Hàm đặt góc để loại bỏ vật thể không đạt
     * @param newAngleBad Góc để loại bỏ vật thể không đạt
     */
    void ServoConfig::setAngleBad(int const newAngleBad) {
        angleBad = newAngleBad;
    }

    /**
     * Hàm di chuyển servo về góc ban đầu
     */
    void ServoConfig::goHome() {
        servo.write(angleHome);
    }

    /**
     * Hàm đặt thời gian delay khi servo hoạt động
     * @param newDelayTime Thời gian delay khi servo hoạt động
     */
    void ServoConfig::setDelayTime(int const newDelayTime) {
        delayTime = newDelayTime;
    }
}