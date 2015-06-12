///
/// \file	trace_driver.cpp
///	\brief	
///	\date	22 mars 2015
/// \author	nb_work
///

#include "trace_driver.hpp"
using namespace board::mcu;

/// === Includes	================================================================================

#include "pinout_mapping.hpp"
#include "led/led.hpp"

/// === Public Definitions	========================================================================

TraceDriver::TraceDriver()
		: PeripheralHandler(Trace_UART_e, &UART_handle_), SEM_UART(0)
{
	initialize(115200);
}

/// ------------------------------------------------------------------------------------------------

void TraceDriver::write(const char* _buf, size_t _size)
{
	if (HAL_UART_Transmit_IT(&UART_handle_, reinterpret_cast<const uint8_t*>(_buf), _size) != HAL_OK)
	{
		board::led::LED_Red.on();
	}

	if (SEM_UART.take(femtin::unit::millisecond(200)) == false)
	{
		while (1)
		{
		}
	}
}

/// === Private Definitions	========================================================================

bool TraceDriver::initialize(uint32_t _speed)
{
	/// --- Clocks

	/// Enable UART interface clock
	Trace_UART_CLK_ENABLE();

	/// Enable the clocks for UART GPIOs
	Trace_GPIO_CLK_ENABLE();

	/// --- GPIOs

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = Trace_UART_TX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = Trace_UART_PIN_AF;

	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(Trace_UART_GPIO_PORT), &GPIO_InitStruct);

	/// --- Interrupt

	/// \warning	Must be lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	///				to be able to call a freeRTOS ISR routine

	/// Configure the UART interrupt priority
	HAL_NVIC_SetPriority(Trace_UART_IRQn, Trace_UART_IRQn_PRIO, Trace_UART_IRQn_SUBPRIO);

	/// Enable NVIC UART IRQ handle
	HAL_NVIC_EnableIRQ(Trace_UART_IRQn);

	/// --- UART

	UART_handle_.Instance = const_cast<USART_TypeDef*>(Trace_UART);
	UART_handle_.Init.BaudRate = _speed;
	UART_handle_.Init.WordLength = UART_WORDLENGTH_9B;
	UART_handle_.Init.StopBits = UART_STOPBITS_1;
	UART_handle_.Init.Parity = UART_PARITY_EVEN;
	UART_handle_.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_handle_.Init.Mode = UART_MODE_TX;

	/// User param
	UART_handle_.user_param = this;

	if (HAL_UART_Init(&UART_handle_) != HAL_OK)
	{
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

void TraceDriver::HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == Trace_UART)
	{
		SEM_UART.giveFromISR();
	}
}

/// ------------------------------------------------------------------------------------------------

void TraceDriver::HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == Trace_UART)
	{
		switch (_huart->ErrorCode)
		{
		case HAL_UART_ERROR_PE:
		case HAL_UART_ERROR_NE:
		case HAL_UART_ERROR_FE:
		case HAL_UART_ERROR_ORE:
		case HAL_UART_ERROR_DMA:

			board::led::LED_Red.on();
			while (1)
			{
			}
			break;
		}
	}
}

/// === END OF FILE	================================================================================
