///
/// \file	template.cpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///

#include "logger_component.hpp"
using namespace application::logger;

/// === Includes	================================================================================
/// === Namespaces	================================================================================


using namespace femtin;
using namespace application;
using namespace application::system_controller;


/// === Constants	================================================================================
/// === Public Definitions	========================================================================

const femtin::String<COMPONENT_NAME_LEN_MAX>& LoggerComponent::name() const
{
	return LOGGER_TASK_NAME;
}

/// ------------------------------------------------------------------------------------------------

void* LoggerComponent::getAPIService()
{
	return &service_;
}

/// ------------------------------------------------------------------------------------------------

bool LoggerComponent::initialize(ComponentRegistry& _comp_reg)
{
	(void) _comp_reg;

	service_.link(&task_);
	return task_.initialize();
}

/// ------------------------------------------------------------------------------------------------

bool LoggerComponent::start()
{
	task_.resume();

	return true;
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
