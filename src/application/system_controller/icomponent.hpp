///
/// \file	icomponent.hpp
///	\brief	
///	\date	05/05/2015
/// \author	nboutin
///
#ifndef APPLICATION_SYSTEM_CONTROLLER_ICOMPONENT_HPP_
#define APPLICATION_SYSTEM_CONTROLLER_ICOMPONENT_HPP_

/// === Includes	================================================================================

#include "../appli_conf.hpp"
#include "femtin/string.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace system_controller
{

/// === Forward Declarations	====================================================================

class ComponentRegistry;

/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class IComponent
{
public:
	/// === Public Declarations	====================================================================

	virtual const femtin::String<COMPONENT_NAME_LEN_MAX>& name() const = 0;

	virtual void* getAPIService()
	{
		assert(false);
		return NULL;
	}

	virtual bool initialize(ComponentRegistry& _comp_reg) = 0;

	virtual bool start() = 0;

};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_SYSTEM_CONTROLLER_ICOMPONENT_HPP_
/// === END OF FILE	================================================================================
