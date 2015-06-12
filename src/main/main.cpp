///
/// \file	main.cpp
///	\brief
///	\date	22 mars 2015
/// \author	nb_work
///

/// === Includes	================================================================================

#include "FreeRTOS.h"
#include "system_controller/component_registry.hpp"
#include "trace/trace.hpp"

/// === Namespaces	================================================================================

using namespace application::system_controller;
using namespace application::trace;

/// === Public Definitions	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	/// At this stage the system clock should have already been configured at high speed.

	trace_initialize();

	static ComponentRegistry comp_reg;

	vTaskStartScheduler();    /// should never return
}

#pragma GCC diagnostic pop

/// === END OF FILE	================================================================================
