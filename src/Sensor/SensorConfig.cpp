//
// Created by ngoc1 on 1/1/2026.
//

#include "SensorConfig.h"
#include <Arduino.h>

namespace Sensor {
    /**
     * Khởi tạo cấu hình cảm biến
     * @param pin Chân cảm biến
     * @param type Loại cảm biến
     * @param threshold Ngưỡng cảm biến
     */
    SensorConfig::SensorConfig(int  pin, SensorType  type, int  threshold)
        : pin(pin), type(type), threshold(threshold) {
        pinMode(pin, INPUT);
    }

    /**
     * Khởi tạo cấu hình cảm biến
     * @param pin Chân cảm biến
     * @param type Loại cảm biến
     */
    SensorConfig::SensorConfig(int  pin, SensorType  type) : pin(pin), type(type) {
        pinMode(pin, INPUT);
    }

    /**
     * Kiểm tra cảm biến có được phát hiện hay không
     * @return true nếu cảm biến được phát hiện, false nếu không được phát hiện
     */
    bool SensorConfig::isDetected()  {
        int  val = getValue();
        if (val < threshold) return false;
        return true;
    }

    /**
     * Lấy loại cảm biến
     * @return Loại cảm biến
     */
    SensorType SensorConfig::getType()  {
        return type;
    }

    /**
        * Lấy chân cảm biến
     * @return Chân cảm biến
     */
    int SensorConfig::getPin()  {
        return pin;
    }

    /**
     * Lấy giá trị cảm biến
     * @return Giá trị cảm biến, -1 nếu không hợp lệ
     */
    int SensorConfig::getValue()  {
        int  val = analogRead(pin);
        return isValueValid(val) ? val : -1;
    }

    /**
     * Thiết lập chân cảm biến
     * @param newPin Chân cảm biến mới
     */
    void SensorConfig::setPin(int  newPin) {
        pin = newPin;
        pinMode(pin, INPUT);
    }

    /**
     * Thiết lập loại cảm biến
     * @param newType Loại cảm biến mới
     */
    void SensorConfig::setType(SensorType newType) {
        type = newType;
    }

    /**
     * Lấy ngưỡng cảm biến
     * @return Ngưỡng cảm biến
     */
    int SensorConfig::getThreshold()  {
        return threshold;
    }

    /**
     * Kiểm tra giá trị hợp lệ
     * @param value Giá trị cần kiểm tra
     * @return true nếu giá trị hợp lệ, false nếu không hợp lệ
     */
    bool SensorConfig::isValueValid(int  value)  {
        return (value >= 0 && value <= 1023);
    }
} // namespace Sensor
