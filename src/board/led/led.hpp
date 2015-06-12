///
/// \file
///	\brief
///	\date	22 mars 2015
/// \author	nb_work
///
//

#ifndef BOARD_LED_LED_HPP_
#define BOARD_LED_LED_HPP_

/// === Includes	================================================================================

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

/// === Namespaces	================================================================================

namespace board
{

namespace led
{

/// === Macro Definitions	========================================================================

#define BLINK_GPIOx(_N)			((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)		(1 << (_N))
#define BLINK_RCC_MASKx(_N)		(RCC_AHB1ENR_GPIOAEN << (_N))

/// === Forward Declarations	====================================================================

class BlinkLed;

/// === Extern Declarations	========================================================================

extern BlinkLed LED_Green;
extern BlinkLed LED_Orange;
extern BlinkLed LED_Red;
extern BlinkLed LED_Blue;

/// === Class Declarations	========================================================================

class BlinkLed
{
public:
	/// === Basic Types	============================================================================

	typedef uint8_t port_type;
	typedef uint8_t pin_type;

	/// === Public Declarations	====================================================================

	BlinkLed(port_type _port, pin_type _pin);

	inline void __attribute((always_inline)) toggle();

	inline void __attribute__((always_inline)) on();

	inline void __attribute__((always_inline)) off();

private:
	/// === Private Declarations	================================================================

	void initialize();

	/// === Private Attributes	====================================================================

	pin_type pin_;
	port_type port_;
};

/// === Inline Definitions	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

inline void __attribute((always_inline)) BlinkLed::toggle()
{
	HAL_GPIO_TogglePin(BLINK_GPIOx(port_), BLINK_PIN_MASK(pin_));
}

/// ------------------------------------------------------------------------------------------------

inline void __attribute__((always_inline)) BlinkLed::on()
{
	HAL_GPIO_WritePin(BLINK_GPIOx(port_), BLINK_PIN_MASK(pin_), GPIO_PinState::GPIO_PIN_SET);
}

/// ------------------------------------------------------------------------------------------------

inline void __attribute__((always_inline)) BlinkLed::off()
{
	HAL_GPIO_WritePin(BLINK_GPIOx(port_), BLINK_PIN_MASK(pin_), GPIO_PIN_RESET);

}

#pragma GCC diagnostic pop
/// ------------------------------------------------------------------------------------------------
}/// led
}    /// board
#endif /// BOARD_LED_LED_HPP_
/// === END OF FILE	================================================================================
