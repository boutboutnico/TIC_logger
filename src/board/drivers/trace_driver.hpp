///
/// \file	trace_driver.hpp
///	\brief	
///	\date	29/05/2015
/// \author	nboutin
///
#ifndef BOARD_DRIVERS_TRACE_DRIVER_HPP_
#define BOARD_DRIVERS_TRACE_DRIVER_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "femtin/freeRTOS_wrapper/semaphore/semaphore.hpp"
#include "peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{

/// === Class Declarations	========================================================================

class TraceDriver : public PeripheralHandler
{
public:
	/// === Public Declarations	====================================================================

	TraceDriver();

	void write(const char* _buf, size_t _size);

private:
	/// === Private Constants	====================================================================
	/// === Private Declarations	================================================================

	bool initialize(uint32_t _speed);

	virtual void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart);
	virtual void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart);

	/// === Private Attributes	====================================================================

	UART_HandleTypeDef UART_handle_;
	femtin::os::Semaphore SEM_UART;
};
/// === Inlines Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}///mcu
}    /// board
#endif	/// BOARD_DRIVERS_TIC_DRIVER_HPP_
/// === END OF FILE	================================================================================
