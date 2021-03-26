/**
 * @file TestPcLink.c
 * @author Mohamed Hassanin
 * @brief The test file for the Multiplexed LED Display Module.
 * @version 0.1
 * @date 2021-03-24
 */
/*****************************************************************************
* Includes
******************************************************************************/
/// @cond NODOC
/* Include Unity */
#include <stdio.h>
#include "unity.h"
/// @endcond

#include "mx_led_display.h" /**< module under the test */
#include "mx_led_display_cfg.h" /**< module under the test */
#include "Mock_dio.h"
/**********************************************************************
* Variable Definitions
**********************************************************************/
static const MxLedDisplayConfig_t * gConfig;

/**********************************************************************/

void 
setUp(void)
{
  gConfig = MxLedDisplay_GetConfig();
  MxLedDisplay_Init(gConfig);
}

void 
tearDown(void)
{
}

/*****************************************************************************
* Test cases
******************************************************************************/
void 
test_UpdateFunctionMultiplexLedsCorrectly(void)
{
  //given the intial state of enable channels indices is 0

  //Verify that Dio_ChannelWrite is called the correct number of times
  for(uint8_t Display = 0; Display < MX_LED_DISPLAY_MAX; Display++)
    {
      //Disable a channel
      Dio_ChannelWrite_Expect(gConfig[Display].EnableChannels[0], DIO_STATE_LOW);
      //enable the next channel
      Dio_ChannelWrite_Expect(gConfig[Display].EnableChannels[1], DIO_STATE_HIGH);
    }

  //Act
  MxLedDisplay_Update();
}
/*****************************************************************************
* Helper functions
******************************************************************************/

/*****************************End of File ************************************/

