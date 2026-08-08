#include "led_waterflow.h"


// 限幅
static inline float clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

#define SIZEOF_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0])) // 求数组元素个数

static void led_blink(LED_Blink *blink)
{
    clamp(blink->on_duty, 0.0f, 1.0f);

    uint32_t on_time = blink->duration * blink->on_duty;
    uint32_t off_time = blink->duration - on_time;

    HAL_GPIO_WritePin(GPIOB, blink->on_led_mark, GPIO_PIN_SET);
    HAL_Delay(on_time);
    HAL_GPIO_WritePin(GPIOB, blink->on_led_mark, GPIO_PIN_RESET);
    HAL_Delay(off_time);
}

void led_water_flow(void)
{
    LED_Blink blink_sequence[] = {
        {LED1_PIN, 300, 0.5f},
        {LED2_PIN, 300, 0.5f},
        {LED3_PIN, 300, 0.5f},
        {LED4_PIN, 300, 0.5f},
    };

    for (size_t i = 0; i < SIZEOF_ARRAY(blink_sequence); i++)
    {
        led_blink(&blink_sequence[i]);
    }
}