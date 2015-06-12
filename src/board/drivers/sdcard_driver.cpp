///
/// \file	spi.cpp
///	\brief	
///	\date	8 avr. 2015
/// \author	nb_work
///

#include "sdcard_driver.hpp"
using namespace board::mcu;

/// === Includes	================================================================================

#include <assert.h>

#include "diag/Trace.h"

/// === Static Definitions	========================================================================

static SPI_HandleTypeDef SDCARD_SPI_Handle;

/// === Public Definitions	========================================================================

SDCardDriver::SDCardDriver()
		: SEM_SPI(0)
{
	initialize(SPI_BAUDRATEPRESCALER_256);
}

/// ------------------------------------------------------------------------------------------------

bool SDCardDriver::speed(uint32_t _speed)
{
	return initialize(_speed);
}

/// ------------------------------------------------------------------------------------------------

bool SDCardDriver::write(uint8_t _data)
{
	if (HAL_SPI_Transmit_IT(&SDCARD_SPI_Handle, &_data, 1) != HAL_OK)
	{
		return false;
	}

	if (SEM_SPI.take(200) == false)
	{
		while (1)
		{
		}
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

bool SDCardDriver::write(const uint8_t* _data, size_t _len)
{
	if (HAL_SPI_Transmit_IT(&SDCARD_SPI_Handle, const_cast<uint8_t*>(_data),
							static_cast<uint16_t>(_len))
		!= HAL_OK)
	{
		return false;
	}

	if (SEM_SPI.take(200) == false)
	{
		while (1)
		{
		}
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

bool SDCardDriver::read(uint8_t* _data, size_t _len)
{
	if (HAL_SPI_Receive_IT(&SDCARD_SPI_Handle, _data, static_cast<uint16_t>(_len)) != HAL_OK)
	{
		return false;
	}

	if (SEM_SPI.take(200) == false)
	{
		while (1)
		{
		}
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

bool SDCardDriver::initialize(uint32_t _speed)
{
	/// --- Clocks

	/// Enable SPI interface clock
	SDCARD_SPI_CLK_ENABLE();

	/// Enable the clock for SPI GPIOs
	SDCARD_GPIO_CLK_ENABLE();

	/// --- GPIOs

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = SDCARD_SPI_PIN_AF;

	/// CLK Pin
	GPIO_InitStruct.Pin = SDCARD_SPI_CLK_PIN;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), &GPIO_InitStruct);

	/// MISO Pin
	GPIO_InitStruct.Pin = SDCARD_SPI_MISO_PIN;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), &GPIO_InitStruct);

	/// MOSI Pin
	GPIO_InitStruct.Pin = SDCARD_SPI_MOSI_PIN;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), &GPIO_InitStruct);

	/// CS Pin
	GPIO_InitStruct.Pin = SDCARD_SPI_CS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), &GPIO_InitStruct);

	/// Set CS to High
	HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(SDCARD_SPI_GPIO_PORT), SDCARD_SPI_CS_PIN,
						GPIO_PIN_SET);

	/// --- Interrupt

	/// \warning	Must be lower than configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
	///				to be able to call a freeRTOS ISR routine

	/// Configure the SPI interrupt priority
	HAL_NVIC_SetPriority(SDCARD_SPI_IRQn, SDCARD_SPI_IRQn_PRIO, SDCARD_SPI_IRQn_SUBPRIO);

	/// Enable NVIC SPI IRQ handle
	HAL_NVIC_EnableIRQ(SDCARD_SPI_IRQn);

	/// --- SPI

	SDCARD_SPI_Handle.Instance = const_cast<SPI_TypeDef*>(SDCARD_SPI);
	SDCARD_SPI_Handle.Init.BaudRatePrescaler = _speed;
	SDCARD_SPI_Handle.Init.Direction = SPI_DIRECTION_2LINES;
	SDCARD_SPI_Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
	SDCARD_SPI_Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
	SDCARD_SPI_Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	SDCARD_SPI_Handle.Init.CRCPolynomial = 7;
	SDCARD_SPI_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
	SDCARD_SPI_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SDCARD_SPI_Handle.Init.NSS = SPI_NSS_SOFT;
	SDCARD_SPI_Handle.Init.TIMode = SPI_TIMODE_DISABLE;
	SDCARD_SPI_Handle.Init.Mode = SPI_MODE_MASTER;

	/// User parameter
	SDCARD_SPI_Handle.user_param = this;

	if (HAL_SPI_Init(&SDCARD_SPI_Handle) != HAL_OK)
	{
		return false;
	}

	return true;
}

/// ------------------------------------------------------------------------------------------------

void SDCardDriver::HAL_SPI_TxCpltCallback(SPI_HandleTypeDef*_hspi)
{
	if (_hspi == &SDCARD_SPI_Handle)
	{
		SEM_SPI.giveFromISR();
	}
}

/// ------------------------------------------------------------------------------------------------

void SDCardDriver::HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* _hspi)
{
	if (_hspi == &SDCARD_SPI_Handle)
	{
		SEM_SPI.giveFromISR();
	}
}

/// ------------------------------------------------------------------------------------------------

void SDCardDriver::HAL_SPI_ErrorCallback(SPI_HandleTypeDef* _hspi)
{
//	(void) _hspi;
//	while (1)
//		;

//#define HAL_SPI_ERROR_NONE         ((uint32_t)0x00000000)   /*!< No error             */
//#define HAL_SPI_ERROR_MODF         ((uint32_t)0x00000001)   /*!< MODF error           */
//#define HAL_SPI_ERROR_CRC          ((uint32_t)0x00000002)   /*!< CRC error            */
//#define HAL_SPI_ERROR_OVR          ((uint32_t)0x00000004)   /*!< OVR error            */
//#define HAL_SPI_ERROR_FRE          ((uint32_t)0x00000008)   /*!< FRE error            */
//#define HAL_SPI_ERROR_DMA          ((uint32_t)0x00000010)   /*!< DMA transfer error   */
//#define HAL_SPI_ERROR_FLAG         ((uint32_t)0x00000010)   /*!< Flag: RXNE,TXE, BSY  */

	switch (_hspi->ErrorCode)
	{
	case HAL_SPI_ERROR_MODF:
		trace_puts("HAL_SPI_ERROR_MODF");
		break;

	case HAL_SPI_ERROR_CRC:
		trace_puts("HAL_SPI_ERROR_CRC");
		break;

	case HAL_SPI_ERROR_OVR:
		trace_puts("HAL_SPI_ERROR_OVR");
		__HAL_SPI_CLEAR_OVRFLAG(&SDCARD_SPI_Handle);
		break;

	case HAL_SPI_ERROR_FRE:
		trace_puts("HAL_SPI_ERROR_FRE");
		break;

	case HAL_SPI_ERROR_DMA:
		trace_puts("HAL_SPI_ERROR_DMA");
		break;
	}
}

/// ================================================================================================
/// === Public Definitions	========================================================================

void board::mcu::SPI2_IRQHandler(void)
{
	HAL_SPI_IRQHandler(&SDCARD_SPI_Handle);
}

/// ------------------------------------------------------------------------------------------------

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* _hspi)
{
	assert(_hspi->user_param != 0);

	reinterpret_cast<SDCardDriver*>(_hspi->user_param)->HAL_SPI_TxCpltCallback(_hspi);

}

/// ------------------------------------------------------------------------------------------------

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef* _hspi)
{
	assert(_hspi->user_param != 0);

	reinterpret_cast<SDCardDriver*>(_hspi->user_param)->HAL_SPI_RxCpltCallback(_hspi);
}

/// ------------------------------------------------------------------------------------------------

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef* _hspi)
{
	assert(_hspi->user_param != 0);

	reinterpret_cast<SDCardDriver*>(_hspi->user_param)->HAL_SPI_ErrorCallback(_hspi);
}

/// === END OF FILE	================================================================================
