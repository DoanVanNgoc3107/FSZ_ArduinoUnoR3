/**
 * ---------------------------------------------------------------
 *  PROJECT: Product Classification System by Height (Arduino)
 *  AUTHOR : Doan Van Ngoc – 104317 – DTD64CL
 *  ADVISOR: MSc. Vu Thi Thu
 * ---------------------------------------------------------------
 *
 *  TEAM MEMBERS:
 *      • Phan Quy Luan   – 104304
 *      • Vu Quang Minh   – 104310
 *      • Vu Hai Thanh    – 104328
 *
 *  VERSION : 4.1.27.2
 *  DATE    : 20/11/2025
 *
 *  DESCRIPTION:
 *      Core implementation for an automated height-based product
 *      classification system using Arduino and embedded sensors.
 *      This file contains the essential logic, hardware mappings,
 *      and control flow of the complete system.
 *
 *  IMPORTANT NOTICE:
 *      DO NOT modify this source code unless you fully understand
 *      the execution flow and hardware interaction of the system.
 *
 *      If any unexpected behavior, malfunction, or bug is detected,
 *      please contact the maintainer:
 *          • Facebook: https://www.facebook.com/DoanVanNgoc317
 *          • Zalo : 0342204589
 *
 *  COPYRIGHT:
 *      Redistribution, re-uploading, or reuse of this source code
 *      in any form is strictly prohibited without explicit written
 *      permission from the original author — Doan Van Ngoc (104317).
 * ---------------------------------------------------------------
 */

#include <Arduino.h>
#include <Servo.h>

// ==== CẤU HÌNH CHÂN (PINS) ====
const int PIN_SERVO = 9;
const int PIN_SENSOR_HEIGHT = A0; // Cảm biến đo chiều cao (Đặt trên cao)
const int PIN_SENSOR_START  = A1; // Cảm biến phát hiện vật (Đặt thấp/Bắt đầu)

// ==== CẤU HÌNH THÔNG SỐ ====
const int BAUD_RATE = 9600;

// Ngưỡng cảm biến hồng ngoại (Vật cản -> Giá trị thấp)
// Bạn cần chỉnh biến trở trên cảm biến sao cho:
// - Không vật: ~900-1000
// - Có vật: < 100
const int THRESHOLD = 500;

// Góc Servo
const int ANGLE_PUSH = 70;  // Góc gạt
const int ANGLE_IDLE = 0;   // Góc chờ

// THỜI GIAN TRÔI (Rất quan trọng)
// Đây là thời gian vật đi từ Cảm biến đến Servo.
// Nếu Servo gạt sớm quá -> Tăng số này lên.
// Nếu Servo gạt trễ quá (vật đi qua rồi mới gạt) -> Giảm số này xuống.
const unsigned long TIME_TO_TRAVEL = 0; // 2000ms = 2 giây (Ví dụ)

Servo myServo;

// Trạng thái hệ thống
bool objectDetected = false;
bool isTallObject = false;
unsigned long timeDetection = 0;
bool waitingForServo = false;

// ==== FUNCTION PROTOTYPES ====
void initSystem();
bool isSensorBlocked(int pin);
void processSystem();

// ========================================================
// MAIN
// ========================================================
void setup() {
    initSystem();
}

void loop() {
    processSystem();
}

// ========================================================
// IMPLEMENTATION
// ========================================================

void initSystem() {
    Serial.begin(BAUD_RATE);
    pinMode(PIN_SENSOR_HEIGHT, INPUT);
    pinMode(PIN_SENSOR_START, INPUT);

    myServo.attach(PIN_SERVO);
    myServo.write(ANGLE_IDLE);

    Serial.println("--- SYSTEM READY (2 SENSORS MODE) ---");
    Serial.println("Waiting for product...");
}

// Hàm kiểm tra cảm biến (Logic: Giá trị < 500 là CÓ VẬT)
bool isSensorBlocked(int pin) {
    int val = analogRead(pin);
    return (val < THRESHOLD);
}

void processSystem() {
    unsigned long currentMillis = millis();

    // --- GIAI ĐOẠN 1: PHÁT HIỆN VẬT (Dùng cảm biến Start) ---
    // Chỉ kiểm tra khi hệ thống đang rảnh (không trong thời gian chờ servo)
    if (!waitingForServo) {
        if (isSensorBlocked(PIN_SENSOR_START)) {
            Serial.println(">> [1] Phat hien co vat di vao...");

            // Ngay khi phát hiện vật, kiểm tra ngay chiều cao
            // (Giả sử 2 cảm biến đặt thẳng hàng nhau theo phương thẳng đứng)
            delay(100); // Chờ 0.1s để vật đi vào ổn định hẳn dưới cảm biến

            if (isSensorBlocked(PIN_SENSOR_HEIGHT)) {
                Serial.println("   -> Phat hien: VAT CAO (Khong dat yeu cau) -> Se gat bo.");
                isTallObject = true;
            } else {
                Serial.println("   -> Phat hien: VAT THAP (Dat yeu cau) -> Cho qua.");
                isTallObject = false;
            }

            // Lưu thời gian bắt đầu và chuyển sang trạng thái chờ trôi
            timeDetection = currentMillis;
            waitingForServo = true;

            // Chờ cho vật đi qua hẳn cảm biến Start để tránh check lặp lại liên tục
            // (Đoạn này tạm dừng code 1 chút cho vật trôi qua khỏi mắt đọc)
            delay(500);
        }
    }

    // --- GIAI ĐOẠN 2: VẬN CHUYỂN VÀ XỬ LÝ SERVO ---
    if (waitingForServo) {
        // Tính thời gian vật trôi trên băng tải
        if (currentMillis - timeDetection >= TIME_TO_TRAVEL) {

            // Nếu là vật CAO -> Gạt
            if (isTallObject) {
                Serial.println(">> [ACTION] Servo KICH HOAT (Gat vat loi)");
                myServo.write(ANGLE_PUSH);
                delay(4000); // Thời gian gạt
                myServo.write(ANGLE_IDLE); // Thu về
            } else {
                Serial.println(">> [PASS] Vat thap -> Servo dung im.");
            }

            // Reset trạng thái, sẵn sàng đón vật mới
            waitingForServo = false;
            Serial.println(">> [DONE] Xong. Cho vat tiep theo.\n");
        }
    }
}