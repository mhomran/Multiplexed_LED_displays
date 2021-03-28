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
 * Function prototypes
 ******************************************************************************/
static void
MxLedDisplay_ChannelWrite(
  MxLedDisplayType_t Type,
  DioChannel_t Channel,
  DioState_t State);
/******************************************************************************
 * Module variables definitions
 ******************************************************************************/
/**
 * @brief This variable is used to track which channel to enable next.
 */ 
static uint8_t gPrevEnChannel[MX_LED_DISPLAY_MAX];

/**
 * @brief This variable is used to track the data of the seven segments.
 */
static uint8_t gData[MX_LED_DISPLAY_MAX][MX_LED_DISPLAY_MAX_SEG];

/**
 * @brief The configuration pointer.
 */
static const MxLedDisplayConfig_t* gConfig;

static const uint8_t SevSegTable[] = {
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
/******************************************************************************
* Function : MxLedDisplay_Init()
*//**
* \b Description: Initialization function for the Multiplexed Led Display
* module<br/>
* \b PRE-CONDITION: Configuration table is populated<br/>
* @param Config a pointer to the configuration table of the displays.
* @return void 
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
      gPrevEnChannel[Display] = 0;

      for(SevSeg = 0; SevSeg < gConfig[Display].EnableChannelsSize; SevSeg++)
        {
          //make sure all enable signals are low
          MxLedDisplay_ChannelWrite(gConfig[Display].Type,
          gConfig[Display].EnableChannels[SevSeg],
          DIO_STATE_LOW);
        }
    }
}

/******************************************************************************
* Function : MxLedDisplay_Update()
*//**
* \b Description: Update function to multiplex the seven segment units of the 
* displays<br/>
* \b PRE-CONDITION: MxLedDisplay_Init is called correctly<br/>
* @return void 
******************************************************************************/
extern void 
MxLedDisplay_Update(void)
{
  uint8_t Display;
  uint8_t SevSegOutput;
  uint8_t SevSegLed;

  for(Display = 0; Display < MX_LED_DISPLAY_MAX; Display++)
    {
      //Disable the last channel
      MxLedDisplay_ChannelWrite(gConfig[Display].Type,
       gConfig[Display].EnableChannels[gPrevEnChannel[Display]],
        DIO_STATE_LOW);

      gPrevEnChannel[Display] = (gPrevEnChannel[Display] + 1) %
      gConfig[Display].EnableChannelsSize;

      //Enable the next channel
      MxLedDisplay_ChannelWrite(gConfig[Display].Type,
       gConfig[Display].EnableChannels[gPrevEnChannel[Display]],
        DIO_STATE_HIGH);

      //Change the data
      SevSegOutput = SevSegTable[gData[Display][gPrevEnChannel[Display]]];

      for(SevSegLed = 0; SevSegLed < 7; SevSegLed++)
        {
          if(SevSegOutput & (1 << SevSegLed))
            {
              MxLedDisplay_ChannelWrite(gConfig[Display].Type,
          gConfig[Display].DataChannels[SevSegLed], DIO_STATE_LOW);
            }
          else
            {
              MxLedDisplay_ChannelWrite(gConfig[Display].Type,
          gConfig[Display].DataChannels[SevSegLed], DIO_STATE_HIGH);
            }
        }
    }
}

/******************************************************************************
* Function : MxLedDisplay_ChannelWrite()
*//**
* \b Description: Utility function used to right a channel according to its 
* display type. For Cathode diplays the state is inverted.<br/>
* \b PRE-CONDITION: MxLedDisplay_Init is called correctly<br/>
* @param Type the type of the display.
* @param Channel the channel to write.
* @param State the state of the channel.
* @return void 
******************************************************************************/
static void
MxLedDisplay_ChannelWrite(
  MxLedDisplayType_t Type,
  DioChannel_t Channel,
  DioState_t State)
{
  if(!(Type < MX_LED_DISPLAY_TYPE_MAX &&
  Channel < DIO_CHANNEL_MAX &&
  State < DIO_STATE_MAX))
    {
      //TODO: handle this error
      return;
    }
  if(Type == MX_LED_DISPLAY_TYPE_ANODE)
    {
      if(State == DIO_STATE_HIGH)
        {
          Dio_ChannelWrite(Channel, DIO_STATE_HIGH);
        }
        else
        {
          Dio_ChannelWrite(Channel, DIO_STATE_LOW);
        }
    }
  else
    {
      if(State == DIO_STATE_HIGH)
      	{
          Dio_ChannelWrite(Channel, DIO_STATE_LOW);
      	}
      else
      	{
          Dio_ChannelWrite(Channel, DIO_STATE_HIGH);
      	}
    }
}

/******************************************************************************
* Function : MxLedDisplay_SetData()
*//**
* \b Description: This is a function used to change the content of a display's
* seven segment unit.<br/>
* \b PRE-CONDITION: MxLedDisplay_Init is called correctly<br/>
* @param Display the display ID.
* @param SevSegNum the seven segment index starting from the left (0).
* @param Data the data to show on the seven segment.
* @return void 
******************************************************************************/
extern void 
MxLedDisplay_SetData(MxLedDisplay_t Display, uint8_t SevSegNum, uint8_t Data)
{
  if(!(
      Display < MX_LED_DISPLAY_MAX &&
      SevSegNum >= 0 &&
      SevSegNum < gConfig[Display].EnableChannelsSize &&
      Data <= 9
      ))
    {
      //TODO: handle this error
      return;
    }

  gData[Display][SevSegNum] = Data;
}
/*****************************End of File ************************************/
