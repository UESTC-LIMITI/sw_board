/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-03-19 17:01:26
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-03-21 14:33:40
 * @FilePath: \MDK-ARM\tool\utils.h
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include "math.h"
#include "stdbool.h"
#include "main.h"

void truncate_int32  (int32_t* value, int32_t min, int32_t max);
void truncate_int16  (int16_t* value, int16_t min, int16_t max);
void truncate_int8   (int8_t* value, int8_t min, int8_t max);
void truncate_float  (float* value, float min, float max);
void truncate_uint32 (uint32_t* value, uint32_t max);
void truncate_uint16 (uint16_t* value, uint16_t max);
void truncate_uint8  (uint8_t* value, uint8_t max);
void angle_normalize (float* angle);
void angle_normalize_multiturn (float* angle, float round);

#define MEAN_FILTER_INT16_WINDOW_SIZE 100
#define MEAN_FILTER_INT32_WINDOW_SIZE 100
#define MEAN_FILTER_FLOAT_WINDOW_SIZE 100

typedef struct {
    int16_t window[MEAN_FILTER_INT16_WINDOW_SIZE];
    int32_t sum;
    int32_t index;
} mean_filter_int16_t;

typedef struct {
    int32_t window[MEAN_FILTER_INT32_WINDOW_SIZE];
    int64_t sum;
    int32_t index;
} mean_filter_int32_t;

typedef struct {
    float window[MEAN_FILTER_FLOAT_WINDOW_SIZE];
    float sum;
    int32_t index;
} mean_filter_float_t;

void mean_filter_int16_routine (int16_t now, mean_filter_int16_t* filter);
void mean_filter_int32_routine (int32_t now, mean_filter_int32_t* filter);
void mean_filter_float_routine (float_t now, mean_filter_float_t* filter);
float mean_filter_int16_get_value (mean_filter_int16_t* filter);
float mean_filter_int32_get_value (mean_filter_int32_t* filter);
float mean_filter_float_get_value (mean_filter_float_t* filter);
void delay_us_init (void);
void delay_us (uint32_t delay);
void delay_semius (uint32_t delay);
#endif
