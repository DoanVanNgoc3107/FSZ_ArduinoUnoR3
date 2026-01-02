//
// Created by ngoc1 on 1/1/2026.
//

#include "Btn.h"

namespace Button {
    /**
     * Constructor
     * @param pin Chân nút bấm
     * @param type Loại nút bấm
     */
    Btn::Btn(int pin, BtnType type) : pin(pin), type(type) {
        pinMode(pin, INPUT_PULLUP);
    }

    /**
     * Lấy chân nút bấm
     * @return Chân nút bấm
     */
    int Btn::getPin()  {
        return pin;
    }

    /**
     * Lấy loại nút bấm
     * @return Loại nút bấm
     */
    BtnType Btn::getType()  {
        return type;
    }

    /**
     * Lấy trạng thái lần trước của nút bấm
     * @return Trạng thái lần trước của nút bấm
     */
    int Btn::getLastState()  {
        return lastState;
    }

    /**
     * Lấy trạng thái hiện tại của nút bấm
     * @return Trạng thái hiện tại của nút bấm
     */
    int Btn::getCurrentState()  {
        return currentState;
    }

    /**
     * Đặt chân nút bấm mới
     * @param newPin Chân nút bấm mới
     */
    void Btn::setPin(int  newPin) {
        pin = newPin;
        pinMode(pin, INPUT_PULLUP);
    }

    /**
     * Đặt loại nút bấm mới
     * @param newType Loại nút bấm mới
     */
    void Btn::setType(BtnType  newType) {
        type = newType;
    }

    /**
     * Đặt trạng thái lần trước của nút bấm mới
     * @param newLastState  Trạng thái lần trước của nút bấm mới
     */
    void Btn::setLastState(int  newLastState) {
        lastState = newLastState;
    }

    /**
     * Đặt trạng thái hiện tại của nút bấm mới
     * @param newCurrentState Trạng thái hiện tại của nút bấm mới
     */
    void Btn::setCurrentState(int  newCurrentState) {
        currentState = newCurrentState;
    }
}
