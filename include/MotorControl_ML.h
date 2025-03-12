#ifndef MotorControl_ML_H
#define MotorControl_ML_H

#include <Arduino.h>
#include <inttypes.h>

/*///////////////////////////////////////////////


            MotorControl_ML

@author Mathys Lodé

*////////////////////////////////////////////////

const uint8_t RR = 0;
const uint8_t FR = 1;
const uint8_t RL = 2;
const uint8_t FL = 3;

class MotorControl
{
public:

    uint8_t MOTORS_PIN[4];

    int16_t FinRight = 0;
    int16_t RinRight = 0;
    int16_t FinLeft = 0;
    int16_t RinLeft = 0;

    TaskHandle_t SerialPlotter;

    static void SerialPlotterLoop(void *parameter);

    void init(uint8_t FinRightPIN, uint8_t RinRightPIN, uint8_t FinLeftPIN, uint8_t RinLeftPIN);

    void setMotorPWM(uint8_t rightMotor, uint8_t leftMotor, bool RMDir, bool LMDir);

    void setSpeed(int16_t rightMotor, int16_t leftMotor);

protected:
};

extern MotorControl Motors;


#endif