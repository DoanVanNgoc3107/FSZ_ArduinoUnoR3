//
// Created by ngoc1 on 1/1/2026.
//

#include "SensorConfig.h"
#include <Arduino.h>

namespace Sensor {

    /**
     * Khởi tạo cấu hình cảm biến
     */
    SensorConfig::SensorConfig(int const pin, SensorType const type) : pin(pin), type(type) {
        pinMode(pin, INPUT);
    }

    /**
     * Lấy giá trị cảm biến
     * @return Giá trị cảm biến, -1 nếu không hợp lệ
     */
    int SensorConfig::getValue() const {
        int const val = analogRead(pin);
        return isValueValid(val) ? val : -1;
    }

    /**
     * Thiết lập chân cảm biến
     * @param newPin Chân cảm biến mới
     */
    void SensorConfig::setPin(int const newPin) {
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
     * Kiểm tra giá trị hợp lệ
     * @param value Giá trị cần kiểm tra
     * @return true nếu giá trị hợp lệ, false nếu không hợp lệ
     */
    bool SensorConfig::isValueValid(int const value) const {
        return (value >= 0 && value <= 1023);
    }

} // namespace Sensor