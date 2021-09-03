#include "delay.h"
#include "pwm_out.h"

int main(void)
{
	PWM_Out_Init();
	MOTOR_Stop();
}
