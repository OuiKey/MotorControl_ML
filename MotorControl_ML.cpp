#include <Arduino.h>
#include <inttypes.h>
#include "MotorControl_ML.h"

MotorControl Motors;


void MotorControl::SerialPlotterLoop(void *parameter)
{
    MotorControl *motors = static_cast<MotorControl *>(parameter);

    for (;;)
    {
        Serial.printf(">FinLeft:%d\n", motors->FinLeft);
        Serial.printf(">RinLeft:%d\n", motors->RinLeft);
        Serial.printf(">FinRight:%d\n", motors->FinRight);
        Serial.printf(">RinRight:%d\n", motors->RinRight);
        delay(10);
    }
}
void MotorControl::init(uint8_t FinLeftPIN, uint8_t RinLeftPIN, uint8_t FinRightPIN, uint8_t RinRightPIN)
{

    
    MOTORS_PIN[FL] = FinLeftPIN;
    MOTORS_PIN[RL] = RinLeftPIN;
    MOTORS_PIN[FR] = FinRightPIN;
    MOTORS_PIN[RR] = RinRightPIN;
    
    Motors.setSpeed(0, 0);

    xTaskCreatePinnedToCore(SerialPlotterLoop, "SerialPlotterLoop", 4096, this, 1, &SerialPlotter, 0);

}

void MotorControl::setMotorPWM(uint8_t rightMotor, uint8_t leftMotor, bool RMDir, bool LMDir)
{   
    rightMotor = (rightMotor < 75) && rightMotor ? 75 : rightMotor;
    leftMotor = (leftMotor < 75) && leftMotor ? 75 : leftMotor;

    if (RMDir)
    {
        analogWrite(MOTORS_PIN[FR], rightMotor);
        FinRight = rightMotor;
        analogWrite(MOTORS_PIN[RR], 0);
        RinRight = 0;
    }
    else if (rightMotor == 0)
    {
        analogWrite(MOTORS_PIN[FR], 255);
        FinRight = 255;
        analogWrite(MOTORS_PIN[RR], 255);
        RinRight = 255;
    }
    else
    {
        analogWrite(MOTORS_PIN[FR], 0);
        FinRight = 0;
        analogWrite(MOTORS_PIN[RR], rightMotor);
        RinRight = rightMotor;
    }

    if (LMDir)
    {
        analogWrite(MOTORS_PIN[FL], leftMotor);
        FinLeft = leftMotor;
        analogWrite(MOTORS_PIN[RL], 0);
        RinLeft = 0;
    }
    else if (leftMotor == 0)
    {
        analogWrite(MOTORS_PIN[FL], 255);
        FinLeft = 255;
        analogWrite(MOTORS_PIN[RL], 255);
        RinLeft = 255;
    }
    else
    {
        analogWrite(MOTORS_PIN[FL], 0);
        FinLeft = 0;
        analogWrite(MOTORS_PIN[RL], leftMotor);
        RinLeft = leftMotor;
    }
}

void MotorControl::setSpeed(int16_t rightMotor, int16_t leftMotor)
{
    bool RMDir = rightMotor > 0;
    bool LMDir = leftMotor > 0;

    static bool RMStop = 0;
    static bool LMStop = 0;

    bool RMStart = rightMotor < 75 && rightMotor != 0 && RMStop;
    bool LMStart = leftMotor < 75 && leftMotor != 0 && LMStop;

    if (RMStart || LMStart)
    {
        setMotorPWM(RMStart * 255, LMStart * 255, RMDir, LMDir);
        delay(40);
    }

    setMotorPWM(abs(rightMotor), abs(leftMotor), RMDir, LMDir);

    RMStop = rightMotor == 0 ? 1 : 0;
    LMStop = leftMotor == 0 ? 1 : 0;
}
