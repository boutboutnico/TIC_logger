/// ================================================================================================
///
/// \file	template.cpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
/// ================================================================================================

#include "peripherals_manager.hpp"

/// === Includes	================================================================================

#include <assert.h>
#include "femtin/array.hpp"
#include "peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{

/// === Constants	================================================================================

/// ===

femtin::Array<PeripheralHandler*, 2> peripherals_;

/// === Public Definitions	========================================================================

bool subscribe(PeripheralHandler& _handler)
{
	switch (_handler.peripheral())
	{
	case Peripherals_e::UART2:
	case Peripherals_e::UART3:
	{
		peripherals_[static_cast<size_t>(_handler.peripheral())] = &_handler;
		break;
	}

	default:
	{
		assert(false);
	}
	}

	return true;
}

/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(peripherals_[static_cast<size_t>(Peripherals_e::UART2)]->handle().uart_);
}

/// ------------------------------------------------------------------------------------------------

void USART3_IRQHandler(void)
{
	HAL_UART_IRQHandler(peripherals_[static_cast<size_t>(Peripherals_e::UART3)]->handle().uart_);
}

/// ------------------------------------------------------------------------------------------------

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _huart)
{
	assert(_huart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_huart->user_param)->HAL_UART_RxCpltCallback(_huart);

}

/// ------------------------------------------------------------------------------------------------

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart)
{
	assert(_huart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_huart->user_param)->HAL_UART_TxCpltCallback(_huart);
}

/// ------------------------------------------------------------------------------------------------

void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart)
{
	assert(_huart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_huart->user_param)->HAL_UART_ErrorCallback(_huart);
}

/// ------------------------------------------------------------------------------------------------

void HAL_USART_RxCpltCallback(USART_HandleTypeDef* _husart)
{
	assert(_husart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_husart->user_param)->HAL_USART_RxCpltCallback(_husart);

}

/// ------------------------------------------------------------------------------------------------

void HAL_USART_TxCpltCallback(USART_HandleTypeDef* _husart)
{
	assert(_husart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_husart->user_param)->HAL_USART_TxCpltCallback(_husart);
}

/// ------------------------------------------------------------------------------------------------

void HAL_USART_ErrorCallback(USART_HandleTypeDef* _husart)
{
	assert(_husart->user_param != 0);

	reinterpret_cast<PeripheralHandler*>(_husart->user_param)->HAL_USART_ErrorCallback(_husart);
}

/// ------------------------------------------------------------------------------------------------
}/// mcu
}    /// board
/// === END OF FILE	================================================================================
