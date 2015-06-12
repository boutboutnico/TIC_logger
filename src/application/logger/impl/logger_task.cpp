///
/// \file	tsk_logger.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///

#include "logger_task.hpp"
using namespace application::logger;

/// === Includes	================================================================================

#include <cstring>
#include "../chanN/FatFs/src/ff.h"
#include "appli_conf.hpp"

#include "diag/Trace.h"
#include "led/led.hpp"

/// === Namespaces	================================================================================

using namespace os;
using namespace femtin;

/// === Public Definitions	========================================================================

LoggerTask::LoggerTask()
		: 	Task(application::LOGGER_TASK_NAME.c_str(), application::LOGGER_TASK_STACK_SIZE,
					application::LOGGER_TASK_PRIO),
			queue_(2, sizeof(dataset_t))
{
	suspend();
}

/// ------------------------------------------------------------------------------------------------

bool LoggerTask::initialize()
{
	bool b_result = false;

	vol_.mount("", 1) == FR_OK ? b_result = true : b_result = false;

	b_result ?
			trace_puts("[Logger] SD Card mounted") :
			trace_puts("[Logger] !!! SD Card NOT mounted !!!");

//	file_.open("hello.txt", FA_OPEN_EXISTING | FA_WRITE | FA_READ) == FR_OK ?
//			b_result = true : b_result = false;
//
//	b_result ? trace_puts("[Logger] File opened") : trace_puts("[Logger] !!! File NOT opened !!!");
//
//	/// Read All
//	char line[64];
//	while (file_.eof() == false)
//	{
//		trace_printf("%s", file_.gets(line, sizeof(line)));
//	}
//
//	/// Set file pointer to beginning
//	file_.lseek(0);

	return b_result;
}

/// ------------------------------------------------------------------------------------------------

bool LoggerTask::log(const dataset_t& _dataset)
{
	bool b_result = queue_.sendToBack(&_dataset, 200);

	assert(b_result == true);

	return b_result;
}

/// ------------------------------------------------------------------------------------------------

void LoggerTask::run()
{
	/// --- Initialization	------------------------------------------------------------------------

	/// --- Infinite Loop	------------------------------------------------------------------------

	dataset_t dataset;

	for (;;)
	{
		board::led::LED_Blue.off();

		queue_.receive(&dataset);

		board::led::LED_Blue.on();

		femtin::String<femtin::fatfs::File::FILENAME_SIZE> filename(dataset.file_name_);

		/// Is file already open ?
		if (file_.name() != filename)
		{
			file_.close();
			file_.open(filename, FA_OPEN_ALWAYS | FA_WRITE);

			/// Set file pointer to end
			file_.lseek(file_.size());
		}

		/// Log to file
		file_.puts(dataset.str_);
		file_.puts("\n");
		file_.sync();
	}
}

/// === END OF FILE	================================================================================
