///
/// \file	tsk_logger.hpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_LOGGER_TSK_LOGGER_HPP_
#define APPLICATION_LOGGER_TSK_LOGGER_HPP_

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/task/task.hpp"
#include "femtin/freeRTOS_wrapper/queue/queue.hpp"
#include "femtin/string.hpp"
#include "femtin/array.hpp"
#include "femtin/FatFs_wrapper/volume.hpp"
#include "femtin/FatFs_wrapper/file.hpp"
#include "../i_logger.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace logger
{

/// === Structures	================================================================================
/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class LoggerTask : public os::Task
{
public:
	/// === Public Constants	====================================================================
	/// === Public Declarations	====================================================================

	LoggerTask();

	bool initialize();

	virtual void run();

	bool log(const dataset_t& _dataset);

private:
	/// === Private Constants	====================================================================
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	femtin::fatfs::Volume vol_;
	femtin::fatfs::File file_;
	os::Queue queue_;
};

#pragma GCC diagnostic pop

/// === Inlines Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}/// logger
}    /// application
#endif	/// APPLICATION_LOGGER_TSK_LOGGER_HPP_
/// === END OF FILE	================================================================================
