/*
 Femtin V0.0.1 - Copyright (C) 2015 Nicolas Boutin.
 All rights reserved

 This file is part of the Femtin distribution.

 Femtin is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation.

 Femtin is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.
 */

/// ================================================================================================
///
/// \file	peripheral_handler.hpp
/// \brief
/// \date	22/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef BOARD_DRIVERS_PERIPHERAL_HANDLER_HPP_
#define BOARD_DRIVERS_PERIPHERAL_HANDLER_HPP_

/// === Includes	================================================================================

#include <cstdint>
#include <assert.h>
#include "peripherals_manager.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{
/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================

enum class Peripherals_e
	: uint8_t
	{
		UART2 = 0x00,
	UART3,
};

/// === Union	====================================================================================

union Handle_u
{
	Handle_u(UART_HandleTypeDef* _handle)
			: uart_(_handle)
	{
	}

	Handle_u(USART_HandleTypeDef* _handle)
			: usart_(_handle)
	{
	}

	/// --- Public Attributes
	UART_HandleTypeDef* uart_;
	USART_HandleTypeDef* usart_;
};

/// === Class Declarations	========================================================================

class PeripheralHandler
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	PeripheralHandler(Peripherals_e _peri, Handle_u _handle)
			: peripheral_(_peri), handle_(_handle)
	{
		subscribe(*this);
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline Peripherals_e peripheral() const
	{
		return peripheral_;
	}

	inline Handle_u& handle()
	{
		return handle_;
	}

	//// --- UART Callback	------------------------------------------------------------------------

	virtual void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _huart)
	{
		(void) _huart;
	}

	virtual void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart)
	{
		(void) _huart;
	}

	virtual void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart)
	{
		(void) _huart;
	}

	//// --- USART Callback	------------------------------------------------------------------------

	virtual void HAL_USART_RxCpltCallback(USART_HandleTypeDef* _husart)
	{
		(void) _husart;
	}

	virtual void HAL_USART_TxCpltCallback(USART_HandleTypeDef* _husart)
	{
		(void) _husart;
	}

	virtual void HAL_USART_ErrorCallback(USART_HandleTypeDef* _husart)
	{
		(void) _husart;
	}

private:
	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	Peripherals_e peripheral_;
	Handle_u handle_;
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}
/// name
}/// sub_name

#endif	/// BOARD_DRIVERS_PERIPHERAL_HANDLER_HPP_
/// === END OF FILE	================================================================================
