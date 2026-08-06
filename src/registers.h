#include <stddef.h>
#include <stdint.h>

#define BASE_2_PTR(type, name, base) volatile type* const name = (volatile type*) base;

#define __IO volatile

/* ==============> Useful macros <============ */

/* ==============>  SysTick  <=============== */
struct SysTickDef {
    __IO uint32_t CTRL;
    __IO uint32_t LOAD;
    __IO uint32_t VAL;
    __IO uint32_t CALIB;
};

enum {
    SysTick_CTRL_ENABLE_Pos,
    SysTick_CTRL_TICKINT_Pos,
    SysTick_CTRL_CLKSOURCE_Pos,
    SysTick_CTRL_COUNTFLAG_Pos = 16,
};

#define SysTick_CTRL_ENABLE (1 << SysTick_CTRL_ENABLE_Pos)
#define SysTick_CTRL_TICKINT (1 << SysTick_CTRL_TICKINT_Pos)
#define SysTick_CTRL_CLKSOURCE_AHB (1 << SysTick_CTRL_CLKSOURCE_Pos)
#define SysTick_CTRL_COUNTFLAG (1 << SysTick_CTRL_COUNTFLAG_Pos)

#define SysTick_Base 0xE000E010

// BASE_2_PTR(struct SysTickDef, SysTick, SysTick_Base)
#define SysTick ((volatile struct SysTickDef*) SysTick_Base)

/* ==============> Flash <=============== */
struct FlashDef {
    __IO uint32_t ACR;
    __IO uint32_t KEYR;
    __IO uint32_t OPTKEY_R;
    __IO uint32_t SR;
    __IO uint32_t CR;
    __IO uint32_t AR;
    __IO uint32_t __reserved;
    __IO uint32_t OBR;
    __IO uint32_t WRPR;
};

#define FLASH_ACR_LATENCY_ONE (0x1)
#define FLASH_ACR_LATENCY_TWO (0x2)

#define FLASH_Base 0x40022000

#define FLASH ((volatile struct FlashDef*) FLASH_Base)

/* ==============>  RCC  <=============== */
struct RccDef {
    __IO uint32_t CR;
    __IO uint32_t CFGR;
    __IO uint32_t CIR;
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB1RSTR;
    __IO uint32_t AHBENR;
    __IO uint32_t APB2ENR;
    __IO uint32_t APB1ENR;
    __IO uint32_t BRCR;
    __IO uint32_t CSR;
};

// CR
enum {
    RCC_CR_HSION_Pos,
    RCC_CR_HSIRDY_Pos,
    RCC_CR_HSITRIM_Pos = 3,
    RCC_CR_HSICAL_Pos = 8,
    RCC_CR_HSEON_Pos = 16,
    RCC_CR_HSERDY_Pos,
    RCC_CR_HSEBYP_Pos,
    RCC_CR_CSSON_Pos,
    RCC_CR_PLLON_Pos = 24,
    RCC_CR_PLLRDY_Pos,
};

#define RCC_CR_HSION_Msk (0x1 << RCC_CR_HSION_Pos)
#define RCC_CR_HSIRDY_Msk (0x1 << RCC_CR_HSIRDY_Pos)
#define RCC_CR_HSITRIM_Msk (0x1F << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSICAL_Msk (0xFF << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSEON_Msk (0x1 << RCC_CR_HSEON_Pos)
#define RCC_CR_HSERDY_Msk (0x1 << RCC_CR_HSERDY_Pos)
#define RCC_CR_HSEBYP_Msk (0x1 << RCC_CR_HSEBYP_Pos)
#define RCC_CR_CSSON_Msk (0x1 << RCC_CR_CSSON_Pos)
#define RCC_CR_PLLON_Msk (0x1 << RCC_CR_PLLON_Pos)
#define RCC_CR_PLLRDY_Msk (0x1 << RCC_CR_PLLRDY_Pos)

enum {
    RCC_CR_HSION_OFF_Val,
    RCC_CR_HSION_ON_Val,
};

// clang-format off
#define RCC_CR_HSION_OFF (RCC_CR_HSION_OFF_Val << RCC_CR_HSION_Pos)
#define RCC_CR_HSION_ON (RCC_CR_HSION_ON_Val << RCC_CR_HSION_Pos)
// clang-format on


enum {
    RCC_CR_HSIRDY_NOT_READY_Val,
    RCC_CR_HSIRDY_READY_Val,
};

// clang-format off
#define RCC_CR_HSIRDY_NOT_READY (RCC_CR_HSIRDY_NOT_READY_Val << RCC_CR_HSIRDY_Pos)
#define RCC_CR_HSIRDY_READY (RCC_CR_HSIRDY_READY_Val << RCC_CR_HSIRDY_Pos)
// clang-format on


enum {
    RCC_CR_HSEON_OFF_Val,
    RCC_CR_HSEON_ON_Val,
};

// clang-format off
#define RCC_CR_HSEON_OFF (RCC_CR_HSEON_OFF_Val << RCC_CR_HSEON_Pos)
#define RCC_CR_HSEON_ON (RCC_CR_HSEON_ON_Val << RCC_CR_HSEON_Pos)
// clang-format on


enum {
    RCC_CR_HSERDY_NOT_READY_Val,
    RCC_CR_HSERDY_READY_Val,
};

// clang-format off
#define RCC_CR_HSERDY_NOT_READY (RCC_CR_HSERDY_NOT_READY_Val << RCC_CR_HSERDY_Pos)
#define RCC_CR_HSERDY_READY (RCC_CR_HSERDY_READY_Val << RCC_CR_HSERDY_Pos)
// clang-format on


enum {
    RCC_CR_HSEBYP_NOT_BYPASSED_Val,
    RCC_CR_HSEBYP_BYPASSED_Val,
};

// clang-format off
#define RCC_CR_HSEBYP_NOT_BYPASSED (RCC_CR_HSEBYP_NOT_BYPASSED_Val << RCC_CR_HSEBYP_Pos)
#define RCC_CR_HSEBYP_BYPASSED (RCC_CR_HSEBYP_BYPASSED_Val << RCC_CR_HSEBYP_Pos)
// clang-format on


enum {
    RCC_CR_CSSON_OFF_Val,
    RCC_CR_CSSON_ON_Val,
};

// clang-format off
#define RCC_CR_CSSON_OFF (RCC_CR_CSSON_OFF_Val << RCC_CR_CSSON_Pos)
#define RCC_CR_CSSON_ON (RCC_CR_CSSON_ON_Val << RCC_CR_CSSON_Pos)
// clang-format on


enum {
    RCC_CR_PLLON_OFF_Val,
    RCC_CR_PLLON_ON_Val,
};

// clang-format off
#define RCC_CR_PLLON_OFF (RCC_CR_PLLON_OFF_Val << RCC_CR_PLLON_Pos)
#define RCC_CR_PLLON_ON (RCC_CR_PLLON_ON_Val << RCC_CR_PLLON_Pos)
// clang-format on


enum {
    RCC_CR_PLLRDY_UNLOCKED_Val,
    RCC_CR_PLLRDY_LOCKED_Val,
};

// clang-format off
#define RCC_CR_PLLRDY_UNLOCKED (RCC_CR_PLLRDY_UNLOCKED_Val << RCC_CR_PLLRDY_Pos)
#define RCC_CR_PLLRDY_LOCKED (RCC_CR_PLLRDY_LOCKED_Val << RCC_CR_PLLRDY_Pos)
// clang-format on


// CFGR

enum {
    RCC_CFGR_SW_Pos,
    RCC_CFGR_SWS_Pos = 2,
    RCC_CFGR_HPRE_Pos = 4,
    RCC_CFGR_PPRE1_Pos = 8,
    RCC_CFGR_PPRE2_Pos = 11,
    RCC_CFGR_ADCPRE_Pos = 14,
    RCC_CFGR_PLLSRC_Pos = 16,
    RCC_CFGR_PLLXTPRE_Pos = 17,
    RCC_CFGR_PLLMUL_Pos = 18,
    RCC_CFGR_USBPRE_Pos = 22,
    RCC_CFGR_MCO_Pos = 24,
};

#define RCC_CFGR_SW_Msk (0x3 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SWS_Msk (0x3 << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_HPRE_Msk (0xF << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_PPRE1_Msk (0x7 << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE2_Msk (0x7 << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_ADCPRE_Msk (0x3 << RCC_CFGR_ADCPRE_Pos)
#define RCC_CFGR_PLLSRC_Msk (0x1 << RCC_CFGR_PLLSRC_Pos)
#define RCC_CFGR_PLLXTPRE_Msk (0x1 << RCC_PLLXTPRE_SW_Pos)
#define RCC_CFGR_PLLMUL_Msk (0xF << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_USBPRE_Msk (0x1 << RCC_CFGR_USBPRE_Pos)
#define RCC_CFGR_MCO_Msk (0x7 << RCC_CFGR_MCO_Pos)

// enum {
//     RCC_CFGR_SW_Len = 2,
//     RCC_CFGR_SWS_Len = 2,
//     RCC_CFGR_HPRE_Len = 4,
//     RCC_CFGR_PPRE1_Len = 3,
//     RCC_CFGR_PPRE2_Len = 3,
//     RCC_CFGR_ADCPRE_Len = 2,
//     RCC_CFGR_PLLSRC_Len = 1,
//     RCC_CFGR_PLLXTPRE_Len = 1,
//     RCC_CFGR_PLLMUL_Len = 4,
//     RCC_CFGR_USBPRE_Len = 1,
//     RCC_CFGR_MCO_Len = 3,
// };


enum {
    RCC_CFGR_SW_HSI_Val,
    RCC_CFGR_SW_HSE_Val,
    RCC_CFGR_SW_PLL_Val,
};

// clang-format off
#define RCC_CFGR_SW_HSI (RCC_CFGR_SW_HSI_Val << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_HSE (RCC_CFGR_SW_HSE_Val << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLL (RCC_CFGR_SW_PLL_Val << RCC_CFGR_SW_Pos)
// clang-format on

enum {
    RCC_CFGR_SWS_HSI_Val,
    RCC_CFGR_SWS_HSE_Val,
    RCC_CFGR_SWS_PLL_Val,
};

// clang-format off
#define RCC_CFGR_SWS_HSI (RCC_CFGR_SWS_HSI_Val << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_HSE (RCC_CFGR_SWS_HSE_Val << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_PLL (RCC_CFGR_SWS_PLL_Val << RCC_CFGR_SWS_Pos)
// clang-format on


enum {
    RCC_CFGR_HPRE_SYSCLK_NO_DIV_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_2_Val = 0x8,
    RCC_CFGR_HPRE_SYSCLK_DIV_4_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_8_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_16_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_64_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_128_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_256_Val,
    RCC_CFGR_HPRE_SYSCLK_DIV_512_Val,
};

// clang-format off
#define RCC_CFGR_HPRE_SYSCLK_NO_DIV (RCC_CFGR_HPRE_SYSCLK_NO_DIV_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_2 (RCC_CFGR_HPRE_SYSCLK_DIV_2_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_4 (RCC_CFGR_HPRE_SYSCLK_DIV_4_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_8 (RCC_CFGR_HPRE_SYSCLK_DIV_8_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_16 (RCC_CFGR_HPRE_SYSCLK_DIV_16_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_64 (RCC_CFGR_HPRE_SYSCLK_DIV_64_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_128 (RCC_CFGR_HPRE_SYSCLK_DIV_128_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_256 (RCC_CFGR_HPRE_SYSCLK_DIV_256_Val << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_SYSCLK_DIV_512 (RCC_CFGR_HPRE_SYSCLK_DIV_512_Val << RCC_CFGR_HPRE_Pos)
// clang-format on


enum {
    RCC_CFGR_PPRE1_HCLK_NO_DIV_Val,
    RCC_CFGR_PPRE1_HCLK_DIV_2_Val = 0x4,
    RCC_CFGR_PPRE1_HCLK_DIV_4_Val,
    RCC_CFGR_PPRE1_HCLK_DIV_8_Val,
    RCC_CFGR_PPRE1_HCLK_DIV_16_Val,
};

// clang-format off
#define RCC_CFGR_PPRE1_HCLK_NO_DIV (RCC_CFGR_PPRE1_HCLK_NO_DIV_Val << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_HCLK_DIV_2 (RCC_CFGR_PPRE1_HCLK_DIV_2_Val << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_HCLK_DIV_4 (RCC_CFGR_PPRE1_HCLK_DIV_4_Val << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_HCLK_DIV_8 (RCC_CFGR_PPRE1_HCLK_DIV_8_Val << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_HCLK_DIV_16 (RCC_CFGR_PPRE1_HCLK_DIV_16_Val << RCC_CFGR_PPRE1_Pos)
// clang-format on


enum {
    RCC_CFGR_PPRE2_HCLK_NO_DIV_Val,
    RCC_CFGR_PPRE2_HCLK_DIV_2_Val = 0x4,
    RCC_CFGR_PPRE2_HCLK_DIV_4_Val,
    RCC_CFGR_PPRE2_HCLK_DIV_8_Val,
    RCC_CFGR_PPRE2_HCLK_DIV_16_Val,
};

// clang-format off
#define RCC_CFGR_PPRE2_HCLK_NO_DIV (RCC_CFGR_PPRE2_HCLK_NO_DIV_Val << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_HCLK_DIV_2 (RCC_CFGR_PPRE2_HCLK_DIV_2_Val << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_HCLK_DIV_4 (RCC_CFGR_PPRE2_HCLK_DIV_4_Val << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_HCLK_DIV_8 (RCC_CFGR_PPRE2_HCLK_DIV_8_Val << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_HCLK_DIV_16 (RCC_CFGR_PPRE2_HCLK_DIV_16_Val << RCC_CFGR_PPRE2_Pos)
// clang-format on


enum {
    RCC_CFGR_ADCPRE_PCLK2_DIV_2_Val,
    RCC_CFGR_ADCPRE_PCLK2_DIV_4_Val,
    RCC_CFGR_ADCPRE_PCLK2_DIV_6_Val,
    RCC_CFGR_ADCPRE_PCLK2_DIV_8_Val,
};

// clang-format off
#define RCC_CFGR_ADCPRE_PCLK2_DIV_2 (RCC_CFGR_ADCPRE_PCLK2_DIV_2_Val << RCC_CFGR_ADCPRE_Pos)
#define RCC_CFGR_ADCPRE_PCLK2_DIV_4 (RCC_CFGR_ADCPRE_PCLK2_DIV_4_Val << RCC_CFGR_ADCPRE_Pos)
#define RCC_CFGR_ADCPRE_PCLK2_DIV_6 (RCC_CFGR_ADCPRE_PCLK2_DIV_6_Val << RCC_CFGR_ADCPRE_Pos)
#define RCC_CFGR_ADCPRE_PCLK2_DIV_8 (RCC_CFGR_ADCPRE_PCLK2_DIV_8_Val << RCC_CFGR_ADCPRE_Pos)
// clang-format on


enum {
    RCC_CFGR_PLLSRC_HSI_DIV_BY_2_Val,
    RCC_CFGR_PLLSRC_HSE_Val,
};

// clang-format off
#define RCC_CFGR_PLLSRC_HSI_DIV_BY_2 (RCC_CFGR_PLLSRC_HSI_DIV_BY_2_Val << RCC_CFGR_PLLSRC_Pos)
#define RCC_CFGR_PLLSRC_HSE (RCC_CFGR_PLLSRC_HSE_Val << RCC_CFGR_PLLSRC_Pos)
// clang-format on


enum {
    RCC_CFGR_PLLXTPRE_HSE_NO_DIV_Val,
    RCC_CFGR_PLLXTPRE_HSE_DIV_2_Val,
};

// clang-format off
#define RCC_CFGR_PLLXTPRE_HSE_NO_DIV (RCC_CFGR_PLLXTPRE_HSE_NO_DIV_Val << RCC_CFGR_PLLXTPRE_Pos)
#define RCC_CFGR_PLLXTPRE_HSE_DIV_2 (RCC_CFGR_PLLXTPRE_HSE_DIV_2_Val << RCC_CFGR_PLLXTPRE_Pos)
// clang-format on


enum {
    RCC_CFGR_PLLMUL_X2_Val,
    RCC_CFGR_PLLMUL_X3_Val,
    RCC_CFGR_PLLMUL_X4_Val,
    RCC_CFGR_PLLMUL_X5_Val,
    RCC_CFGR_PLLMUL_X6_Val,
    RCC_CFGR_PLLMUL_X7_Val,
    RCC_CFGR_PLLMUL_X8_Val,
    RCC_CFGR_PLLMUL_X9_Val,
    RCC_CFGR_PLLMUL_X10_Val,
    RCC_CFGR_PLLMUL_X11_Val,
    RCC_CFGR_PLLMUL_X12_Val,
    RCC_CFGR_PLLMUL_X13_Val,
    RCC_CFGR_PLLMUL_X14_Val,
    RCC_CFGR_PLLMUL_X15_Val,
    RCC_CFGR_PLLMUL_X16_Val,
};

// clang-format off
#define RCC_CFGR_PLLMUL_X2 (RCC_CFGR_PLLMUL_X2_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X3 (RCC_CFGR_PLLMUL_X3_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X4 (RCC_CFGR_PLLMUL_X4_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X5 (RCC_CFGR_PLLMUL_X5_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X6 (RCC_CFGR_PLLMUL_X6_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X7 (RCC_CFGR_PLLMUL_X7_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X8 (RCC_CFGR_PLLMUL_X8_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X9 (RCC_CFGR_PLLMUL_X9_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X10 (RCC_CFGR_PLLMUL_X10_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X11 (RCC_CFGR_PLLMUL_X11_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X12 (RCC_CFGR_PLLMUL_X12_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X13 (RCC_CFGR_PLLMUL_X13_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X14 (RCC_CFGR_PLLMUL_X14_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X15 (RCC_CFGR_PLLMUL_X15_Val << RCC_CFGR_PLLMUL_Pos)
#define RCC_CFGR_PLLMUL_X16 (RCC_CFGR_PLLMUL_X16_Val << RCC_CFGR_PLLMUL_Pos)
// clang-format on


enum {
    RCC_CFGR_USBPRE_PLL_DIV_1_5_Val,
    RCC_CFGR_USBPRE_PLL_NO_DIV_Val,
};

// clang-format off
#define RCC_CFGR_USBPRE_PLL_DIV_1_5 (RCC_CFGR_USBPRE_PLL_DIV_1_5_Val << RCC_CFGR_USBPRE_Pos)
#define RCC_CFGR_USBPRE_PLL_NO_DIV (RCC_CFGR_USBPRE_PLL_NO_DIV_Val << RCC_CFGR_USBPRE_Pos)
// clang-format on


enum {
    RCC_CFGR_MCO_NO_CLOCK_Val,
    RCC_CFGR_MCO_SYSCLK_Val = 0x4,
    RCC_CFGR_MCO_HSI_Val,
    RCC_CFGR_MCO_HSE_Val,
    RCC_CFGR_MCO_PLL_DIV_2_Val,
};

// clang-format off
#define RCC_CFGR_MCO_NO_CLOCK (RCC_CFGR_MCO_NO_CLOCK_Val << RCC_CFGR_MCO_Pos)
#define RCC_CFGR_MCO_SYSCLK (RCC_CFGR_MCO_SYSCLK_Val << RCC_CFGR_MCO_Pos)
#define RCC_CFGR_MCO_HSI (RCC_CFGR_MCO_HSI_Val << RCC_CFGR_MCO_Pos)
#define RCC_CFGR_MCO_HSE (RCC_CFGR_MCO_HSE_Val << RCC_CFGR_MCO_Pos)
#define RCC_CFGR_MCO_PLL_DIV_2 (RCC_CFGR_MCO_PLL_DIV_2_Val << RCC_CFGR_MCO_Pos)
// clang-format on


// APB2ENR

enum {
    RCC_APB2ENR_AFIOEN_Pos,
    // Reserved
    RCC_APB2ENR_IOPAEN_Pos = 2,
    RCC_APB2ENR_IOPBEN_Pos,
    RCC_APB2ENR_IOPCEN_Pos,
    RCC_APB2ENR_IOPDEN_Pos,
    RCC_APB2ENR_IOPEEN_Pos,
    RCC_APB2ENR_IOPFEN_Pos,
    RCC_APB2ENR_IOPGEN_Pos,
    RCC_APB2ENR_ADC1EN_Pos,
    RCC_APB2ENR_ADC2EN_Pos,
    RCC_APB2ENR_TIM1EN_Pos,
    RCC_APB2ENR_SPI1En_Pos,
    RCC_APB2ENR_TIM8EN_Pos,
    RCC_APB2ENR_USART1EN_Pos,
    RCC_APB2ENR_ADC3EN_Pos,
    // Reserved
    RCC_APB2ENR_TIM9EN_Pos = 19,
    RCC_APB2ENR_TIM10EN_Pos,
    RCC_APB2ENR_TIM11EN_Pos,
};

#define RCC_APB2ENR_AFIOEN (1 << RCC_APB2ENR_AFIOEN_Pos)
#define RCC_APB2ENR_IOPAEN (1 << RCC_APB2ENR_IOPAEN_Pos)
#define RCC_APB2ENR_IOPBEN (1 << RCC_APB2ENR_IOPBEN_Pos)
#define RCC_APB2ENR_IOPCEN (1 << RCC_APB2ENR_IOPCEN_Pos)
#define RCC_APB2ENR_IOPDEN (1 << RCC_APB2ENR_IOPDEN_Pos)
#define RCC_APB2ENR_IOPEEN (1 << RCC_APB2ENR_IOPEEN_Pos)
#define RCC_APB2ENR_IOPFEN (1 << RCC_APB2ENR_IOPFEN_Pos)
#define RCC_APB2ENR_IOPGEN (1 << RCC_APB2ENR_IOPGEN_Pos)
#define RCC_APB2ENR_ADC1EN (1 << RCC_APB2ENR_ADC1EN_Pos)
#define RCC_APB2ENR_ADC2EN (1 << RCC_APB2ENR_ADC2EN_Pos)
#define RCC_APB2ENR_TIM1EN (1 << RCC_APB2ENR_TIM1EN_Pos)
#define RCC_APB2ENR_SPI1En (1 << RCC_APB2ENR_SPI1En_Pos)
#define RCC_APB2ENR_TIM8EN (1 << RCC_APB2ENR_TIM8EN_Pos)
#define RCC_APB2ENR_USART1EN (1 << RCC_APB2ENR_USART1EN_Pos)
#define RCC_APB2ENR_ADC3EN (1 << RCC_APB2ENR_ADC3EN_Pos)
#define RCC_APB2ENR_TIM9EN (1 << RCC_APB2ENR_TIM9EN_Pos)
#define RCC_APB2ENR_TIM10EN (1 << RCC_APB2ENR_TIM10EN_Pos)
#define RCC_APB2ENR_TIM11EN (1 << RCC_APB2ENR_TIM11EN_Pos)

#define RCC_Base 0x40021000

// BASE_2_PTR(struct RccDef, RCC, RCC_Base)
#define RCC ((volatile struct RccDef*) RCC_Base)

/* ==============>  GPIO  <=============== */
struct GpioDef {
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t BRR;
    __IO uint32_t LCKR;
};

enum {
    GPIO_CNF_INPUT_ANALOG,
    GPIO_CNF_INPUT_FLOATING,
    GPIO_CNF_INPUT_PULL_UP_PULL_DOWN,
};

enum {
    GPIO_CNF_OUTPUT_PUSH_PULL,
    GPIO_CNF_OUTPUT_OPEN_DRAIN,
    GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE,
    GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE
};

enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT_10MHZ,
    GPIO_MODE_OUTPUT_2MHZ,
    GPIO_MODE_OUTPUT_50MHZ,
};

// #define GPIO_PORT_CFG_M(cnf, mode, port) (((cnf << 2) | mode) << (port << 2))

#define GPIOA_Base 0x40010800
#define GPIOB_Base 0x40010C00
#define GPIOC_Base 0x40011000

#define GPIOA ((volatile struct GpioDef*) GPIOA_Base)
#define GPIOB ((volatile struct GpioDef*) GPIOB_Base)
#define GPIOC ((volatile struct GpioDef*) GPIOC_Base)

void gpio_port_cfg(
        volatile struct GpioDef* const gpio, const uint8_t port, const uint8_t cnf, const uint8_t mode
);
