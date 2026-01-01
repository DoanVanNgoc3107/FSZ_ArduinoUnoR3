//
// Created by ngoc1 on 1/1/2026.
//

#ifndef FSZ_ARDUINOUNOR3_SENSORCONFIG_H
#define FSZ_ARDUINOUNOR3_SENSORCONFIG_H

namespace Sensor {
    /**
     * Loại cảm biến
     */
    enum SensorType {
        TYPE_HEIGHT = 0,
        TYPE_START = 1,
    };

    class SensorConfig {
        int pin = 0;
        SensorType type = TYPE_HEIGHT;

    public:
        // Constructor
        SensorConfig(int pin, SensorType type);

        // Getter: Lấy chân cảm biến (Inline - tốt cho hiệu năng)
        int getPin() const {
            return pin;
        }

        // Getter: Lấy loại cảm biến (Inline)
        SensorType getType() const {
            return type;
        }

        // Lấy giá trị cảm biến
        int getValue() const;

        // Setter
        void setPin(int newPin);
        void setType(SensorType newType);

        // Helper
        bool isValueValid(int value) const;
    };
} // namespace Sensor

#endif //FSZ_ARDUINOUNOR3_SENSORCONFIG_H
