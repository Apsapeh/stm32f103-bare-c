#include <stddef.h>
#include <stdint.h>

#include "registers.h"
#include "rtt.h"

#define LED 13
#define LED_DELAY 6000000


static inline void setup_frequency(void);
static inline void setup_systick(void);

int main(void) {
    rtt_init((const char*[]) {"Terminal"}, (uint32_t[]) {RTT_BUFFER_MODE_BLOCK_IF_FULL}, NULL, NULL);

    // Set SYSCLK to 48MHz
    setup_frequency();

    // Enable APM2ENR bus
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    volatile uint32_t dummy;
    dummy = RCC->APB2ENR;
    dummy = RCC->APB2ENR;

    setup_systick();

    gpio_port_cfg(GPIOC, LED, GPIO_CNF_OUTPUT_PUSH_PULL, GPIO_MODE_OUTPUT_2MHZ);

    while (1) {
    }

    return 0;
}


/* === Set SYSCLK to 48MHz === */
static inline void setup_frequency(void) {
    // Enable flash latency to one (24MHz < SYSCLK <= 48MHz), cuz max frequency of the Flash is 24MHz
    FLASH->ACR |= FLASH_ACR_LATENCY_ONE;

    // Enable HSE and wait until it enables
    RCC->CR |= RCC_CR_HSEON_ON;
    while ((RCC->CR & RCC_CR_HSERDY_Msk) != RCC_CR_HSERDY_READY) {
    }

    // Setup PLL. HSE -> PLE (HSE * 6) ->
    RCC->CFGR |= RCC_CFGR_PLLMUL_X6 | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLXTPRE_HSE_NO_DIV;

    // Enable PLL and wait until it enables
    RCC->CR |= RCC_CR_PLLON_ON;
    while ((RCC->CR & RCC_CR_PLLRDY_Msk) != RCC_CR_PLLRDY_LOCKED) {
    }

    // Switch SYSCLK to PLL, and wait until it switches
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL) {
    }
}


static inline void setup_systick(void) {
    SysTick->LOAD = LED_DELAY - 1;
    SysTick->VAL = 0;

    SysTick->CTRL |= SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT;
}


void systick_hdl(void) {
    GPIOC->ODR ^= 1 << LED;

    static uint32_t blink_counter = 0;
    rprintf(0, "Blink #%u\n", ++blink_counter);
}
