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

float step(uint32_t time, uint32_t period, float min_out, float max_out)
{
    if(time/period % 2)
    {
        return min_out;
    }
    return max_out;

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

    // static constexpr float Ki = 4, Kp = 1;
    // static float Ts = 0.6, I = 0;
    // float Umax = 12;

    // // float e = w0 - w;
    // // float eKp = (w0 - w) * Kp;
    // float u = ((w0 - w) * Kp) + I;
    // float eKi = ((w0 - w) * Kp) * Ki;
    
    // uint32_t time = millis();  

    // if(Umax == constrain(u, -12, 12) || I * eKi < 0)
    // {
    //     float dI = eKi * Ts;
    //     I = I + dI;

    // }

    uint32_t time = millis();

    float u = step(time, 2000, 0, 10); // 0 если время не пришло, 10 если время пришло

    over.setMotorU (u);

    Serial.print(time);
    Serial.print(" ");
    Serial.print(u);
    Serial.print(" ");
    Serial.println(w);
}
