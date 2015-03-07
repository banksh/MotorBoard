#include "timer.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0;

void TIM_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/* GPIOA Clocks enable */
RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
/* GPIOA Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_15;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
GPIO_Init(GPIOB, &GPIO_InitStructure);

GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_2);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_2);
}

void PWM_Config(void)
{
uint16_t TimerPeriod = (SystemCoreClock / 32000) -1;
uint16_t Pulselength = (uint16_t) (((uint32_t) 5*(TimerPeriod -1)) / 10); // gives 50% duty cycle

// Enable timer clock
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);

TIM_TimeBaseStructure.TIM_Prescaler = 0;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

TIM_OCInitStructure.TIM_Pulse = Pulselength;
TIM_OC1Init(TIM1, &TIM_OCInitStructure);

TIM_OCInitStructure.TIM_Pulse = Pulselength;
TIM_OC1Init(TIM17, &TIM_OCInitStructure);

TIM_Cmd(TIM1, ENABLE);
TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
