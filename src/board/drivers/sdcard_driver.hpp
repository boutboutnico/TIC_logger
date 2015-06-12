///
/// \file	sdcard_driver.hpp
///	\brief	
///	\date	8 avr. 2015
/// \author	nb_work
///
#ifndef BOARD_DRIVERS_SDCARD_DRIVER_HPP_
#define BOARD_DRIVERS_SDCARD_DRIVER_HPP_

/// === Includes	================================================================================

#include <cstddef>
#include "stm32f4xx_hal.h"
#include "femtin/freeRTOS_wrapper/semaphore/semaphore.hpp"
#include "pinout_mapping.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{

/// === Class Declarations	========================================================================

class SDCardDriver
{
public:
	/// === Public Declarations	====================================================================

	SDCardDriver();

	inline void __attribute((always_inline)) CS_Low();
	inline void __attribute((always_inline)) CS_High();

	bool write(uint8_t _data);
	bool write(const uint8_t* _data, size_t _len);
	bool read(uint8_t* _data, size_t _len);

	bool speed(uint32_t _speed);

	/// --- Do not use	----------------------------------------------------------------------------

	void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef*_hspi);
	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* _hspi);
	void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* _hspi);

private:
	/// === Private Declarations	================================================================

	bool initialize(uint32_t _speed);

	/// === Private Attributes	====================================================================

	femtin::os::Semaphore SEM_SPI;
};

/// === Inlines Definitions	========================================================================

inline void __attribute((always_inline)) SDCardDriver::CS_Low()
{
	HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), SDCARD_SPI_CS_PIN,
						GPIO_PIN_RESET);
}

/// ------------------------------------------------------------------------------------------------

inline void __attribute((always_inline)) SDCardDriver::CS_High()
{
	HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), SDCARD_SPI_CS_PIN,
						GPIO_PIN_SET);
}

/// === Public Declarations	========================================================================

#ifdef __cplusplus
extern "C"
{
#endif

void SPI2_IRQHandler(void);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef*_hspi);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* _hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* _hspi);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* _hspi);

#ifdef __cplusplus
}
#endif
/// ------------------------------------------------------------------------------------------------
}/// mcu
}    /// board
#endif	/// BOARD_DRIVERS_SDCARD_DRIVER_HPP_
/// === END OF FILE	================================================================================
