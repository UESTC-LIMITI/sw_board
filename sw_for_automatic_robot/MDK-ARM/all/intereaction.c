/*
 * @Author: xiayuan 1137542776@qq.com
 * @Date: 2024-06-11 08:54:07
 * @LastEditors: xiayuan 1137542776@qq.com
 * @LastEditTime: 2024-06-11 10:54:35
 * @FilePath: \MDK-ARM\Intereaction\intereaction.c
 * @Description: 
 * 
 * Copyright (c) 2024 by UESTC_LIMITI, All Rights Reserved. 
 */
#include "intereaction.h"

switches_t switches = {
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	false,
	};
uint32_t stop_count = 0;
uint32_t start_count = 0;
acknowledge_t ack = {false};


void intereaction_scan_sw(void) {
	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == GPIO_PIN_SET) {
		switches.sw1 = true;
	} else {
		switches.sw1 = false;
	}

	if (HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == GPIO_PIN_SET) {
		switches.sw2 = true;
	} else {
		switches.sw2 = false;
	}

	if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_SET) {
		switches.sw3 = true;
	} else {
		switches.sw3 = false;
	}

	if (HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin) == GPIO_PIN_SET) {
		switches.sw4 = true;
	} else {
		switches.sw4 = false;
	}

	if (HAL_GPIO_ReadPin(BLUE_AREA_SW_GPIO_Port, BLUE_AREA_SW_Pin) == GPIO_PIN_SET) {
		switches.in_blue = true;
		switches.in_red = false;
	} else if (HAL_GPIO_ReadPin(RED_AREA_SW_GPIO_Port, RED_AREA_SW_Pin) == GPIO_PIN_SET) {
		switches.in_red = true;
		switches.in_blue = false;
	} else {
		switches.in_red = false;
		switches.in_blue = false;		
	}
	
	//tim2 -> stop 
	//tim3 -> start
	if (stop_count >= 50) {
		switches.stop = true;
		switches.start = false;
		// HAL_TIM_Base_Stop_IT(&htim2);
		// stop_count = 0;
	}
	if (start_count >= 50) {
		switches.stop = false;
		switches.start = true;
		// HAL_TIM_Base_Stop_IT(&htim3);
		// start_count = 0;
	}
}

void intereaction_send_can_message(uint8_t index) {
	uint32_t stdid = 0;
	switch (index)
	{
	case 0:
		stdid = COMMUNICATION_TEST;
		break;
	
	case 1:
    intereaction_single_send();
    return;
    break;
	
	case 2:
		stdid = STOP;
		break;
		
	case 3:
		stdid = SELF_CHECK;
		break;
		
	default:
		return;
		break;
	}

	FDCAN_SendData (&hfdcan1, NULL, stdid, 0);
}

uint8_t buffer[2];
void intereaction_single_send (void) {
  memset(buffer, 0, sizeof(buffer));
	if (switches.in_blue) {
		buffer[0] = 0x01;
	} else if (switches.in_red) {
		buffer[0] = 0x02;
	} else {
    buffer[0] = 0x00;
  }
//  delay_us(1);
	if (switches.sw2) {
		buffer[1] = 0x02;
	} else {
		buffer[1] = 0x01;
	}
  FDCAN_SendData (&hfdcan1, buffer, START, 2);
//  delay_us(1);
}

void intereacion_can_decode (uint32_t stdid, uint8_t *Rxdata) {
	if (stdid == 0x02f) {
		ack.chassis_config_ack = true;
	}
}
