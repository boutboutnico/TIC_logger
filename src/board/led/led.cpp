///
/// \file
///	\brief
///	\date	22 mars 2015
/// \author	nb_work
///
//

#include "led.hpp"
using namespace board::led;

/// === Includes	================================================================================
/// === Static Instantiation	====================================================================

BlinkLed board::led::LED_Green(3, 12);
BlinkLed board::led::LED_Orange(3, 13);
BlinkLed board::led::LED_Red(3, 14);
BlinkLed board::led::LED_Blue(3, 15);

/// === Public Definitions	========================================================================

BlinkLed::BlinkLed(port_type _port, pin_type _pin)
		: pin_(_pin), port_(_port)
{
	initialize();
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================

void BlinkLed::initialize()
{
	/// Enable GPIO Peripheral clock
	RCC->AHB1ENR |= BLINK_RCC_MASKx(port_);

	GPIO_InitTypeDef GPIO_InitStructure;

	/// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin = BLINK_PIN_MASK(pin_);
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(BLINK_GPIOx(port_), &GPIO_InitStructure);

	/// Start with led turned off
	off();
}

/// === END OF FILE	================================================================================
