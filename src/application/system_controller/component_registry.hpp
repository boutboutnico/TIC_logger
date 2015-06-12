///
/// \file	component_registry.hpp
///	\brief	
///	\date	05/05/2015
/// \author	nboutin
///
#ifndef APPLICATION_SYSTEM_CONTROLLER_COMPONENT_REGISTRY_HPP_
#define APPLICATION_SYSTEM_CONTROLLER_COMPONENT_REGISTRY_HPP_

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/task/task.hpp"
#include "femtin/array.hpp"

#include "icomponent.hpp"

#include "../appli_conf.hpp"

/// === Namespaces	================================================================================

namespace application
{

/// === Forward Declarations	====================================================================

namespace tic_reader
{
class ITICReader;
class TICReaderComponent;
}

namespace logger
{
class ILogger;
class LoggerComponent;
}

namespace system_controller
{

/// === Enumerations	============================================================================

enum class ComponentName_e
	: uint8_t
	{
		TIC_Reader = 0,
	Logger = 1,
};

/// === Class Declarations	========================================================================

class ComponentRegistry : public os::Task
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	ComponentRegistry();

	logger::ILogger* APILogger();

private:
	/// === Private Declarations	================================================================

	virtual void run();

	/// === Private Attributs	====================================================================

	femtin::Array<IComponent*, COMPONENT_COUNT> components_;

};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// application
}    /// system_controller

#endif	/// APPLICATION_SYSTEM_CONTROLLER_COMPONENT_REGISTRY_HPP_
/// === END OF FILE	================================================================================
