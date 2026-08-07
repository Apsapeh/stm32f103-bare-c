#include <stdint.h>

/*

MANY THANKS TO THIS REPO:
    https://github.com/probe-rs/rtt-target

*/

/* ======== RTT config ======== */
#define RTT_MAX_UP_CHANNELS 1
#define RTT_MAX_DOWN_CHANNELS 0
#define RTT_UP_RING_BUFFER_SIZE 64
#define RTT_DOWN_RING_BUFFER_SIZE 64
/* ============================ */

#define RTT_BUFFER_MODE_Msk 3

enum {
    /// Doesn't work with the 'rputc' function.
    RTT_BUFFER_MODE_NO_BLOCK_SKIP = 0,
    RTT_BUFFER_MODE_NO_BLOCK_TRIM = 1 << 0,
    RTT_BUFFER_MODE_BLOCK_IF_FULL = 1 << 1
};


struct SeggerRttRingBuffer {
    const char* name;
    volatile uint8_t* buffer;
    uint32_t size;
    volatile uint32_t write;
    volatile uint32_t read;
    uint32_t flags;
};


struct SeggerRttControlBlock {
    uint8_t id[16];
    uint32_t max_up_channels;
    uint32_t max_down_channels;

#if RTT_MAX_UP_CHANNELS != 0
    struct SeggerRttRingBuffer up_channels[RTT_MAX_UP_CHANNELS];
#endif

#if RTT_MAX_DOWN_CHANNELS != 0
    struct SeggerRttRingBuffer down_channels[RTT_MAX_DOWN_CHANNELS];
#endif
};


extern volatile struct SeggerRttControlBlock _SEGGER_RTT;

#if RTT_MAX_UP_CHANNELS != 0
extern volatile uint8_t g_seggerRttUpRingBufferData[RTT_MAX_UP_CHANNELS][RTT_UP_RING_BUFFER_SIZE];
#endif

#if RTT_MAX_DOWN_CHANNELS != 0
extern volatile uint8_t g_seggerRttDownRingBufferData[RTT_MAX_DOWN_CHANNELS][RTT_DOWN_RING_BUFFER_SIZE];
#endif


static inline void rtt_init(
        const char* const up_names[], uint32_t const up_modes[], const char* const down_names[],
        uint32_t const down_modes[]
) {
    // Trick to avoid storing "SEGGER RTT" in the binary file in normal form. Because real
    // SeggerRttControlBlock not stored in binary, it dynamically loaded at runtime via this function.
    const uint8_t id[16] = {0, 0, 0, 0, 0, 0, 'T', 'T', 'R', ' ', 'R', 'E', 'G', 'G', 'E', 'S'};

    for (uint8_t i = 0; i < 16; ++i) {
        _SEGGER_RTT.id[i] = id[15 - i];
    }

    _SEGGER_RTT.max_up_channels = RTT_MAX_UP_CHANNELS;
    _SEGGER_RTT.max_down_channels = RTT_MAX_DOWN_CHANNELS;

#if RTT_MAX_UP_CHANNELS != 0
    for (uint32_t i = 0; i < RTT_MAX_UP_CHANNELS; ++i) {
        volatile struct SeggerRttRingBuffer* rbuf = &_SEGGER_RTT.up_channels[i];
        rbuf->name = up_names[i];
        rbuf->buffer = &g_seggerRttUpRingBufferData[i][0];
        rbuf->size = RTT_UP_RING_BUFFER_SIZE;
        rbuf->write = 0;
        rbuf->read = 0;
        rbuf->flags = up_modes[i];
    }
#endif

#if RTT_MAX_DOWN_CHANNELS != 0
    for (uint32_t i = 0; i < RTT_MAX_DOWN_CHANNELS; ++i) {
        volatile struct SeggerRttRingBuffer* rbuf = &_SEGGER_RTT.down_channels[i];
        rbuf->name = down_names[i];
        rbuf->buffer = &g_seggerRttDownRingBufferData[i][0];
        rbuf->size = RTT_DOWN_RING_BUFFER_SIZE;
        rbuf->write = 0;
        rbuf->read = 0;
        rbuf->flags = down_modes[i];
    }
#endif
}

/**
    Print one char via RTT.

    @warning Supports only RTT_BUFFER_MODE_NO_BLOCK_TRIM (default) and RTT_BUFFER_MODE_BLOCK_IF_FULL. It
   is the function limitation: NO_BLOCK_TRIM and NO_BLOCK_SKIP behave identically for one char (one
   byte).

    @warning Keep in mind this can cause issues with unicode characters. Not a single byte character can
   be sliced between read-write cycles especially if your buffer is small
 */
void rputc(uint32_t buff_idx, const char ch);


/**
    Print formatted string via RTT.

    @warning Can cause some problems, because uses 'rputc' underhood. For more information look to
   'rputc' description
*/
void rprintf(uint32_t buff_idx, const char* fmt, ...);
