#include "../src/Servo/ServoConfig.h"
#include "Sensor/SensorConfig.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button/Btn.h"

using namespace ServoConfiguration;
using namespace Sensor;
using namespace Button;

constexpr int BAUD_RATE = 9600;
bool isTurnOn = false;
int goodProductCount = 0;

ServoConfig servoAc(10, 0, 90, 500); // Servo 1 trên chân 10
SensorConfig sensorHeight(A0, TYPE_HEIGHT, 600);        // Cảm biến chiều cao trên chân A0
SensorConfig sensorStart(A1, TYPE_START, 600);          // Cảm biến bắt đầu trên chân A1
Btn buttonStart(7, TURN_ON);                                // Nút khởi động trên chân 7
LiquidCrystal_I2C lcd(0x27, 16, 2);         // Khởi tạo LCD với địa chỉ 0x27 và kích thước 16x2
Btn buttonStop(8, TURN_OFF);                                // Nút dừng trên chân 8

void lcdInit();
void systemProcess(); // Quá trình chính của hệ thống

void setup() {
    Serial.begin(BAUD_RATE);
    Serial.println("Starting servo test");
    lcdInit();        // Khởi tạo LCD
    Serial.println("LCD initialized");
    servoAc.init();  // Khởi tạo servo
}

void loop() {
    // Xử lý nút Start
    if (digitalRead(buttonStart.getPin()) == LOW) {
        if (!isTurnOn) {
            isTurnOn = true;
            lcd.clear();
            lcd.print("GOOD PR: ");
            lcd.print(goodProductCount);
            delay(500); // Chống dội phím
        }
    }

    // Xử lý nút Stop
    if (digitalRead(buttonStop.getPin()) == LOW) {
        if (isTurnOn) {
            isTurnOn = false;
            lcd.clear();
            lcd.print("SYSTEM OFF");
            delay(500); // Chống dội phím
        }
    }

    // Logic hệ thống khi đang bật
    if (isTurnOn) {
        int valStart = sensorStart.getValue();
        int threshStart = sensorStart.getThreshold();

        // Nếu cảm biến Start phát hiện vật (giá trị < ngưỡng)
        if (valStart < threshStart) {
            // Đợi một chút để vật đi vào vị trí ổn định (tùy chỉnh thời gian này)
            delay(100);

            int valHeight = sensorHeight.getValue();
            int threshHeight = sensorHeight.getThreshold();

            // Kiểm tra cảm biến chiều cao
            if (valHeight < threshHeight) {
                // Cả 2 đều < ngưỡng -> Đạt yêu cầu
                goodProductCount++;
                lcd.setCursor(9, 0); // Vị trí sau "GOOD PR: "
                lcd.print(goodProductCount);
            } else {
                // Chỉ Start < ngưỡng, Height >= ngưỡng -> Không đạt -> Gạt
                servoAc.goPush();
                servoAc.goIdle();
            }

            // Chờ vật đi qua hết cảm biến Start để tránh đếm lặp lại
            while (sensorStart.getValue() < threshStart) {
                delay(10);
            }
        }
    }
}

/**
 * Khởi tạo LCD
 */
void lcdInit() {
    lcd.init();      // Khởi tạo LCD
    lcd.backlight(); // Bật đèn nền LCD
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM OFF");
}

/**
 * Quá trình chính của hệ thống
 */
void systemProcess() {
    if (sensorHeight.getValue() != -1 || sensorStart.getValue() != -1) {
        Serial.println("Sensor Height: " + String(sensorHeight.getValue()));
        Serial.println("Sensor Start: " + String(sensorStart.getValue()));
    }
}

