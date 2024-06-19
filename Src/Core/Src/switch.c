#include "switch.h"

const static uint32_t chatterDelay = 50;

static void SW_defaultPressedCbk(SW_t *instance){
    //Do not use
}

static bool SW_defaultReadPin(void){
    return 0;
    //Do not use
}


void SW_init(SW_t *instance, bool isActiveLow, void (*Cbk)(SW_t *), bool (*readPin)(void))
{
    if (!instance)
        return;

    instance->isActiveLow = isActiveLow;

    instance->interruptFlag = 0;
    instance->pressedTimer = 0;

    instance->OnPressedCbk = (Cbk) ? Cbk : SW_defaultPressedCbk;
    instance->readPin = (readPin) ? readPin : SW_defaultReadPin;
}

void SW_msTask(SW_t *instance)
{
    if (!instance)
        return;

    const bool PRESSED = !(instance->isActiveLow);

    if (instance->interruptFlag)
    {
        if (instance->readPin() == PRESSED) // Pressed : 1
        {
            if (instance->pressedTimer > chatterDelay)
            {
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

void SW_notifySwitchPressed(SW_t *instance)
{
    if (!instance)
        return;

    instance->interruptFlag = true;
}


