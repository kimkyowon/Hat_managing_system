#include "switch.h"

void SW_init(SW_t *instance, void (*Cbk)(SW_t *), bool (*readPin)(SW_t*))
{
    if (!instance)
        return;

    instance->interruptFlag = 0;
    instance->pressedTimer = 0;

    if (Cbk)
        instance->OnPressedCbk = Cbk;
    else
        instance->OnPressedCbk = SW_defaultPressedCbk;

    if (readPin)
        instance->OnPressedCbk = Cbk;
    else
        instance->OnPressedCbk = SW_defaultReadPin;
}

void SW_msTask(SW_t *instance)
{
    if (!instance)
        return;

    if (instance->interruptFlag)
    {
        if (instance->readPin() == 1) // Pressed : 1
        {
            if(instance->pressedTimer > chatterDelay){
                instance->pressedTimer = 0;
                instance->interruptFlag = false;
                instance->OnPressedCbk(instance);
                return;
            }
            instance->pressedTimer++;
        }
        else
        {
            instance->pressedTimer = 0;
            instance->interruptFlag = false;
        }
    }
    else
    {
        instance->pressedTimer = 0;
    }
}

void SW_notifyInterrupt(SW_t *instance)
{
    if (!instance)
        return;

    instance->interruptFlag = true;
}

static void SW_defaultPressedCbk(SW_t *instance){
    //Do not use
}

static bool SW_defaultReadPin(void){
    return 0;
    //Do not use
}
