/*
 * drv_pulse.c
 *
 *  Created on: Oct 22, 2026
 *      Author: maith
 */

#include "drv_pulse.h"

static TIM_HandleTypeDef* l_tim;
static uint16_t clock = 0 ;
static int8_t channle_enable[10] = {0};
static volatile int16_t delta[10] = {0};
void drv_pulse_init(TIM_HandleTypeDef* tim_init, uint16_t clock_input)
{
	if ( tim_init != ((TIM_HandleTypeDef*) 0x00))
	{
		l_tim = tim_init;
		clock = clock_input;
	}
}

void drv_pulse_set_period(uint8_t TIM_Channel, uint16_t pulse)
{
    // 1. Kiểm tra tránh lỗi chia cho 0
    if (pulse == 0) return;

    // 2. Tính số tick đếm cho NỬA CHU KỲ (để đảo trạng thái Toggle)
    // Tần số Timer Clock = clock * 1000000 / (Prescaler + 1)
    // delta_t = (Timer Clock / pulse) / 2
    uint32_t tim_clock = (uint32_t)clock * 1000000;
    uint32_t delta_t = tim_clock / ((l_tim->Init.Prescaler + 1) * pulse * 2);

    // 3. Xử lý cho từng kênh TIM_CHANNEL
    switch (TIM_Channel)
    {
        case TIM_CHANNEL_1:
            delta[1] = delta_t;
            if (channle_enable[1] == 0)
            {
                channle_enable[1] = 1;
                // Nếu kênh chưa chạy, đặt mốc CCR ban đầu và kích hoạt ngắt OC
                uint32_t current_cnt = __HAL_TIM_GET_COUNTER(l_tim);
                __HAL_TIM_SET_COMPARE(l_tim, TIM_CHANNEL_1, current_cnt + delta_t);
                if (HAL_TIM_OC_Start_IT(l_tim, TIM_CHANNEL_1) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            break;

        case TIM_CHANNEL_2:
            delta[2] = delta_t;
            if (channle_enable[2] == 0)
            {
                channle_enable[2] = 1;
                uint32_t current_cnt = __HAL_TIM_GET_COUNTER(l_tim);
                __HAL_TIM_SET_COMPARE(l_tim, TIM_CHANNEL_2, current_cnt + delta_t);
                if (HAL_TIM_OC_Start_IT(l_tim, TIM_CHANNEL_2) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            break;

        case TIM_CHANNEL_3:
            delta[3] = delta_t;
            if (channle_enable[3] == 0)
            {
                channle_enable[3] = 1;
                uint32_t current_cnt = __HAL_TIM_GET_COUNTER(l_tim);
                __HAL_TIM_SET_COMPARE(l_tim, TIM_CHANNEL_3, current_cnt + delta_t);
                if (HAL_TIM_OC_Start_IT(l_tim, TIM_CHANNEL_3) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            break;

        case TIM_CHANNEL_4:
            delta[4] = delta_t;
            if (channle_enable[4] == 0)
            {
                channle_enable[4] = 1;
                uint32_t current_cnt = __HAL_TIM_GET_COUNTER(l_tim);
                __HAL_TIM_SET_COMPARE(l_tim, TIM_CHANNEL_4, current_cnt + delta_t);
                if (HAL_TIM_OC_Start_IT(l_tim, TIM_CHANNEL_4) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            break;

        default:
            break;
    }
}
void drv_pulse_deinit()
{
	l_tim = (TIM_HandleTypeDef*) 0x00;
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != l_tim->Instance) return;

    uint32_t channel;
    uint8_t ch_idx;

    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_1:
            channel = TIM_CHANNEL_1;
            ch_idx = 1;
            break;

        case HAL_TIM_ACTIVE_CHANNEL_2:
            channel = TIM_CHANNEL_2;
            ch_idx = 2;
            break;

        case HAL_TIM_ACTIVE_CHANNEL_3:
            channel = TIM_CHANNEL_3;
            ch_idx = 3;
            break;

        case HAL_TIM_ACTIVE_CHANNEL_4:
            channel = TIM_CHANNEL_4;
            ch_idx = 4;
            break;

        default:
            return; // Nếu là kênh khác (ví dụ kịch bản ngắt phụ) thì thoát ngay
    }

    // Đọc và cập nhật CCR[cite: 1]
    uint32_t current_ccr = HAL_TIM_ReadCapturedValue(htim, channel);
    __HAL_TIM_SET_COMPARE(htim, channel, current_ccr + delta[ch_idx]);
}
