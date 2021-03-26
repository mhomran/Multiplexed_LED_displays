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

extern void 
MxLedDisplay_Update(void)
{
  uint8_t Display;
  uint8_t SevSeg;
  uint8_t NextChannel;
  uint8_t PrevChannel;

  for(Display = 0; Display < MX_LED_DISPLAY_MAX; Display++)
    {
      //Disable the last channel
      PrevChannel = gEnChannelsOrder[Display][SevSeg];
      Dio_ChannelWrite(gConfig[Display].EnableChannels[PrevChannel], DIO_STATE_LOW);
      
      NextChannel = PrevChannel + 1;
      NextChannel = NextChannel % gConfig[Display].EnableChannelsSize;
      gEnChannelsOrder[Display][SevSeg] = NextChannel;

      //Enable the next channel
      Dio_ChannelWrite(gConfig[Display].EnableChannels[NextChannel], DIO_STATE_HIGH);
    }
}
/*****************************End of File ************************************/
