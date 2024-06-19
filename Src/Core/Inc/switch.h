#ifndef INC_SWITCH_H_
#define INC_SWITCH_H_

#include <stdbool.h>
#include <stdint.h>

// static bool lock = 0;

typedef struct __SW
{
    bool isActiveLow;

    bool interruptFlag;
    uint32_t pressedTimer;

    void (*OnPressedCbk)(struct __SW *);
    bool (*readPin)(void);
} SW_t;

void SW_init(SW_t *, bool, void (*)(struct __SW *), bool (*)(void));
void SW_msTask(SW_t *);
void SW_notifySwitchPressed(SW_t *);

#endif
