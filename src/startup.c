#include <stddef.h>
#include <stdint.h>

const size_t SRAM_START = 0x20000000;
const size_t SRAM_SIZE = 20 * 1024;
const size_t SRAM_END = SRAM_START + SRAM_SIZE;
const size_t STACK_START = SRAM_END;

void default_hdl(void);
void reset_hdl(void);
void nmi_hdl(void) __attribute__((weak, alias("default_hdl")));
void hard_fault_hdl(void) __attribute__((weak, alias("default_hdl")));
void mem_manage_hdl(void) __attribute__((weak, alias("default_hdl")));
void bus_hdl(void) __attribute__((weak, alias("default_hdl")));
void usage_fault_hdl(void) __attribute__((weak, alias("default_hdl")));
void svcall_hdl(void) __attribute__((weak, alias("default_hdl")));
void debug_monitor_hdl(void) __attribute__((weak, alias("default_hdl")));
void pendsv_hdl(void) __attribute__((weak, alias("default_hdl")));
void systick_hdl(void) __attribute__((weak, alias("default_hdl")));
void wwdg_hdl(void) __attribute__((weak, alias("default_hdl")));
void pvd_hdl(void) __attribute__((weak, alias("default_hdl")));
void tamper_hdl(void) __attribute__((weak, alias("default_hdl")));
void rtc_hdl(void) __attribute__((weak, alias("default_hdl")));
void flash_hdl(void) __attribute__((weak, alias("default_hdl")));
void rcc_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti0_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti1_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti2_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti3_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti4_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel1_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel2_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel3_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel4_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel5_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel6_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma1_channel7_hdl(void) __attribute__((weak, alias("default_hdl")));
void adc1_2_hdl(void) __attribute__((weak, alias("default_hdl")));
void usb_hp_can_tx_hdl(void) __attribute__((weak, alias("default_hdl")));
void usb_lp_can_rx0_hdl(void) __attribute__((weak, alias("default_hdl")));
void can_rx1_hdl(void) __attribute__((weak, alias("default_hdl")));
void can_sce_hdl(void) __attribute__((weak, alias("default_hdl")));
void exit9_5_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim1_brk_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim1_up_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim1_trg_com_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim1_cc_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim2_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim3_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim4_hdl(void) __attribute__((weak, alias("default_hdl")));
void i2c1_ev_hdl(void) __attribute__((weak, alias("default_hdl")));
void i2c1_er_hdl(void) __attribute__((weak, alias("default_hdl")));
void i2c2_ev_hdl(void) __attribute__((weak, alias("default_hdl")));
void i2c2_er_hdl(void) __attribute__((weak, alias("default_hdl")));
void spi1_hdl(void) __attribute__((weak, alias("default_hdl")));
void spi2_hdl(void) __attribute__((weak, alias("default_hdl")));
void usart1_hdl(void) __attribute__((weak, alias("default_hdl")));
void usart2_hdl(void) __attribute__((weak, alias("default_hdl")));
void usart3_hdl(void) __attribute__((weak, alias("default_hdl")));
void exti15_10_hdl(void) __attribute__((weak, alias("default_hdl")));
void rtc_alarm_hdl(void) __attribute__((weak, alias("default_hdl")));
void usb_wakeup_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim8_brk_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim8_up_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim8_trg_com_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim8_cc_hdl(void) __attribute__((weak, alias("default_hdl")));
void adc3_hdl(void) __attribute__((weak, alias("default_hdl")));
void fsmc_hdl(void) __attribute__((weak, alias("default_hdl")));
void sdio_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim5_hdl(void) __attribute__((weak, alias("default_hdl")));
void spi3_hdl(void) __attribute__((weak, alias("default_hdl")));
void uart4_hdl(void) __attribute__((weak, alias("default_hdl")));
void uart5_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim6_hdl(void) __attribute__((weak, alias("default_hdl")));
void tim7_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma2_channel1_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma2_channel2_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma2_channel3_hdl(void) __attribute__((weak, alias("default_hdl")));
void dma2_channel4_5_hdl(void) __attribute__((weak, alias("default_hdl")));

#define ISR_VECTOR_SIZE 76

const uint32_t isr_vector[ISR_VECTOR_SIZE]
    __attribute__((section(".isr_vector"))) = {
        STACK_START,
        (uint32_t)reset_hdl,
        (uint32_t)nmi_hdl,
        (uint32_t)hard_fault_hdl,
        (uint32_t)mem_manage_hdl,
        (uint32_t)bus_hdl,
        (uint32_t)usage_fault_hdl,
        0,
        0,
        0,
        0,
        (uint32_t)svcall_hdl,
        (uint32_t)debug_monitor_hdl,
        0,
        (uint32_t)pendsv_hdl,
        (uint32_t)systick_hdl,
        (uint32_t)wwdg_hdl,
        (uint32_t)pvd_hdl,
        (uint32_t)tamper_hdl,
        (uint32_t)rtc_hdl,
        (uint32_t)flash_hdl,
        (uint32_t)rcc_hdl,
        (uint32_t)exti0_hdl,
        (uint32_t)exti1_hdl,
        (uint32_t)exti2_hdl,
        (uint32_t)exti3_hdl,
        (uint32_t)exti4_hdl,
        (uint32_t)dma1_channel1_hdl,
        (uint32_t)dma1_channel2_hdl,
        (uint32_t)dma1_channel3_hdl,
        (uint32_t)dma1_channel4_hdl,
        (uint32_t)dma1_channel5_hdl,
        (uint32_t)dma1_channel6_hdl,
        (uint32_t)dma1_channel7_hdl,
        (uint32_t)adc1_2_hdl,
        (uint32_t)usb_hp_can_tx_hdl,
        (uint32_t)usb_lp_can_rx0_hdl,
        (uint32_t)can_rx1_hdl,
        (uint32_t)can_sce_hdl,
        (uint32_t)exit9_5_hdl,
        (uint32_t)tim1_brk_hdl,
        (uint32_t)tim1_up_hdl,
        (uint32_t)tim1_trg_com_hdl,
        (uint32_t)tim1_cc_hdl,
        (uint32_t)tim2_hdl,
        (uint32_t)tim3_hdl,
        (uint32_t)tim4_hdl,
        (uint32_t)i2c1_ev_hdl,
        (uint32_t)i2c1_er_hdl,
        (uint32_t)i2c2_ev_hdl,
        (uint32_t)i2c2_er_hdl,
        (uint32_t)spi1_hdl,
        (uint32_t)spi2_hdl,
        (uint32_t)usart1_hdl,
        (uint32_t)usart2_hdl,
        (uint32_t)usart3_hdl,
        (uint32_t)exti15_10_hdl,
        (uint32_t)rtc_alarm_hdl,
        (uint32_t)usb_wakeup_hdl,
        (uint32_t)tim8_brk_hdl,
        (uint32_t)tim8_up_hdl,
        (uint32_t)tim8_trg_com_hdl,
        (uint32_t)tim8_cc_hdl,
        (uint32_t)adc3_hdl,
        (uint32_t)fsmc_hdl,
        (uint32_t)sdio_hdl,
        (uint32_t)tim5_hdl,
        (uint32_t)spi3_hdl,
        (uint32_t)uart4_hdl,
        (uint32_t)uart5_hdl,
        (uint32_t)tim6_hdl,
        (uint32_t)tim7_hdl,
        (uint32_t)dma2_channel1_hdl,
        (uint32_t)dma2_channel2_hdl,
        (uint32_t)dma2_channel3_hdl,
        (uint32_t)dma2_channel4_5_hdl,
};

void default_hdl(void) {
  while (1) {
  }
}

int main(void);
extern uint32_t _etext, _sdata, _edata, _sidata, _sbss, _ebss;

void reset_hdl(void) {
  // Copy static data from FLASH to SRAM
  uint32_t *data_ptr = &_sidata;
  uint32_t *sram_ptr = &_sdata;
  const uint32_t *sram_end_ptr = &_edata;

  while (sram_ptr != sram_end_ptr) {
    *(sram_ptr++) = *(data_ptr++);
  }

  // Init .bss sections with 0
  uint32_t *bss_ptr = &_sbss;

  const uint32_t *bss_end_ptr = &_ebss;
  while (bss_ptr != bss_end_ptr) {
    *(bss_ptr++) = 0;
  }

  main();
}
