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

    void led_water_flow(void);

#ifdef __cplusplus
}
#endif

#endif /* LED_WATERFLOW_H */