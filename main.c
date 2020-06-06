#include "stm32f10x.h"

void SysTickDelayMs(int n);

int main()
{
	__disable_irq();
	RCC->APB2ENR |=(1<<4);      // ENABLE_CLOCK_FOR_LED_PIN
	RCC->APB2ENR |=(1<<2);      // ENABLE_CLOCK_FOR_INTERRUPT_PIN
	RCC->APB2ENR |=(1<<0);      // ENABLE_ALTERNATE_FUNCTION_CLOCK
	
	GPIOC->CRH |= (0x02<<(5*4));     // CONFIGURE_LED_PIN_AS_OUTPUT_TYPE
//	GPIOC->CRH|=0x00200000;        // GPIOC OUTPUT =>  PUSH_PULL  ; PIN : 13
	GPIOA->CRL |= ~(1<<0);           // CONFIGURE_GPIO_PIN_A0_IN_INPUT_MODE [BY DEFAULT PIN SET TO 0. i.e. INPUT MODE]
	
	AFIO->EXTICR[0]|=0x00;           // CONFIGURING_GPIO_PIN_A0_AS_EXTI
	EXTI->IMR |=(1<<0);              // EXTI_UNMASK_FOR_LINE_A0
	EXTI->RTSR |=(1<<0);             // EXTI_ENABLED_FOR_RISING_EDGE_FOR_LINE_A0
	
	NVIC_EnableIRQ(EXTI0_IRQn);      /* NVIC_LINE_ENABLE */
	__enable_irq();                  /* ENABLE_IRQ */
	
	GPIOC->BSRR|=(1<<29);
	SysTickDelayMs(1000);
	GPIOC->BSRR|=(1<<13);
	
	while(1)
	{
	}
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR|=(1<<0);                    // CLEAR_INTERRUPT_REQUEST, OTHERWISE_INTERRUPT_WILL_STUCK_HERE
	
	GPIOC->BSRR|=(1<<29);	               // RESETTING GPIO_PIN
	SysTickDelayMs(100);
	GPIOC->BSRR|=(1<<13);                // SETTING_GPIO_PIN
	SysTickDelayMs(100);
}

void SysTickDelayMs(int n)
{
	SysTick->CTRL=0x5;                   // ENABLE SYSTICK  [CLOCK SOURCE: AHB ; SYSTICK : ENABLE ]
	SysTick->LOAD=72000-1;               // RELOAD NUMBER OF CYCLES PER MILLISECONDS
//	SysTick->VAL=0;                    // CLEAR CURRENT VALUE REGISTER

	for(int i=0;i<n;i++)
	while(!(SysTick->CTRL & (1<<16)));   // Check flag for systick underflow 
	
		SysTick->CTRL=0;             // Systick Disable for next time or keep systick counting for every millisecond.
}