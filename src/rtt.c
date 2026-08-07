#include "rtt.h"
#include <stdarg.h>
#include <stdint.h>

// ======> Allocate Segger blocks automatically in SRAM (.bss section) <======
volatile struct SeggerRttControlBlock _SEGGER_RTT;

#if RTT_MAX_UP_CHANNELS != 0
volatile uint8_t g_seggerRttUpRingBufferData[RTT_MAX_UP_CHANNELS][RTT_UP_RING_BUFFER_SIZE];
#endif

#if RTT_MAX_DOWN_CHANNELS != 0
volatile uint8_t g_seggerRttDownRingBufferData[RTT_MAX_DOWN_CHANNELS][RTT_DOWN_RING_BUFFER_SIZE];
#endif
// ===============


static inline void rprint_str(uint32_t buff_idx, const char* str) {
#if RTT_MAX_UP_CHANNELS != 0
    while (*str) {
        rputc(buff_idx, *(str++));
    }
#endif
}


static inline void rprint_u32(uint32_t buff_idx, uint32_t n) {
#if RTT_MAX_UP_CHANNELS != 0
    if (n == 0) {
        rputc(buff_idx, '0');
        return;
    }

    char buf[10] = {0};
    char* buf_ptr = buf;

    while (n) {
        *(buf_ptr++) = '0' + n % 10;
        n = n / 10;
    }

    while (buf_ptr != buf) {
        rputc(buff_idx, *(--buf_ptr));
    }
#endif
}


static inline void rprint_i32(uint32_t buff_idx, int32_t n) {
#if RTT_MAX_UP_CHANNELS != 0
    uint32_t new_n;
    if (n < 0) {
        rputc(buff_idx, '-');
        new_n = (uint32_t) (~n) + 1;
    } else {
        new_n = (uint32_t) n;
    }

    rprint_u32(buff_idx, new_n);
#endif
}


static inline void rprint_bool(uint32_t buff_idx, uint8_t n) {
#if RTT_MAX_UP_CHANNELS != 0
    if (n) {
        rprint_str(buff_idx, "true");
    } else {
        rprint_str(buff_idx, "false");
    }
#endif
}


void rputc(uint32_t buff_idx, const char ch) {
#if RTT_MAX_UP_CHANNELS != 0
    volatile struct SeggerRttRingBuffer* rbuf = &_SEGGER_RTT.up_channels[buff_idx];

    const uint32_t wr = rbuf->write;
    uint32_t next_write = wr + 1;
    if (next_write == RTT_UP_RING_BUFFER_SIZE) {
        next_write = 0;
    }

    /*
        rputc supports only RTT_BUFFER_MODE_NO_BLOCK_TRIM (default) and RTT_BUFFER_MODE_BLOCK_IF_FULL
        It is the function limitation: NO_BLOCK_TRIM and NO_BLOCK_SKIP behave identically for one char
    */
    if (rbuf->flags == RTT_BUFFER_MODE_BLOCK_IF_FULL) {
        // Wait until buffer is not full
        while (next_write == rbuf->read) {
        }
    } else { // NO_BLOCK_TRIM behavior by default
        // Buffer is full, skip printing
        if (next_write == rbuf->read) {
            return;
        }
    }

    rbuf->buffer[wr] = ch;
    rbuf->write = next_write;
#endif
}


enum RPrintfFsm {
    RPRINTF_FSM_PRINT,
    RPRINTF_FSM_ARG,
};

void rprintf(uint32_t buff_idx, const char* fmt, ...) {
#if RTT_MAX_UP_CHANNELS != 0
    // Only support %s, %d, %u, %b, %%
    va_list args;
    va_start(args, fmt);

    enum RPrintfFsm state = RPRINTF_FSM_PRINT;
    while (*fmt) {
        char ch = *(fmt++);

        if (state == RPRINTF_FSM_PRINT) {
            if (ch == '%') {
                state = RPRINTF_FSM_ARG;
            } else {
                rputc(buff_idx, ch);
            }

        } else if (state == RPRINTF_FSM_ARG) {
            switch (ch) {
                case '%':
                    rputc(buff_idx, '%');
                    break;
                case 's':
                    rprint_str(buff_idx, va_arg(args, const char*));
                    break;
                case 'd':
                    rprint_i32(buff_idx, va_arg(args, int32_t));
                    break;
                case 'u':
                    rprint_u32(buff_idx, va_arg(args, uint32_t));
                    break;
                case 'b':
                    rprint_bool(buff_idx, (uint8_t) va_arg(args, uint32_t));
                    break;
                default:
                    rputc(buff_idx, '%');
                    rputc(buff_idx, ch);
                    break;
            }

            state = RPRINTF_FSM_PRINT;
        }
    }

    if (state == RPRINTF_FSM_ARG) {
        rputc(buff_idx, '%');
    }

    va_end(args);
#endif
}
