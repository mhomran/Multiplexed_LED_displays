/**
 * @file mx_led_display.h
 * @author Mohamed Hassanin
 * @brief Multi-segment LED displays pattern for time-triggered embedded systems.
 * @version 0.1
 * @date 2021-03-22
 */
#ifndef MX_LED_DISPLAY_H
#define MX_LED_DISPLAY_H
/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include "mx_led_display_cfg.h"
/******************************************************************************
 * Function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

extern void MxLedDisplay(MxLedDisplayConfig_t * const Config);
extern void MxLedDisplay_Update(void);
extern void MxLedDisplay_SetData(MxLedDisplay_t Display, uint8_t SevSegNum, uint8_t Data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
