/* Alpha virtual IO addresses */
#include "stdint.h"

#define IO_BASE 0x20000000

#define GPIO_BASE (IO_BASE + 0x200000)
#define GPIO_FSEL GPIO_BASE
#define GPIO_FSEL_IN 0b000
#define GPIO_FSEL_OUT 0b001
#define GPIO_SET0 (GPIO_BASE + 0x1c)
#define GPIO_CLR0 (GPIO_BASE + 0x28)
#define GPIO_LEV0 (GPIO_BASE + 0x34)
#define GPIO_EDS0 (GPIO_BASE + 0x40)
#define GPIO_REN0 (GPIO_BASE + 0x4c)
#define GPIO_AREN0 (GPIO_BASE + 0x7c)

#define SYS_TIMER_BASE (IO_BASE + 0x3000)
#define SYS_TIMER_CLO (SYS_TIMER_BASE + 0x4)

#define GPIO_MASK_13_0 0b11111111111111
#define GPIO_MASK_16 (1 << 16)
#define GPIO_MASK_23 (1 << 23)
#define GPIO_MASK_24 (1 << 24)
#define GPIO_MASK_25 (1 << 25)
#define GPIO_MASK_26 (1 << 26)