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
        int threshold = 500; // Ngưỡng mặc định
        bool detected = false;

    public:
        // Constructor
        SensorConfig(int pin, SensorType type, int threshold);

        // Hàm tạo không tham số ngưỡng
        SensorConfig(int pin, SensorType type);

        // Getter: Lấy chân cảm biến (Inline - tốt cho hiệu năng)
        int getPin() ;

        // Getter: Lấy loại cảm biến (Inline)
        SensorType getType() ;

        // Lấy giá trị cảm biến
        int getValue() ;

        // Lấy ngưỡng cảm biến
        int getThreshold() ;

        // Setter
        void setPin(int newPin);

        // Đặt loại cảm biến
        void setType(SensorType newType);

        // Kiểm tra cảm biến có được phát hiện hay không
        bool isDetected() ;

        // Kiểm tra giá trị có hợp lệ khôngs
        bool isValueValid(int value) ;
    };
} // namespace Sensor

#endif //FSZ_ARDUINOUNOR3_SENSORCONFIG_H
