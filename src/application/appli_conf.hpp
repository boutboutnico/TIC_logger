///
/// \file	appli_conf.hpp
///	\brief	
///	\date	19/04/2015
/// \author	nb_work
///
#ifndef APPLICATION_APPLI_CONF_HPP_
#define APPLICATION_APPLI_CONF_HPP_

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/task/task.hpp"
#include "femtin/string.hpp"
#include "FreeRTOSConfig.h"

/// === Namespaces	================================================================================

namespace application
{

/// === Public Declarations	========================================================================

const uint8_t COMPONENT_COUNT = 2;
const uint8_t COMPONENT_NAME_LEN_MAX = configMAX_TASK_NAME_LEN;

const UBaseType_t COMPONENT_REGISTRY_TASK_PRIO = (tskIDLE_PRIORITY + 4);
const uint16_t COMPONENT_REGISTRY_TASK_STACK_SIZE = configMINIMAL_STACK_SIZE;
const femtin::String<COMPONENT_NAME_LEN_MAX> COMPONENT_REGISTRY_TASK_NAME("CompReg");

const UBaseType_t TIC_READER_TASK_PRIO = (tskIDLE_PRIORITY + 3);
const uint16_t TIC_READER_TASK_STACK_SIZE = configMINIMAL_STACK_SIZE * 2;
const femtin::String<COMPONENT_NAME_LEN_MAX> TIC_READER_TASK_NAME("TIC_Reader");

const UBaseType_t LOGGER_TASK_PRIO = (tskIDLE_PRIORITY + 2);
const uint16_t LOGGER_TASK_STACK_SIZE = configMINIMAL_STACK_SIZE * 2;
const femtin::String<COMPONENT_NAME_LEN_MAX> LOGGER_TASK_NAME("Logger");

/// ------------------------------------------------------------------------------------------------
}

#endif	/// APPLICATION_APPLI_CONF_HPP_
/// === END OF FILE	================================================================================
