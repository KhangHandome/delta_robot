#include "Hybrid_Servo.h"
#include "hal_layer.h"
#include <unistd.h> // for usleep

HybridServo    myHybridServo[MAX_SERVO_INSTANCE];
static uint8_t indexOfServo = 0 ; 
// User this to get instance of the step motor 
static uint8_t HybridServo_GetInstanceID(HybridServo *servo);
uint8_t HybridServo_GetInstanceID(HybridServo *servo)
{
    uint8_t retVal = 0xff ; 
    uint8_t index  = 0 ; 
    for ( index = 0 ; index < indexOfServo ; index ++ )
    {
        if ( servo->index == myHybridServo[index].index)
        {
            retVal = index;
            index = 0xff;
        }
    }
    return retVal; 
}
void HybridServo_Init(HybridServo* servo) 
{
    // Setup the pin for step motor 
    myHybridServo[indexOfServo].index      = servo->index ; 
    myHybridServo[indexOfServo].step_pin   = servo->step_pin ; 
    myHybridServo[indexOfServo].dir_pin    = servo->dir_pin ; 
    myHybridServo[indexOfServo].speed      = servo->speed ; 
    myHybridServo[indexOfServo].direction  = servo->direction ;
    myHybridServo[indexOfServo].servo_state = SERVO_STATE_UNINITIALIZED ;
    // Init pin port 
    HAL_SetPinOutput(myHybridServo[indexOfServo].step_pin);
    HAL_SetPinOutput(myHybridServo[indexOfServo].dir_pin);
    // Up to the next setup 
    indexOfServo += 1 ; 
}

void HybridServo_SetUp(HybridServo* servo) 
{
    
    uint8_t instance = 0 ; 
    // Get the instance of my servo 
    instance = HybridServo_GetInstanceID(servo);
    if(instance != 0xff)
    {
        myHybridServo[instance].servo_state = SERVO_STATE_CONFIGURING ;
        // Set hướng quay
        myHybridServo[instance].speed       = servo->speed ; 
        myHybridServo[instance].direction   = servo->direction ; 
        myHybridServo[instance].servo_state = SERVO_STATE_READY ;
    }
}
void HybridServo_Running(void)
{
    uint8_t counter = 0 ;
    // Cấu hình PWM to setup the speed 
    for (counter = 0; counter < indexOfServo; counter++)
    {
        switch (myHybridServo[counter].servo_state)
        {
            case SERVO_STATE_CONFIGURING:
                myHybridServo[counter].servo_state = SERVO_STATE_READY;
                /* code */
                break;
            case SERVO_STATE_READY:
                myHybridServo[counter].servo_state = SERVO_STATE_ACTIVE;
                HAL_SetPWM(myHybridServo[counter].step_pin, 0.0f);
                if(myHybridServo[counter].direction == Clockwise )
                {
                    HAL_WritePin(myHybridServo[counter].dir_pin, 0);
                }
                else
                {
                    HAL_WritePin(myHybridServo[counter].dir_pin, 1);
                }
                break;
            case SERVO_STATE_ACTIVE:
                // The servo is running 
                break;
            default:
                break;
        }
    }
}
void HybridServo_Stop(HybridServo* servo) 
{
    uint8_t instance = HybridServo_GetInstanceID(servo);

    if(instance != 0xff)
    {
        HAL_SetPWM(myHybridServo[instance].step_pin, 0.0f);
        HAL_WritePin(myHybridServo[instance].dir_pin, 0);
        myHybridServo[instance].servo_state = SERVO_STATE_STOP;
    }
}
