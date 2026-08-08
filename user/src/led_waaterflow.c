#include "led_waterflow.h"
#include "stdbool.h"

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

typedef struct
{
    uint16_t duration; // 持续时间，单位为ms
    uint32_t start_time;
    bool is_running;
} Timer;

static void timer_start(Timer *timer, float duration)
{
    timer->duration = duration;
    timer->start_time = HAL_GetTick();
    timer->is_running = true;
}
static void timer_stop(Timer *timer)
{
    timer->is_running = false;
}

static bool is_timer_expired(Timer *timer)
{
    if (!timer->is_running)
    {
        return false;
    }

    float elapsed_time = HAL_GetTick() - timer->start_time;
    if (elapsed_time >= timer->duration)
    {
        timer->start_time = HAL_GetTick(); // 重置计时器
        return true;
    }
    return false;
}

// 仅供参考,在学习了tim中断和freertos后,可以使用更优雅的方式实现led流水灯状态机
void LED_FSM(uint8_t signal)
{
    static LED_Blink_Mode current_mode_;
    static LED_Blink_Mode target_mode_;
    static Timer blink_timer_;
    static uint8_t led_mark = 0U;
    static bool is_entering_mode_ = true;

    if (signal >= LED_BLINK_MODE_COUNT)
    {
        return;
    }

    target_mode_ = (LED_Blink_Mode)signal;
    if (current_mode_ != target_mode_)
    {
        led_off(LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN);
        current_mode_ = target_mode_;
        is_entering_mode_ = true;
    }

    switch (current_mode_)
    {
    case IDLE:
        led_off(LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN);
        timer_stop(&blink_timer_);
        break;
    case SINGLE_BLINK:
        if (is_entering_mode_)
        {
            timer_start(&blink_timer_, 100.0f);
            is_entering_mode_ = false;
            led_mark = LED1_PIN;

            led_on(led_mark);
        }
        if (is_timer_expired(&blink_timer_))
        {
            led_off(led_mark);
            led_mark = (uint8_t)(led_mark << 1);
            if (led_mark > LED4_PIN)
            {
                led_mark = LED1_PIN;
            }
            led_on(led_mark);
        }
        break;
    case DOUBLE_BLINK:
        if (is_entering_mode_)
        {
            timer_start(&blink_timer_, 200.0f);
            is_entering_mode_ = false;
            led_mark = LED1_PIN | LED2_PIN;
            led_on(led_mark);
        }
        if (is_timer_expired(&blink_timer_))
        {
            led_off(led_mark);
            led_mark = (uint8_t)(led_mark << 2);
            if (led_mark > (LED4_PIN | LED3_PIN))
            {
                led_mark = LED1_PIN | LED2_PIN;
            }
            led_on(led_mark);
        }
        break;
    case ALL_BLINK:
        if (is_entering_mode_)
        {
            timer_start(&blink_timer_, 400.0f);
            is_entering_mode_ = false;
            led_mark = LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN;
            led_on(led_mark);
        }
        if (is_timer_expired(&blink_timer_))
        {
            led_toggle(led_mark);
        }
        break;
    case LED_BLINK_MODE_COUNT:
        break;
    default:
        break;
    }
}