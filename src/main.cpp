#include <Arduino.h>
#include <Servo.h>

// ==== CẤU HÌNH CHÂN (PINS) ====
constexpr int PIN_SERVO = 9;
constexpr int PIN_SENSOR_HEIGHT = A0; // Cảm biến đo chiều cao (Đặt trên cao)
constexpr int PIN_SENSOR_START = A1; // Cảm biến phát hiện vật (Đặt thấp/Bắt đầu)
constexpr int BUTTON_START = 5;

// ==== CẤU HÌNH THÔNG SỐ ====
constexpr int BAUD_RATE = 9600;

// Ngưỡng cảm biến hồng ngoại (Vật cản -> Giá trị thấp)
// Bạn cần chỉnh biến trở trên cảm biến sao cho:
// - Không vật: ~900-1000
// - Có vật: < 100
constexpr int THRESHOLD = 500;

// Góc Servo
constexpr int ANGLE_PUSH = 65; // Góc gạt
constexpr int ANGLE_IDLE = 0; // Góc chờ

// Thời gian vật trôi trên băng tải từ cảm biến Start đến vị trí Servo (ms)
const unsigned long TIME_TO_TRAVEL = 0; // 2000ms = 2 giây (Ví dụ)

Servo myServo; // Khởi tạo đối tượng Servo

// Trạng thái hệ thống
bool isTurnOn = false;
bool isTurnOff = false;
bool objectDetected = false; // Biến này sử dụng để phát hiện vật thể
bool isTallObject = false; // Biến này sử dụng để kiểm tra xem vật có đạt yêu cầu về chiều cao hay không?
unsigned long timeDetection = 0; // Biến này sử dụng để lưu thời gian phát hiện vật
bool waitingForServo = false; // Biến này sử dụng để chờ thời gian trôi đến khi kích hoạt servo
bool btnLastState = HIGH; // Luu trang thai truoc cua nut bam

// ==== FUNCTION PROTOTYPES ====
void initSystem();

bool isSensorBlocked(int pin);

void processSystem();

void setup() {
    initSystem();
}

void loop() {
    int btnCurrentState = digitalRead(BUTTON_START);
    if (btnCurrentState != btnLastState) {
        delay(50); // Debounce
        btnCurrentState = digitalRead(BUTTON_START);
        if (btnCurrentState != btnLastState) {
            btnLastState = btnCurrentState;
            if (btnCurrentState == LOW) {
                isTurnOn = !isTurnOn;
            }
        }
    }
    if (isTurnOn) {
        processSystem();
    } else {
        Serial.println("--- SYSTEM OFF ---");
        delay(1000); // Giảm tần số in khi tắt hệ thống
    }
}

void initSystem() {
    Serial.begin(BAUD_RATE);
    pinMode(PIN_SENSOR_HEIGHT, INPUT);
    pinMode(PIN_SENSOR_START, INPUT);

    pinMode(BUTTON_START, INPUT_PULLUP);

    myServo.attach(PIN_SERVO);
    myServo.write(ANGLE_IDLE);

    Serial.println("--- SYSTEM READY (2 SENSORS MODE) ---");
    Serial.println("Waiting for product...");
}

bool isSensorBlocked(const int pin) {
    const int val = analogRead(pin);
    return (val < THRESHOLD);
}

void processSystem() {
    const unsigned long currentMillis = millis();

    if (!waitingForServo) {
        if (isSensorBlocked(PIN_SENSOR_START)) {
            Serial.println("[DETECTED] Product detected!");

            // Ngay khi phát hiện vật, kiểm tra ngay chiều cao
            delay(100); // Chờ 0.1s để vật đi vào ổn định hẳn dưới cảm biến

            if (isSensorBlocked(PIN_SENSOR_HEIGHT)) {
                Serial.println("[ITEMS] :  GOOD!\n");
                isTallObject = true;
            } else {
                Serial.println("[ITEMS] :  BAD!\n");
                isTallObject = false;
            }

            // Lưu thời gian bắt đầu và chuyển sang trạng thái chờ trôi
            timeDetection = currentMillis;
            waitingForServo = true;

            // Chờ cho vật đi qua hẳn cảm biến Start để tránh check lặp lại liên tục
            // (Đoạn này tạm dừng code 1 chút cho vật trôi qua khỏi mắt đọc)
            delay(1000);
        }
    }

    // --- GIAI ĐOẠN 2: VẬN CHUYỂN VÀ XỬ LÝ SERVO ---
    if (waitingForServo) {
        // Tính thời gian vật trôi trên băng tải
        if (currentMillis - timeDetection >= TIME_TO_TRAVEL) {
            // Nếu là vật CAO -> Gạt
            if (isTallObject) {
                Serial.println("[ACTION] - ");
                myServo.write(ANGLE_PUSH);
                delay(200); // Thời gian gạt
                myServo.write(ANGLE_IDLE); // Thu về
            } else {
                Serial.println("[PASS]");
            }

            // Reset trạng thái, sẵn sàng đón vật mới
            waitingForServo = false;
            Serial.println(">> [DONE]");
        }
    }
}
