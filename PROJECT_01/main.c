#include "stm32f4xx.h"

/* RCC AHB1 and APB1 address definitions */
#define    RCC_BASE_ADDR        (0x40023800)

#define    AHB1ENR_OFFSET       (0x30)
#define    RCC_AHB1ENR          (*((volatile uint32_t *)(RCC_BASE_ADDR + AHB1ENR_OFFSET)))
#define    GPIOAEN              (1U << 0)

#define    APB1ENR_OFFSET       (0x40)
#define    RCC_APB1ENR          (*((volatile uint32_t *)(RCC_BASE_ADDR + APB1ENR_OFFSET)))
#define    TIM2EN               (1U << 0)

/* GPIOA address definitions */

#define    GPIOA_BASE_ADDR      (0x40020000)

#define    GPIOA_MODER_OFFSET   (0x00)
#define    GPIOA_MODER          (*((volatile uint32_t *)(GPIOA_BASE_ADDR + GPIOA_MODER_OFFSET)))
#define    PIN5_OUTPUT          (1U << 10)

#define    GPIOA_ODR_OFFSET     (0x14)
#define    GPIOA_ODR            (*((volatile uint32_t *)(GPIOA_BASE_ADDR + GPIOA_ODR_OFFSET)))

/* TIM2 address definitions */

#define    TIM2_BASE_ADDR       (0x40000000)

#define    TIM2_CR1_OFFSET      (0x00)
#define    TIM2_CR1             (*((volatile uint32_t *)(TIM2_BASE_ADDR + TIM2_CR1_OFFSET)))

#define    TIM2_SR_OFFSET       (0x10)
#define    TIM2_SR              (*((volatile uint32_t *)(TIM2_BASE_ADDR + TIM2_SR_OFFSET)))

#define    TIM2_PSC_OFFSET      (0x28)
#define    TIM2_PSC             (*((volatile uint32_t *)(TIM2_BASE_ADDR + TIM2_PSC_OFFSET)))

#define    TIM2_ARR_OFFSET      (0x2C)
#define    TIM2_ARR             (*((volatile uint32_t *)(TIM2_BASE_ADDR + TIM2_ARR_OFFSET)))


void delay_ms(uint32_t ms)
{
	TIM2_PSC = 16000 - 1;	// 16 000 000 / 16 000 = 1kHz (1ms)
	TIM2_ARR = ms;
	TIM2_CR1 = 1;		// timer başlat

	while (!(TIM2_SR & (1U << 0)));	// UIF (Update Flag) set edilene kadar bekle

	TIM2_SR &= ~(1U << 0);
}

int main(void)
{
	RCC_AHB1ENR |= GPIOAEN;
	GPIOA_MODER |= PIN5_OUTPUT;
	RCC_APB1ENR |= TIM2EN;

	while(1) {

		GPIOA_ODR ^= (1U << 5);
		delay_ms(300);
	}
}
