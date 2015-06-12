///
/// \file	template.hpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
#ifndef APPLICATION_LOGGER_IMPL_LOGGER_COMPONENT_HPP_
#define APPLICATION_LOGGER_IMPL_LOGGER_COMPONENT_HPP_

/// === Includes	================================================================================

#include "system_controller/icomponent.hpp"

#include "logger_service.hpp"
#include "logger_task.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace logger
{
/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class LoggerComponent : public system_controller::IComponent
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// --- Component interface	--------------------------------------------------------------------

	virtual const femtin::String<COMPONENT_NAME_LEN_MAX>& name() const;
	virtual void* getAPIService();

	virtual bool initialize(system_controller::ComponentRegistry& _comp_reg);

	virtual bool start();

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	LoggerService service_;
	LoggerTask task_;
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_LOGGER_IMPL_LOGGER_COMPONENT_HPP_
/// === END OF FILE	================================================================================
