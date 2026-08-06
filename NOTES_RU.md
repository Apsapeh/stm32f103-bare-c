# 0. Introduction

Некоторые заметки по программированию BluePill (STM32F103C8T6) без внешних библиотек, только чистый C99 + GCC + Make.
Каждая глава имеет свой тэг в Git.

# I. Bare-metal blink

Что понадобится:

- BluePill - сама плата
- GCC (arm-none-eabi-gcc) - форк GCC от ARM для компиляции нашей прошивки
- GNU Binary Utils (arm-none-eabi-binutils) - а конкретно, objcopy (arm-none-eabi-objcopy)
- Make
- [RМ0008](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf) - Основная документация по STM32F1. Далее RM.
- [PM0056](https://www.st.com/resource/en/programming_manual/cd00228163-stm32f10xxx-20xxx-21xxx-l1xxxx-cortex-m3-programming-manual-stmicroelectronics.pdf) - документация по программированию под ARM Cortex-M3. Далее PM.

Чтоб поморгать светодиодом, нужно выполнить следующие шаги:

- [Разметить память](NOTES_RU#I.1%20%D0%A0%D0%B0%D0%B7%D0%BC%D0%B5%D1%82%D0%BA%D0%B0%20%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8)
- [Установить начало стека и таблицу векторов прерываний](NOTES_RU#I.2%20%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%B0%D0%B2%D0%BB%D0%B8%D0%B2%D0%BA%D0%B0%20%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D0%B0%20%D1%81%D1%82%D0%B5%D0%BA%D0%B0%20%D0%B8%20%D1%82%D0%B0%D0%B1%D0%BB%D0%B8%D1%86%D1%8B%20%D0%B2%D0%B5%D0%BA%D1%82%D0%BE%D1%80%D0%BE%D0%B2%20%D0%BF%D1%80%D0%B5%D1%80%D1%8B%D0%B2%D0%B0%D0%BD%D0%B8%D0%B9)
- [Инициализировать глобальные переменные](NOTES_RU#I.3%20%D0%98%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F%20%D0%BF%D0%B0%D0%BC%D1%8F%D1%82%D0%B8)
- [Включить тактирование GPIOC, настроить пин PC13 на Output push-pull](NOTES_RU##I.4%20%D0%92%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D0%B5%20%D1%82%D0%B0%D0%BA%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F%20GPIOC,%20%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0%20%D0%BF%D0%B8%D0%BD%D0%B0%20%D0%BD%D0%B0%20push-pull,%20%D0%BC%D0%BE%D1%80%D0%B3%D0%B0%D0%BD%D0%B8%D0%B5)

## I.1 Разметка памяти

```ld
/* STM32 не будет запускаться с этой точки. Больше нужно для отладки */
ENTRY(reset_hdl)

/* По RM */
MEMORY
{
  /* Начало секции с кодом. При BOOT0 == 0, память из 0x08000000 отражается на 0x00000000 */
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 128K
  SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  /* Сначала идёт секция с указателем вершины стека и таблицей векторов прерываний */
  /* Они должны лежать на 0x00000000 и 0x00000004.., соответственно */
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } >FLASH

  /* Секция с кодом */
  .text :
  {
    . = ALIGN(4);
		
    *(.text*)
    *(.rodata*)
		
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* Секция статических данных. Таблиц виртуальных адерсов соотеветствия SRAM-FLASH */
  /* Т.е. тут хранятся адресы SRAM памяти, в которые загружаем данные из FLASH */
  /* mem[.data[i]] = mem[.idata[i]] */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
		
    *(.data)

    . = ALIGN(4);
    _edata = .;
  } >SRAM AT> FLASH
 
  /* Самие статические данные */
  _sidata = LOADADDR(.data);

  /* Секция, где всё должно быть занулено */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
		
    *(.bss)
		
    . = ALIGN(4);
    _ebss = .;
  } >SRAM
}
```

## I.2 Устанавливка начала стека и таблицы векторов прерываний

Не знаю, что тут комментировать.
Открываем главу *10.1.2 в RM*, а конкретно *Table 63. Vector table for other STM32F10xxx devices*, и переписываем.

Cамым первым элементом должна идти вершина указателя. Ставим в самый конец SRAM. Т.к. стек растёт вниз по адресам (0x5, 0x4, 0x3, ...).

Атрибут `__attribute__((weak, alias("default_hdl")))` слабо связывет определение с реальной функцией. Если в где-то другом месте программы определить реальный обрабочик прерывания, то компилятор подтянет его.

```c
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
        /* Ну и так далее всю таблицу */
        /* Подробнее в src/startup.c */
};

void default_hdl(void) {
  while (1) {
  }
}

void reset_hdl(void) {
  // Пока тут пусто
}
```

## I.3 Инициализация памяти

Почти весь минимальный код для запуска был написан, осталось инициализировать глобальные переменные.

```c
int main(void);
// Наши секции, определённые в скрипте линковки
extern uint32_t _etext, _sdata, _edata, _sidata, _sbss, _ebss;

void reset_hdl(void) {
  // Copy static data from FLASH to SRAM
  // Копируем инициализационные данные из FLASH в SRAM
  // _sdata - адрес КУДА копируем (SRAM 0x20000000..)
  // _sidata - адрес ОТКУДА копиурем (FLASH 0x08000000..)
  // Т.е. у нас есть глобальная переменная 'int a = 10'
  // '10' хранится во FLASH. Во время запуска STM32,
  //   мы присваем переменной 'a' значение '10', иначе там будет мусор
   
  uint32_t *data_ptr = &_sidata;
  uint32_t *sram_ptr = &_sdata;
  const uint32_t *sram_end_ptr = &_edata;

  while (sram_ptr != sram_end_ptr) {
    *(sram_ptr++) = *(data_ptr++);
  }

  // Заполняем всю память по .bss адресам нулями
  uint32_t *bss_ptr = &_sbss;
  const uint32_t *bss_end_ptr = &_ebss;

  while (bss_ptr != bss_end_ptr) {
    *(bss_ptr++) = 0;
  }

  main();
}
```

Также вызываем `main()`.

## I.4 Включение тактирования GPIOC, настройка пина на push-pull, моргание

По умолчанию, практически вся переферия МК выключена для уменьшения потребления электроэнергии.

Мне тут лень прям подробно расписывать. В RM находим нужную `RCC` шины для включеия `GPIOC`, у нас это `APB2ENR`, находим нужный бит, это `IOPCEN`. Устанавливаем его. В соответствие с *Errata*, делаем двойное чтение, чтоб переферия была точно включена.

Далее открываем *9.2.2 в RM*, настраиваем `MODE` и `CNF` для нужного порта. Есть два регистра `CRL` и `CRH`. Через `CRL` управляются пины с 0 по 7, через `CRH` с 8 по 15. Встроенная лампочка BluePill висит на пине PC13, т.е. это 5-ый CRH пин.

Настраиваем `MODE` на *Output mode, max speed 2 MHZ*, т.е. нужно установить `MODE` биты в `0b10`. Далее настраиваем `CNF` в *General purpose output push-pull*, биты `0b00`.

Смотрим по таблице, `MODE13` это биты 20 и 21, `CNF13` - 22 и 23. Устанавливаем их.

Далее в цикле моргаем лампочкой, установка значения в `LOW` или `HIGH` идёт через регистры `BRR` и `BSRR` (можно через `ODR`, но это менее эффективно, т.к. сначала нужно прочитать значение).

```c
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

// RM 9.2.2
const size_t OUTPUT_PUSH_PULL = 0b00;
const size_t OUTPUT_MODE_2MHZ = 0b10;

const size_t LED = 13; // См. распиновку BluePill
const size_t LED_CRH = 5; // 13 - 8 = 5
const size_t LED_DELAY = 1000000; // Просто случайное число задержки

int main(void) {
  // Включаем GPIOC на шине APB2ER
  *RCC_APB2ENR_PTR |= 1 << RCC_APB2ENR_IOPCEN_OFF;

  volatile uint32_t dummy;
  dummy = *RCC_APB2ENR_PTR;
  dummy = *RCC_APB2ENR_PTR;

  // Устанавливаем MODE и CNF для PC13 (CRH 5)
  const size_t mode_setup =
      (OUTPUT_PUSH_PULL << GPIO_CNF_OFF) | (OUTPUT_MODE_2MHZ << GPIO_MODE_OFF);
  *GPIOC_CRH_PTR |= mode_setup << (4 * LED_CRH);

  while (1) {
    // Включаем лампочку, для этого устанавливаем PC13 в LOW (так контринтуитивно работает лампочка на BluePill)
    *GPIOC_BRR_PTR = 1 << LED;

    // Спим некоторое время, volatile нужен, чтоб компилятор не убрал этот цикл
    for (volatile size_t i = 0; i < LED_DELAY; i++)
      ;

    // Выключаем лампочку, PC13 устанавливаем в HIGH
    *GPIOC_BSRR_PTR = 1 << LED;

    // Опять спим
    for (volatile size_t i = 0; i < LED_DELAY; i++)
      ;
  }

  return 0;
}
```

# II. Custom CMSIS and clocks setup

- На этом шаге избавимся от ручного определения каждого регистра через `#define`.
- Настроим *SYSCLK* на 48MHZ (для USB в будущем, но можно и 72MHz использовать).
- И сделаем моргание лампочкой через одну секунду (полный период две секунды) с помощью SysTick (встроенный таймер в Cortex-M3).

## II.1 Write custom CMSIS

Использовать `#define` для каждого регистра очень неудобно и подвержено к большому количеству ошибок. В качестве альтернативы можно регистры определять через *struct*, что уменьшит количество ошибок и сделает программирование более комфортным.
Реализация тривиальна, открываем *RM '* register map'\* и просто всё переписываем. К каждому полю структуры нужно добавить модификатор `volatile`, чтобы компилятор не оптимизировал обращения.
Дополнительно написана небольшая утилитка на Python в *tool/epos2msk.py*. Просто для удобной генерации из *enum* определений.
Файл большой, тут вставлять не буду. Всё лежит в *src/registers.h*

## II.2 Setup frequency to 48Mhz

Сначала нужно настроить `FLASH->ACR` на пропуск одного такта, т.к. максимальная скорость *FLASH* - 24MHz. Если этого не сделать, то будут проблемы с работой МК и его прошивкой (потребудется сброс через `$ st-flash erase`).

Далее нужно включить *HSE* и дождаться пока он включится.

После, настраиваем *PLL*. Устанавливаем *HSE* как источник для *PLL* и ставим множитель *x6* для достижения 48MHz.

Включаем *PLL* и дожидаемся пока он включится.

Когда *PLL* включился, переключаем *SYSCLK* с *HSI* на *PLL*

```c
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
```

Всё, BluePill работает на частоте 48Mhz.
По хорошему, нужно сделать обработку случая, если *HSE* или *PLL* не включается, иначе программа зависнет в вечном цикле. К примеру можно просто добавить счётчик на несколько итераций, и если счётчик обнулился, то делать откат на обычный HSI и зажигать лампочку, например. Но это по хорошему.

## II.3 SysTick setup and blink update

Использовать `for(...){}` для имитации задержки, конечно, хорошо, но очень неточно. Чтоб добиться моргания лампочкой раз в секунду (полный период две секунды), настроим *SysTick*, который является стандартной периферией для процессоров *Cortex-M3*. Т.к. это периферия *Cortex-M3*, то документация лежит в *PM*.

Сначала настроим сам SysTick.
Мы должны задать значение `SysTick->LOAD` (24 бита), это значение (на самом деле `SysTick->VAL`) каждый тик будет декрементироваться, когда оно достигнет `0`, то будет вызвано прерывание `systick_hdl`. Таймер автоматически перезапускается

```c
static inline void setup_systick(void) {
    SysTick->LOAD = LED_DELAY - 1;
    SysTick->VAL = 0;

    // Включаем сам SysTick и испускание прерывания, когда VAL достигает 0
    SysTick->CTRL |= SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT;
}
```

Теперь объявим само прерывание, т.к. в *src/startup.c* оно объявляно как *weak*, то нам нужно просто создать эту функцию.
На каждое прерывания через XOR переключаем светодиод.

```c
void systick_hdl(void) {
    GPIOC->ODR ^= 1 << LED;
}
```
