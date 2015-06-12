///
/// \file	pinout_mapping.hpp
///	\brief	
///	\date	15/04/2015
/// \author	nb_work
///
#ifndef HAL_MSP_PINOUT_MAPPING_HPP_
#define HAL_MSP_PINOUT_MAPPING_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "drivers/peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

#ifdef __cplusplus
extern "C"
{
#endif

/// === Public Declarations	========================================================================

/// --- UART2 - TIC	--------------------------------------------------------------------------------

const mcu::Peripherals_e TIC_UART_e = mcu::Peripherals_e::UART2;
extern const USART_TypeDef* TIC_UART;
extern const GPIO_TypeDef* TIC_UART_GPIO_PORT;
const uint16_t TIC_UART_RX_PIN = GPIO_PIN_3;
const uint8_t TIC_UART_PIN_AF = GPIO_AF7_USART2;

const IRQn_Type TIC_UART_IRQn = USART2_IRQn;
const uint8_t TIC_UART_IRQn_PRIO = 6;
const uint8_t TIC_UART_IRQn_SUBPRIO = 1;

inline void TIC_UART_CLK_ENABLE()
{
	__USART2_CLK_ENABLE();
}

inline void TIC_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

/// --- UART3 - Trace	----------------------------------------------------------------------------

const mcu::Peripherals_e Trace_UART_e = mcu::Peripherals_e::UART3;
extern const USART_TypeDef* Trace_UART;
extern const GPIO_TypeDef* Trace_UART_GPIO_PORT;
const uint16_t Trace_UART_TX_PIN = GPIO_PIN_8;
const uint8_t Trace_UART_PIN_AF = GPIO_AF7_USART3;

const IRQn_Type Trace_UART_IRQn = USART3_IRQn;
const uint8_t Trace_UART_IRQn_PRIO = 6;
const uint8_t Trace_UART_IRQn_SUBPRIO = 3;

inline void Trace_UART_CLK_ENABLE()
{
	__USART3_CLK_ENABLE();
}

inline void Trace_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
}

/// --- SPI2 - SD Card	----------------------------------------------------------------------------

extern const SPI_TypeDef* SDCARD_SPI;
extern const GPIO_TypeDef* SDCARD_SPI_GPIO_PORT;
const uint16_t SDCARD_SPI_CS_PIN = GPIO_PIN_12;
const uint16_t SDCARD_SPI_CLK_PIN = GPIO_PIN_13;
const uint16_t SDCARD_SPI_MISO_PIN = GPIO_PIN_14;
const uint16_t SDCARD_SPI_MOSI_PIN = GPIO_PIN_15;
const uint8_t SDCARD_SPI_PIN_AF = GPIO_AF5_SPI2;

const IRQn_Type SDCARD_SPI_IRQn = SPI2_IRQn;
const uint8_t SDCARD_SPI_IRQn_PRIO = 6;
const uint8_t SDCARD_SPI_IRQn_SUBPRIO = 2;

inline void SDCARD_SPI_CLK_ENABLE()
{
	__HAL_RCC_SPI2_CLK_ENABLE();
}

inline void SDCARD_GPIO_CLK_ENABLE()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

inline void SDCARD_SPI_FORCE_REALEASE_RESET()
{
	__HAL_RCC_SPI2_FORCE_RESET();
	__HAL_RCC_SPI2_RELEASE_RESET();
}

#ifdef __cplusplus
}
#endif

/// ------------------------------------------------------------------------------------------------
}

#endif	/// HAL_MSP_PINOUT_MAPPING_HPP_
/// === END OF FILE	================================================================================
