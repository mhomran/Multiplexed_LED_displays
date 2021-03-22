/**
 * @file mx_led_display.h
 * @author Mohamed Hassanin
 * @brief Multi-segment LED displays pattern for time-triggered embedded systems.
 * @version 0.1
 * @date 2021-03-22
 */
#ifndef MX_LED_DISPLAY_CFG_H
#define MX_LED_DISPLAY_CFG_H
/**********************************************************************
* Includes
**********************************************************************/
#include "dio.h"
/**********************************************************************
* Typedefs
**********************************************************************/
/**
* Defines an enumerated list of all the pc links on the system
*/
typedef enum
{
  /* TODO: Populate this list based on your application */
  MX_LED_DISPLAY_0,
  MX_LED_DISPLAY_MAX
}MxLedDisplay_t;

typedef struct
{
  MxLedDisplay_t PcLink; /**< the mux led display id */
  DioChannel_t DataChannels[7]; /**< the number of the data ports
   for the data of seven segment */
  DioChannel_t* EnableChannels; /**< channels used for enable seven segments */
  uint8_t EnableChannelsSize; /**< the number of the enable channels */
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
