/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-03-10 11:07:49
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-05-21 17:28:28
 * @FilePath: \MDK-ARM\ws2812\utils.c
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#include "utils.h"

void truncate_int32 (int32_t* value, int32_t min, int32_t max) {
    if (*value > max) {
        *value = max;
    } else if (*value < min) {
        *value = min;
    }
}

void truncate_int16 (int16_t* value, int16_t min, int16_t max) {
    if (*value > max) {
        *value = max;
    } else if (*value < min) {
        *value = min;
    }
}

void truncate_int8 (int8_t* value, int8_t min, int8_t max) {
    if (*value > max) {
        *value = max;
    } else if (*value < min) {
        *value = min;
    }
}

void truncate_float (float* value, float min, float max) {
    if (*value > max) {
        *value = max;
    } else if (*value < min) {
        *value = min;
    }
}

void truncate_uint32 (uint32_t* value, uint32_t max) {
    if (*value > max)
        *value = max;
}

void truncate_uint16 (uint16_t* value, uint16_t max) {
    if (*value > max)
        *value = max;
}

void truncate_uint8 (uint8_t* value, uint8_t max) {
    if (*value > max)
        *value = max;
}

void angle_normalize (float* angle) {
    while (*angle > 360.0f) {
        *angle -= 360.0f;
    } 
    while (*angle < 0.0f) {
        *angle += 360.0f;
    }
}

void angle_normalize_multiturn (float* angle, float round) {
    while (*angle > round) {
        *angle -= round;
    } 
    while (*angle < 0.0f) {
        *angle += round;
    }
}



void mean_filter_int16_routine (int16_t now, mean_filter_int16_t* filter) {
  filter->sum -= filter->window[filter->index];
  filter->window[(filter->index)++] = now;
	filter->sum += now;
  if (filter->index >= MEAN_FILTER_INT16_WINDOW_SIZE) {
    filter->index = 0;
  }
}

float mean_filter_int16_get_value (mean_filter_int16_t* filter) {
    return ((float)filter->sum) / MEAN_FILTER_INT16_WINDOW_SIZE;
}

void mean_filter_int32_routine (int32_t now, mean_filter_int32_t* filter) {
  filter->sum -= filter->window[filter->index];
  filter->window[(filter->index)++] = now;
	filter->sum += now;
  if (filter->index >= MEAN_FILTER_INT32_WINDOW_SIZE) {
    filter->index = 0;
  }
}

float mean_filter_int32_get_value (mean_filter_int32_t* filter) {
    return ((float)filter->sum) / MEAN_FILTER_INT32_WINDOW_SIZE;
}

void mean_filter_float_routine (float_t now, mean_filter_float_t* filter) {
  filter->sum -= filter->window[filter->index];
  filter->window[(filter->index)++] = now;
	filter->sum += now;
  if (filter->index >= MEAN_FILTER_FLOAT_WINDOW_SIZE) {
    filter->index = 0;
  }
}

float mean_filter_float_get_value (mean_filter_float_t* filter) {
    return filter->sum / MEAN_FILTER_FLOAT_WINDOW_SIZE;
}



__IO float delay_us_base;
__IO float delay_semius_base;

void delay_us_init (void) {
    __IO uint32_t first_ms, second_ms;
    __IO uint32_t counter = 0;
    __IO float coe = 1.0;

    first_ms = HAL_GetTick() + 1;
    second_ms = first_ms + 1;

    while(uwTick!=first_ms) ;

    while(uwTick!=second_ms) counter++;

    delay_us_base = ((float)counter) / 1000;

    first_ms = HAL_GetTick();
    delay_us(1000000) ;
    second_ms = HAL_GetTick();

    coe = ((float)1000) / (second_ms - first_ms);
    delay_us_base = coe*delay_us_base;
    delay_semius_base = delay_us_base / 2;
}

void delay_us (uint32_t delay) {
    __IO uint32_t delay_reg;
    __IO uint32_t us_num = (uint32_t)(delay * delay_us_base);

    while (us_num) us_num--;
}

void delay_semius (uint32_t delay) {
    __IO uint32_t delay_reg;
    __IO uint32_t us_num = (uint32_t)(delay * delay_semius_base);

    while (us_num) us_num--;
}

