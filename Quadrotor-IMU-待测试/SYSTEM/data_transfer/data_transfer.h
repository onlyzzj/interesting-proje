#ifndef _DATA_TRANSFER_H
#define _DATA_TRANSFER_H
#include "stm32f4xx.h"



void Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z);
void Send_Senser2(s32 bar_alt,u16 csb_alt);
void Send_Status(float angle_rol,float angle_pit,float angle_yaw,s32 alt,u8 fly_model,u8 armed);


#endif
