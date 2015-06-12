///
/// \file	tic_driver.cpp
///	\brief	
///	\date	22 mars 2015
/// \author	nb_work
///

#include "tic_driver.hpp"
using namespace board::mcu;

/// === Includes	================================================================================

#include "pinout_mapping.hpp"
#include "diag/Trace.h"

/// === Public Definitions	========================================================================

TICDriver::TICDriver()
		: PeripheralHandler(TIC_UART_e, &UART_handle_)
{
	st_observer_data_.array_ptr_ = rx_buffer_;
	st_observer_data_.error_ = true;

	initialize(9600);
}

/// ------------------------------------------------------------------------------------------------

bool TICDriver::start()
{
	if (HAL_UART_Receive_IT(&UART_handle_, rx_buffer_.data(), RX_BUFFER_SIZE) != HAL_OK)
	{
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

uint32_t TICDriver::speed() const
{
	return UART_handle_.Init.BaudRate;
}

/// ------------------------------------------------------------------------------------------------

bool TICDriver::speed(uint32_t _speed)
{
	return initialize(_speed);
}

/// ------------------------------------------------------------------------------------------------

bool TICDriver::initialize(uint32_t _speed)
{
	/// --- Clocks

	/// Enable UART interface clock
	TIC_UART_CLK_ENABLE();

	/// Enable the clocks for UART GPIOs
	TIC_GPIO_CLK_ENABLE();

	/// --- GPIOs

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = TIC_UART_RX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = TIC_UART_PIN_AF;

	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(TIC_UART_GPIO_PORT), &GPIO_InitStruct);

	/// --- Interrupt

	/// \warning	Must be lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	///				to be able to call a freeRTOS ISR routine

	/// Configure the UART interrupt priority
	HAL_NVIC_SetPriority(TIC_UART_IRQn, TIC_UART_IRQn_PRIO, TIC_UART_IRQn_SUBPRIO);

	/// Enable NVIC UART IRQ handle
	HAL_NVIC_EnableIRQ(TIC_UART_IRQn);

	/// --- UART

	UART_handle_.Instance = const_cast<USART_TypeDef*>(TIC_UART);
	UART_handle_.Init.BaudRate = _speed;
	UART_handle_.Init.WordLength = UART_WORDLENGTH_8B;
	UART_handle_.Init.StopBits = UART_STOPBITS_1;
	UART_handle_.Init.Parity = UART_PARITY_NONE;
	UART_handle_.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_handle_.Init.Mode = UART_MODE_RX;

	/// User param
	UART_handle_.user_param = this;

	if (HAL_UART_Init(&UART_handle_) != HAL_OK)
	{
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

void TICDriver::HAL_UART_RxCpltCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == TIC_UART)
	{
		__HAL_UART_FLUSH_DRREGISTER(&UART_handle_);    /// TODO useful ??

		if (HAL_UART_Receive_IT(&UART_handle_, rx_buffer_.data(), RX_BUFFER_SIZE) != HAL_OK)
		{
			st_observer_data_.error_ = true;
		}
		else
		{
			st_observer_data_.error_ = false;
		}

		/// Notify observer
		notify(st_observer_data_);

		/// Reset buffer
		rx_buffer_.clear();
	}
}

/// ------------------------------------------------------------------------------------------------

void TICDriver::HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart)
{
	if (_huart->Instance == TIC_UART)
	{
		switch (_huart->ErrorCode)
		{
		case HAL_UART_ERROR_PE:
			trace_puts("UART Parity Error");
			break;

		case HAL_UART_ERROR_NE:
			trace_puts("UART Noise Error");
			__HAL_UART_CLEAR_NEFLAG(&UART_handle_);
			break;

		case HAL_UART_ERROR_FE:
			trace_puts("UART Frame Error");
			__HAL_UART_CLEAR_FEFLAG(&UART_handle_);
			break;

		case HAL_UART_ERROR_ORE:
			trace_puts("UART Overrun Error");
			__HAL_UART_CLEAR_OREFLAG(&UART_handle_);
			break;

		case HAL_UART_ERROR_DMA:
			trace_puts("UART DMA Error");
			break;
		}

		/// Start again TIC Driver
		start();
	}
}

/// === END OF FILE	================================================================================
