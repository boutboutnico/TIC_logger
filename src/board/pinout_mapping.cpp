///
/// \file	pinout_mapping.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///

#include "pinout_mapping.hpp"

namespace board
{

/// --- UART2 - TIC	--------------------------------------------------------------------------------

const USART_TypeDef* TIC_UART = USART2;
const GPIO_TypeDef* TIC_UART_GPIO_PORT = GPIOA;

/// --- UART3 - Trace	--------------------------------------------------------------------------------

const USART_TypeDef* Trace_UART = USART3;
const GPIO_TypeDef* Trace_UART_GPIO_PORT = GPIOD;

/// --- SPI2 - SD Card	----------------------------------------------------------------------------

const SPI_TypeDef* SDCARD_SPI = SPI2;
const GPIO_TypeDef* SDCARD_SPI_GPIO_PORT = GPIOB;
}

/// === END OF FILE	================================================================================
