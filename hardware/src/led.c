/**
 * @file    led.c
 * @brief   LED 驱动实现文件。
 */
#include "led.h"
#include "stdbool.h"

static bool inline is_valid_ledmark(uint8_t led_mark)
{
    return (led_mark & ~(LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN)) == 0;
}

void led_on(uint8_t led_mark)
{
    if (!is_valid_ledmark(led_mark))
    {
        return; // 无效的 LED 标记，直接返回
    }
    HAL_GPIO_WritePin(LED_GPIO_PORT, led_mark, GPIO_PIN_SET);
}
void led_off(uint8_t led_mark)
{
    if (!is_valid_ledmark(led_mark))
    {
        return; // 无效的 LED 标记，直接返回
    }
    HAL_GPIO_WritePin(LED_GPIO_PORT, led_mark, GPIO_PIN_RESET);
}