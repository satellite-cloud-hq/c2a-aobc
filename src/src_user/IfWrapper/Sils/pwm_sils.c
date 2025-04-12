#include "../pwm.h"

int OBC_C2A_PwmSetDuty(int port_id, const float duty);

void PWM_init()
{
  return;
}

void PWM_set_duty(PWM_CHANNEL pwm_channel, float duty)
{
  OBC_C2A_PwmSetDuty((int)pwm_channel, duty);
  return;
}
