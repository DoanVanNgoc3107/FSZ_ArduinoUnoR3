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
 *  VERSION : 4.1.27
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


// ==== INCLUDES ====
#include <Arduino.h>
#include <Servo.h>

// ==== DEFINES & CONSTANTS ====
const int SERVO_PIN = 9; // Chân PWM cho Servo
const int SENSOR_PIN = A0; // Chân Analog cho cảm biến quang
const int BAUD_RATE = 9600;

// --- CẤU HÌNH HỆ THỐNG (CẦN CALIBRATE THỰC TẾ) ---
// Ngưỡng phân biệt Sáng/Tối.
// Cần test: Mở Serial Monitor, xem giá trị khi có vật và không vật để đặt số này.
// Ví dụ: Không vật = 800, Có vật = 200 -> Chọn 500.
const int THRESHOLD_ON = 500;

const int ANGLE_PUSH = 70; // Góc gạt vật ra
const int ANGLE_IDLE = 0; // Góc chờ

// Thời gian (ms) vật di chuyển từ cảm biến đến tay gạt Servo
// Tùy tốc độ băng tải mà chỉnh số này (Ví dụ: 3000ms = 3 giây)
const unsigned long TIME_TO_SERVO = 100;

Servo myServo; // Khởi tạo đối tượng servo

// Biến quản lý trạng thái thời gian (State Machine)
unsigned long detectionStartTime = 0;
bool isProcessing = false; // Trạng thái: True = Đang theo dõi vật, False = Rảnh

// ==== FUNCTION PROTOTYPES ====
void initSystem();
int readSensorAverage(int pin);
bool isObjectDetected(int sensorValue);
void processConveyorSystem(int sensorValue);

// ========================================================
// MAIN SETUP & LOOP
// ========================================================

void setup()
{
    initSystem();
}

void loop()
{
    // 1. Đọc giá trị cảm biến (Đã lọc trung bình)
    int currentVal = readSensorAverage(SENSOR_PIN);

    // 2. Debug giá trị lên màn hình để canh chỉnh (Bỏ comment khi nạp code thật)
    Serial.print("Analog: "); Serial.println(currentVal);

    // 3. Chạy logic hệ thống
    processConveyorSystem(currentVal);
}

// ========================================================
// IMPLEMENTATION
// ========================================================

void initSystem()
{
    Serial.begin(BAUD_RATE);
    pinMode(SENSOR_PIN, INPUT);
    myServo.attach(SERVO_PIN);
    myServo.write(ANGLE_IDLE); // Về vị trí chờ ban đầu
    Serial.println("--- SYSTEM READY ---");
    Serial.println("Waiting for object...");
}

/**
 * Đọc giá trị Analog trung bình cộng để chống nhiễu
 * @param pin Chân Analog cần đọc
 * @return Giá trị trung bình (0 - 1023)
 */
int readSensorAverage(int pin)
{
    long sum = 0;
    const int SAMPLES = 10;

    for (int i = 0; i < SAMPLES; i++)
    {
        sum += analogRead(pin);
        delay(2); // Delay cực nhỏ để ổn định dòng điện giữa các lần đọc
    }

    return static_cast<int>(sum / SAMPLES); // ép kiểu sang int
}

/**
 * Kiểm tra xem có vật che cảm biến hay không
 * Logic: Quang trở bị che -> Tối -> Giá trị Analog GIẢM (Hoặc Tăng tùy mạch)
 * @param sensorValue Giá trị đọc được
 * @return true nếu phát hiện vật
 */
bool isObjectDetected(int sensorValue)
{
    // Giả sử mạch phân áp: Che sáng -> Giá trị nhỏ đi
    if (sensorValue < THRESHOLD_ON)
    {
        return true;
    }
    return false;
}

/**
 * Hàm xử lý logic chính (Core Logic)
 * Sử dụng millis() để không chặn luồng (Non-blocking)
 */
void processConveyorSystem(int sensorValue)
{
    unsigned long currentMillis = millis();

    // Part 1: Xử lý khi phát hiện vật
    if (!isProcessing && isObjectDetected(sensorValue))
    {
        Serial.println(">> [DETECTED] Phat hien vat! Bat dau dem gio...");

        detectionStartTime = currentMillis; // Lưu mốc thời gian
        isProcessing = true; // Khóa hệ thống vào trạng thái xử lý
    }

    // --- GIAI ĐOẠN 2: CHỜ VẬT TRÔI ĐẾN SERVO ---
    if (isProcessing)
    {
        // Tính thời gian đã trôi qua
        // if (currentMillis - detectionStartTime >= TIME_TO_SERVO)
        // {
            Serial.println(">> [ACTION] Vat da den vi tri GAT -> Kich hoat Servo");

            // Thực hiện gạt (Đoạn này dùng delay được vì hành động diễn ra nhanh)
            myServo.write(ANGLE_PUSH);
            delay(5000); // Chờ servo quay tới nơi

            myServo.write(ANGLE_IDLE);
            delay(500); // Chờ servo thu về

            // Reset trạng thái để đón vật tiếp theo
            isProcessing = false;
            Serial.println(">> [DONE] Hoan thanh. Cho vat tiep theo.\n");
        // }
    }
}
