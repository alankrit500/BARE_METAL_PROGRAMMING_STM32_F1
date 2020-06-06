#include "stm32f10x.h"                  // Device header
#include<stdio.h>
#include<stdlib.h>

// TIM_CHANNEL_PIN : A2

int main()
{
	RCC->APB1ENR |=(1<<0);                // TIM2_CLOCK ENABLE
	RCC->APB2ENR =5;                      // GPIOA_CLOCK_ENABLE & AF_ENABLE 
	GPIOA->CRL |=(0x0A <<1);              // PIN A1 CONFIGURATION AS : ALTERNATE FUNCTION PUSH-PULL [TIM2_CH2 : A1]
	TIM2->PSC=72-1;
	TIM2->ARR=1000-1;
	TIM2->CCR2=500-1;
	while(1)
	{
    
	}
}