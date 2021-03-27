/**
 * @file mx_led_display_cfg.c
 * @author Mohamed Hassanin
 * @brief Multi-segment LED displays pattern for time-triggered embedded systems.
 * @version 0.1
 * @date 2021-03-24
 */

/******************************************************************************
* Includes
******************************************************************************/
#include "mx_led_display_cfg.h"
/******************************************************************************
 * Variable definitions
 ******************************************************************************/
static MxLedDisplayConfig_t MxLedDisplayConfig[MX_LED_DISPLAY_MAX] = {
  { 
    .LedDisplay = MX_LED_DISPLAY_0,
    .DataChannels = 
    {
      PORTA_0,
      PORTA_1,
      PORTA_2,
      PORTA_3,
      PORTA_4,
      PORTA_5,
      PORTA_6
    }, 
    
    .EnableChannelsSize = 4,
    .EnableChannels =
    {
      PORTB_0,
      PORTB_1,
      PORTB_2,
      PORTB_3
    },

    .Type = MX_LED_DISPLAY_TYPE_ANODE
  }
};
/******************************************************************************
 * Function definitions
 ******************************************************************************/

extern const MxLedDisplayConfig_t* 
MxLedDisplay_GetConfig(void)
{
  return MxLedDisplayConfig;
}

/*****************************End of File ************************************/
