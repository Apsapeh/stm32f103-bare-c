#include "registers.h"
#include <stdint.h>


/* ==============>  GPIO  <=============== */
void gpio_port_cfg(
        volatile struct GpioDef* const gpio, const uint8_t port, const uint8_t cnf, const uint8_t mode
) {
    volatile uint32_t* const reg = port < 8 ? &gpio->CRL : &gpio->CRH;
    const uint8_t port_idx = port < 8 ? port : port - 8;
    const uint8_t shift = port_idx << 2;
    const uint32_t mask = (uint32_t) 0xF << shift;
    const uint32_t cfg = (((uint32_t) cnf << 2) | mode) << shift;
    *reg = (*reg & ~mask) | cfg;
}
