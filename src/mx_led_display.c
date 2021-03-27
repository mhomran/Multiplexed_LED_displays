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
 * definitions
 ******************************************************************************/
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

static uint8_t SevSegTable[] = {
  0x3F, //0
  0x06, //1
  0x5B, //2
  0x4F, //3
  0x66, //4
  0x6D, //5
  0x7D, //6
  0x07, //7
  0x7F, //8
  0x6F, //9
};
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
      //For Anode 7-segment
      //TODO: implement for cathode

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

extern void 
MxLedDisplay_SetData(MxLedDisplay_t Display, uint8_t SevSegNum, uint8_t Data)
{

  if(!(
      Display < MX_LED_DISPLAY_MAX &&
      SevSegNum > 0 && 
      SevSegNum <= gConfig[Display].EnableChannelsSize &&
      Data <= 9
      ))
    {
      //TODO: handle this error
      return;
    }

  uint8_t SevSegOutput;
  uint8_t SevSegLed;
  DioChannel_t SevSegLedChannel;
  
  SevSegOutput = SevSegTable[Data];
  for(SevSegLed = 0; SevSegLed < 7; SevSegLed++)
    {
      //For Anode 7-segment
      //TODO: implement for cathode

      SevSegLedChannel = gConfig[Display].DataChannels[SevSegLed];
      if(SevSegOutput & (1 << SevSegLed))
        {
          Dio_ChannelWrite(SevSegLedChannel, DIO_STATE_LOW);
        }
      else
        {
          Dio_ChannelWrite(SevSegLedChannel, DIO_STATE_HIGH);
        }
    }
}
/*****************************End of File ************************************/
