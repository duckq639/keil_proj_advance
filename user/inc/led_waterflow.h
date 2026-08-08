#ifndef LED_WATERFLOW_H
#define LED_WATERFLOW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "led.h"

    typedef struct
    {

        uint8_t on_led_mark;
        uint32_t duration;
        float on_duty;
    } LED_Blink;

    typedef enum {
        IDLE = 0,
        SINGLE_BLINK,
        DOUBLE_BLINK,
        ALL_BLINK,
        LED_BLINK_MODE_COUNT,
    } LED_Blink_Mode;

    void LED_FSM(uint8_t signal);

#ifdef __cplusplus
}
#endif

#endif /* LED_WATERFLOW_H */