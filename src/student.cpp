#include "student.h"

/**
 * @brief Инициализировать систему управления
 * @details Вызывется один раз перед вызовом
 * функции \p controllerTick
 */
void controllerInit (Overlord &over)
{
    over.setSlider (SliderEnum::prog1, -12000, 12000);
    over.setSlider (SliderEnum::prog2, -10000, 10000);
}

/**
 * @brief Выполнить одну итерацию системы управления
 * @details Вызывается раз в 5мс
 */
void controllerTick (Overlord &over)
{
    float setPoint = -over.getSetpoint ();
    float carX = -over.getCarX ();
    float carVel = -over.getCarVel ();
    float motorAngle = over.getMotorTheta ();
    float w = over.getMotorVel ();

    float w0 = over.getSlider(SliderEnum::prog1) * 1.0 / 1000;

    float Kp = 1;

    float e = w0 - w;

    float u = Kp * e;

    Serial.print(w0);
    Serial.print(' ');
    Serial.println(w);
    
    over.setMotorU (u);
}