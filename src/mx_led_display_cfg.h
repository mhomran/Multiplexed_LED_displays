/**
 * @file mx_led_display.h
 * @author Mohamed Hassanin
 * @brief Multi-segment LED displays pattern for time-triggered embedded systems.
 * @version 0.1
 * @date 2021-03-22
 */
#ifndef MX_LED_DISPLAY_CFG_H
#define MX_LED_DISPLAY_CFG_H
/******************************************************************************
* Includes
******************************************************************************/
#include "dio.h"
/*****************************************************************************
* Definitions
******************************************************************************/
//TODO: Edit this according to the application
/** defines the maximum number of seven 
 * segments between all MX LED displays (e.g. if there's a display with 2 seven
 * segments and another with 3, then write 3 
 */
#define MX_LED_DISPLAY_MAX_SEG 4
/****************************************************************************
* Typedefs
****************************************************************************/
/**
* Defines an enumerated list of all the pc links on the system
*/
typedef enum
{
  /* TODO: Populate this list based on your application */
  MX_LED_DISPLAY_0,
  MX_LED_DISPLAY_MAX
}MxLedDisplay_t;

typedef enum
{
  MX_LED_DISPLAY_TYPE_ANODE,
  MX_LED_DISPLAY_TYPE_CATHODE,
  MX_LED_DISPLAY_TYPE_MAX
}MxLedDisplayType_t;
typedef struct
{
  MxLedDisplay_t LedDisplay; /**< the mux led display id */
  DioChannel_t DataChannels[7]; /**< the pins of the data of seven segments */
  
  /** channels used to enable seven segments */
  DioChannel_t EnableChannels[MX_LED_DISPLAY_MAX_SEG];
  uint8_t EnableChannelsSize; /**< the number of the enable channels */

  MxLedDisplayType_t Type;
} MxLedDisplayConfig_t;

/******************************************************************************
 * Function prototypes
 ******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

extern const MxLedDisplayConfig_t* MxLedDisplay_GetConfig(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* end MX_LED_DISPLAY_CFG_H */
/*****************************End of File ************************************/
