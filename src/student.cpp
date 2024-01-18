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
    float motorVel = over.getMotorVel ();

    float e = over.getSlider(SliderEnum::prog1) * 1.0 / 1000;

    static float I = 0;

    static constexpr float Ki = 1;

    float dI = over.getTs() * Ki * e;

    I = I + dI;

    float u = I;

    float k = 0.45;
    float kp = 9.87;

    Serial.print(e);
    Serial.print(' ');
    Serial.println(w);
    
    over.setMotorU (u);
}