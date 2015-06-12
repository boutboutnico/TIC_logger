///
/// \file	template.hpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
#ifndef APPLICATION_LOGGER_IMPL_LOGGER_SERVICE_HPP_
#define APPLICATION_LOGGER_IMPL_LOGGER_SERVICE_HPP_

/// === Includes	================================================================================

#include "../i_logger.hpp"
#include "logger_task.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace logger
{

/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class LoggerService : public ILogger
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	LoggerService();

	/// --- Service interface	--------------------------------------------------------------------

	virtual bool log(const dataset_t& _dataset);

	/// ---

	inline void link(LoggerTask* _task);
	bool initialize();

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	LoggerTask* task_;
};

/// === Inlines Declarations	====================================================================

inline void LoggerService::link(LoggerTask* _task)
{
	task_ = _task;
}

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_LOGGER_IMPL_LOGGER_SERVICE_HPP_
/// === END OF FILE	================================================================================
