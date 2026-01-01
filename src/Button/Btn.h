//
// Created by ngoc1 on 1/1/2026.
//

#ifndef FSZ_ARDUINOUNOR3_BTN_H
#define FSZ_ARDUINOUNOR3_BTN_H
#include <Arduino.h>

namespace Button {
    enum BtnType {
        TURN_OFF = 0,
        TURN_ON = 1,
    };
    class Btn {
        int pin = 0;
        int lastState = HIGH;
        int currentState = HIGH;
        BtnType type = TURN_OFF;
    public:
        Btn(int pin, BtnType type);

        // Getter
        int getPin() const;
        BtnType getType() const;
        int getLastState() const;
        int getCurrentState() const;

        // Setter
        void setPin(int newPin);
        void setType(BtnType newType);
        void setLastState(int newLastState);
        void setCurrentState(int newCurrentState);
    };
}


#endif //FSZ_ARDUINOUNOR3_BTN_H