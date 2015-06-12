///
/// \file	tic_driver.hpp
///	\brief	
///	\date	22 mars 2015
/// \author	nb_work
///
#ifndef BOARD_DRIVERS_TIC_DRIVER_HPP_
#define BOARD_DRIVERS_TIC_DRIVER_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"
#include "femtin/array.hpp"
#include "femtin/observer.hpp"
#include "peripheral_handler.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{

/// === Structures	================================================================================

struct TICDriver_Data
{
	bool error_;
	femtin::Array_ptr<uint8_t> array_ptr_;    /// TODO use const uint8_t
};

/// === Class Declarations	========================================================================

class TICDriver : public PeripheralHandler, public femtin::Observable<TICDriver_Data, 1>
{
public:
	/// === Public Declarations	====================================================================

	TICDriver();

	bool start();

	uint32_t speed() const;
	bool speed(uint32_t _speed);

private:
	/// === Private Constants	====================================================================

	static const uint8_t RX_BUFFER_SIZE = 64;

	/// === Private Declarations	================================================================

	bool initialize(uint32_t _speed);

	virtual void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _huart);
	virtual void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart);

	/// === Private Attributes	====================================================================

	UART_HandleTypeDef UART_handle_;
	TICDriver_Data st_observer_data_;
	femtin::Array<uint8_t, RX_BUFFER_SIZE> rx_buffer_;
};
/// === Inlines Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}///mcu
}    /// board
#endif	/// BOARD_DRIVERS_TIC_DRIVER_HPP_
/// === END OF FILE	================================================================================
