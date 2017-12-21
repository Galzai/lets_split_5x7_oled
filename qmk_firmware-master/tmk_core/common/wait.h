#ifndef WAIT_H
#define WAIT_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__AVR__)
#   include <util/delay.h>
#   define wait_ms(ms)  _delay_ms(ms)
#   define wait_us(us)  _delay_us(us)
#elif defined PROTOCOL_CHIBIOS
#   include "ch.h"
#   if defined(STM32F3xx_MCUCONF)
#       define wait_ms(ms) chSysPolledDelayX(MS2RTC(STM32_HCLK, (ms)))
#       define wait_us(us) chSysPolledDelayX(US2RTC(STM32_HCLK, (us)))
#   else
#       define wait_ms(ms) chThdSleepMilliseconds(ms)
#       define wait_us(us) chThdSleepMicroseconds(us)
#   endif
#elif defined(__arm__)
#   include "wait_api.h"
#else  // Unit tests
void wait_ms(uint32_t ms);
#define wait_us(us) wait_ms(us / 1000)
#endif

#ifdef __cplusplus
}
#endif

#endif
