#include "stm32f4xx.h"


#define RCC_BASE_ADDR       (0x40023800)

#define AHB1ENR_OFFSET      (0x30)
#define RCC_AHB1ENR         (*((volatile uint32_t*)(RCC_BASE_ADDR + AHB1ENR_OFFSET)))
#define GPIOAEN             (1U << 0)

#define APB1ENR_OFFSET      (0x40)
#define RCC_APB1ENR         (*((volatile uint32_t*)(RCC_BASE_ADDR + APB1ENR_OFFSET)))
#define TIM2EN              (1U << 0)


#define GPIOA_BASE_ADDR     (0x40020000)

#define MODER_OFFSET        (0x00)
#define GPIOA_MODER         (*((volatile uint32_t*)(GPIOA_BASE_ADDR + MODER_OFFSET)))

#define ODR_OFFSET          (0x14)
#define GPIOA_ODR           (*((volatile uint32_t*)(GPIOA_BASE_ADDR + ODR_OFFSET)))


#define TIM2_BASE_ADDR      (0x40000000)

#define PSC_OFFSET          (0x28)
#define TIM2_PSC            (*((volatile uint32_t*)(TIM2_BASE_ADDR + PSC_OFFSET)))

#define ARR_OFFSET          (0x2C)
#define TIM2_ARR            (*((volatile uint32_t*)(TIM2_BASE_ADDR + ARR_OFFSET)))

#define DIER_OFFSET         (0x0C)
#define TIM2_DIER           (*((volatile uint32_t*)(TIM2_BASE_ADDR + DIER_OFFSET)))
#define TIM2_UIEN           (1U << 0)

#define CR1_OFFSET          (0x00)
#define TIM2_CR1            (*((volatile uint32_t*)(TIM2_BASE_ADDR + CR1_OFFSET)))

#define SR_OFFSET           (0x10)
#define TIM2_SR             (*((volatile uint32_t*)(TIM2_BASE_ADDR + SR_OFFSET)))

#define NVIC_ISER0          (*((volatile uint32_t*)0xE000E100))

void TIM2_IRQHandler(void)
{
	if (TIM2_SR & (1U << 0)) {	// Update interrup flag is 1?
		TIM2_SR &= ~(1 << 0);	// set 0 to UIF
		GPIOA_ODR ^= (1U << 5);		// Led toggle
	}
}


void TIM2_Init(void)
{
	RCC_APB1ENR |= TIM2EN;

	TIM2_PSC = 16000 - 1;		// 1ms
	TIM2_ARR = 1000;			// 1 saniye periyot
	TIM2_DIER |= TIM2_UIEN;		// Update Interrupt Enable
	TIM2_CR1 |= (1U << 0);		// Timer Başlatma
	NVIC_ISER0 |= (1U << 28);	// TIM2 kesmesini etkinleştir
}


int main(void)
{
	RCC_AHB1ENR |= GPIOAEN;
	GPIOA_MODER |= (1U << 10);
	GPIOA_MODER &= ~(1U << 11);

	TIM2_Init();

	while (1) {

	}
}


