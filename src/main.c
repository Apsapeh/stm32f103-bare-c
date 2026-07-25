#include <stddef.h>
#include <stdint.h>

const size_t RCC_BASE = 0x40021000;
const size_t RCC_APB2ENR_OFF = 0x18;
const size_t RCC_APB2ENR = RCC_BASE + RCC_APB2ENR_OFF;
const size_t RCC_APB2ENR_IOPCEN_OFF = 0x04;
volatile uint32_t *const RCC_APB2ENR_PTR = (volatile uint32_t *)RCC_APB2ENR;

const size_t GPIO_MODE_OFF = 0x00;
const size_t GPIO_CNF_OFF = 0x02;
const size_t GPIO_CRH_OFF = 0x04;
const size_t GPIO_BSRR_OFF = 0x10;
const size_t GPIO_BRR_OFF = 0x14;
const size_t GPIOC_BASE = 0x40011000;
const size_t GPIOC_CRH = GPIOC_BASE + GPIO_CRH_OFF;
const size_t GPIOC_BSRR = GPIOC_BASE + GPIO_BSRR_OFF;
const size_t GPIOC_BRR = GPIOC_BASE + GPIO_BRR_OFF;
volatile uint32_t *const GPIOC_BASE_PTR = (volatile uint32_t *)GPIOC_BASE;
volatile uint32_t *const GPIOC_CRH_PTR = (volatile uint32_t *)GPIOC_CRH;
volatile uint32_t *const GPIOC_BSRR_PTR = (volatile uint32_t *)GPIOC_BSRR;
volatile uint32_t *const GPIOC_BRR_PTR = (volatile uint32_t *)GPIOC_BRR;

const size_t OUTPUT_PUSH_PULL = 0b00;
const size_t OUTPUT_MODE_2MHZ = 0b10;

const size_t LED = 13;
const size_t LED_CRH = 5;
const size_t LED_DELAY = 1000000;

int main(void) {
  // Enable APM2ENR bus
  *RCC_APB2ENR_PTR |= 1 << RCC_APB2ENR_IOPCEN_OFF;

  volatile uint32_t dummy;
  dummy = *RCC_APB2ENR_PTR;
  dummy = *RCC_APB2ENR_PTR;

  // Setup PC13 to push-pull mode
  const size_t mode_setup =
      (OUTPUT_PUSH_PULL << GPIO_CNF_OFF) | (OUTPUT_MODE_2MHZ << GPIO_MODE_OFF);
  *GPIOC_CRH_PTR |= mode_setup << (4 * LED_CRH);

  while (1) {
    // Enable led
    *GPIOC_BRR_PTR = 1 << LED;

    // Sleep
    for (volatile size_t i = 0; i < LED_DELAY; i++)
      ;

    // Disable led
    *GPIOC_BSRR_PTR = 1 << LED;

    // Sleep
    for (volatile size_t i = 0; i < LED_DELAY; i++)
      ;
  }

  return 0;
}
