//
// Created by ngoc1 on 1/1/2026.
//

#include "Btn.h"
namespace Button {
    Btn::Btn(int const pin, BtnType const type) : pin(pin), type(type) {
        pinMode(pin, INPUT_PULLUP);
    }

    // Getter
    int Btn::getPin() const {
        return pin;
    }

    BtnType Btn::getType() const {
        return type;
    }

    int Btn::getLastState() const {
        return lastState;
    }

    int Btn::getCurrentState() const {
        return currentState;
    }

    // Setter
    void Btn::setPin(int const newPin) {
        pin = newPin;
        pinMode(pin, INPUT_PULLUP);
    }

    void Btn::setType(BtnType const newType) {
        type = newType;
    }

    void Btn::setLastState(int const newLastState) {
        lastState = newLastState;
    }

    void Btn::setCurrentState(int const newCurrentState) {
        currentState = newCurrentState;
    }
}
