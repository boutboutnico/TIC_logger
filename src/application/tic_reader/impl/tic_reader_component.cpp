///
/// \file	template.cpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///

#include "tic_reader_component.hpp"
using namespace application::tic_reader;

/// === Includes	================================================================================
/// === Namespaces	================================================================================

using namespace femtin;
using namespace application;
using namespace application::system_controller;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

TICReaderComponent::TICReaderComponent()
		: service_(), task_()
{

}

/// ------------------------------------------------------------------------------------------------

const String<COMPONENT_NAME_LEN_MAX>& TICReaderComponent::name() const
{
	return TIC_READER_TASK_NAME;
}

/// ------------------------------------------------------------------------------------------------

void* TICReaderComponent::getAPIService()
{
	return &service_;
}

/// ------------------------------------------------------------------------------------------------

bool TICReaderComponent::initialize(ComponentRegistry& _comp_reg)
{
	bool b_result = task_.initialize(_comp_reg);

	return b_result;
}

/// ------------------------------------------------------------------------------------------------

bool TICReaderComponent::start()
{
	task_.resume();

	return true;
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
