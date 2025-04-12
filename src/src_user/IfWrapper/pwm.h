#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void PWM_init();

typedef enum
{
  PWM_CHANNEL_MTQ_PWM_X = 0,
  PWM_CHANNEL_MTQ_PWM_Y,
  PWM_CHANNEL_MTQ_PWM_Z,
  PWM_CHANNEL_MAX
} PWM_CHANNEL;

/**
 * @fn    PWM_set_duty
 * @param pwm_channel: PWM_CHANNELに準拠
 * @param duty:        [-100.0, 100.0] の範囲におけるPWM duty比 [%]
*/
void PWM_set_duty(PWM_CHANNEL pwm_channel, float duty);

#endif
