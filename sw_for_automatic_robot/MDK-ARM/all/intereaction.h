/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:53:58
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-11 11:00:32
 * @FilePath: \MDK-ARM\Intereaction\intereaction.h
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#ifndef __INTEREACTION_H__ 
#define __INTEREACTION_H__

#include "fdcan.h"
#include "fdcan_bsp.h"
#include "main.h"
#include "stdbool.h"
#include "tim.h"
#include "utils.h"
#include "string.h"

#define COMMUNICATION_TEST 0x00
#define START 0x01
#define STOP 0x02
#define GO_TO_POINT_1 0x03
#define GO_TO_POINT_2 0x04
#define SELF_CHECK 0x05
#define IN_BLUE_AREA 0x06
#define IN_RED_AREA 0x07

typedef struct {
	bool sw1;  //发送一次性状态
	bool sw2;  //设置第一次看球点，打开为2号点，关闭为1号点
	bool sw3;  //请求自检
	bool sw4;
	bool in_red;
	bool in_blue;
	bool stop;  //按下停止，抬起启动
	bool start;
} switches_t;

typedef struct {
	bool chassis_config_ack;
} acknowledge_t;

void intereaction_scan_sw(void);
void intereaction_send_can_message(uint8_t index);
void intereaction_single_send (void);
void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata);
extern switches_t switches;
extern uint32_t stop_count;
extern uint32_t start_count;
extern acknowledge_t ack;

#endif
