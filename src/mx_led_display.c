/**
 * @file mx_led_display.c
 * @author Mohamed Hassanin
 * @brief Multi-segment LED displays pattern for time-triggered embedded systems.
 * @version 0.1
 * @date 2021-03-22
 */
/*****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>
#include "mx_led_display.h"

/******************************************************************************
 * Module variables definitions
 ******************************************************************************/
/**
 * @brief This variable is used to track which channel to enable next.
 */ 
static uint8_t gEnChannelsOrder[MX_LED_DISPLAY_MAX][MX_LED_DISPLAY_MAX_SEG];

/**
 * @brief The configuration pointer.
 */
static const MxLedDisplayConfig_t* gConfig;
/******************************************************************************
 * Function definitions
 ******************************************************************************/
extern void 
MxLedDisplay_Init(const MxLedDisplayConfig_t * const Config)
{
  if(!(Config != 0x00))
    {
      //TODO: handle the error
      return;
    }

  gConfig = Config;

  uint8_t Display;
  uint8_t SevSeg;
  for(Display = 0; Display < MX_LED_DISPLAY_MAX; Display++)
    {
      for(SevSeg = 0; SevSeg < gConfig[Display].EnableChannelsSize; SevSeg++)
        {
          gEnChannelsOrder[Display][SevSeg] = 0;
        }
    }
}
/*****************************End of File ************************************/
