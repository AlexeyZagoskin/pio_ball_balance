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

    float w0 = over.getSlider(SliderEnum::prog1) * 1.0 / 1000;

    float e = w0 - motorVel;

    float Tm = 6;
    float T1 = 35;
    float K = 0.68;


    static float I = 0;
    static constexpr float Ki = 7;
    static constexpr float Kp = 1;
    float Kk = T1 / (2 * K * Tm);


    float u = I + Kp * e * Kk;

    if (-10 < u && u < 10 || I * e < 0)
    {
        float dI = over.getTs() * Ki * e * Kk;
        I = I + dI;
    }

    u = constrain(u, -10, 10);
    



    Serial.print(w0);
    Serial.print(' ');
    Serial.println(motorVel);
    
    over.setMotorU (u);
}