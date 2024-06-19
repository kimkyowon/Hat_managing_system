#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include <stdbool.h>
#include <stdint.h>

// static bool lock = 0;
const static uint32_t chatterDelay = 50;

typedef struct __SW
{
    bool isActiveLow;
    bool interruptFlag;
    uint32_t pressedTimer;
    void (*OnPressedCbk)(struct __SW *);
    bool (*readPin)(void);
} SW_t;

void SW_init(SW_t *, bool, void (*)(struct __SW *), bool (*)(SW_t *));
void SW_msTask(SW_t *);
void SW_notifyInterrupt(SW_t *);

#endif
