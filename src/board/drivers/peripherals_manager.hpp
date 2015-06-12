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
/// \file	peripherals_manager.hpp
/// \brief
/// \date	22/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef BOARD_DRIVERS_PERIPHERALS_MANAGER_HPP_
#define BOARD_DRIVERS_PERIPHERALS_MANAGER_HPP_

/// === Includes	================================================================================

#include "stm32f4xx_hal.h"

/// === Namespaces	================================================================================

namespace board
{

namespace mcu
{
/// === Forward Declarations	====================================================================

class PeripheralHandler;

/// === Enumerations	============================================================================
/// === Declarations	============================================================================

bool subscribe(PeripheralHandler& _handler);

/// ================================================================================================
/// === Public Declarations	========================================================================

#ifdef __cplusplus
extern "C"
{
#endif

/// --- UART	------------------------------------------------------------------------------------

void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef* _huart);

void HAL_USART_RxCpltCallback(USART_HandleTypeDef* _husart);
void HAL_USART_TxCpltCallback(USART_HandleTypeDef* _husart);
void HAL_USART_ErrorCallback(USART_HandleTypeDef* _husart);

#ifdef __cplusplus
}
#endif

}    /// name
}    /// sub_name

#endif	/// BOARD_DRIVERS_PERIPHERALS_MANAGER_HPP_
/// === END OF FILE	================================================================================
