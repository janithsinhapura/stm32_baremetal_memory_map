#include <stdint.h>

#define PERIPH_BASE              	(0x40000000UL)
#define APB2_PERIPH_OFFSET       	(0x00010000UL)
#define APB2_PERIP_BASE          	(PERIPH_BASE + APB2_PERIPH_OFFSET)

#define GPIOC_OFFSET            	(0x00001000UL)
#define GPIOC_BASE               	(APB2_PERIP_BASE + GPIOC_OFFSET)

#define RCC_OFFSET               	(0x00021000UL)
#define RCC_BASE                 	(PERIPH_BASE + RCC_OFFSET)

#define GPIOCEN                  	(1U<<4)

#define	MODE13						((0x3U<<20))

#define ODR13                    	(1U<<13)

#define __IO 						volatile

typedef struct {
	__IO uint32_t DUMMY[6];
	__IO uint32_t APB2ENR;
} RCC_TypeDef;

typedef struct {
	__IO uint32_t CRL;
	__IO uint32_t CRH;
	__IO uint32_t IDR;
	__IO uint32_t ODR;

} GPIO_TypeDef;

void delay(volatile unsigned int count) {
	while (count > 0) {
		count--;
	}
}

#define RCC				((RCC_TypeDef*)RCC_BASE)
#define GPIOC			((GPIO_TypeDef*)GPIOC_BASE)

int main(void) {

	RCC->APB2ENR |= GPIOCEN;
	GPIOC->CRH |= MODE13;

	while (1) {
		GPIOC->ODR ^= (1U << 13);
		delay(20000);
	}

	return 0;
}
