/// ================================================================================================
///
/// \file	template.cpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
/// ================================================================================================

#include "trace.hpp"

/// === Includes	================================================================================

#include <stdio.h>
#include <stdarg.h>
#include <cstring>
//#include "xprintf/xprintf.hpp"
#include "femtin/freeRTOS_wrapper/semaphore/mutex.hpp"
#include "femtin/scoped_locking.hpp"
#include "drivers/trace_driver.hpp"
#include "led/led.hpp"

/// === Namespaces	================================================================================

using namespace board::mcu;

namespace application
{
namespace trace
{

/// === Constants	================================================================================
/// ===

static TraceDriver* ptrace_driver;
static femtin::os::Mutex* pMUT_trace;

/// === Public Definitions	========================================================================

void trace_initialize()
{
	static TraceDriver trace_driver;
	static femtin::os::Mutex MUT_trace;

	ptrace_driver = &trace_driver;
	pMUT_trace = &MUT_trace;
}

/// ------------------------------------------------------------------------------------------------

void trace_putc(const char _c)
{
	femtin::Guard<femtin::os::Mutex> guard(*pMUT_trace, femtin::unit::millisecond(200));

	ptrace_driver->write(&_c, 1);
}

/// ------------------------------------------------------------------------------------------------

void trace_puts(const char* _s)
{
	femtin::Guard<femtin::os::Mutex> guard(*pMUT_trace, femtin::unit::millisecond(200));

	ptrace_driver->write(_s, strlen(_s));
	ptrace_driver->write("\n", 1);
}

/// ------------------------------------------------------------------------------------------------

void trace_printf(const char* format, ...)
{
	femtin::Guard<femtin::os::Mutex> guard(*pMUT_trace, femtin::unit::millisecond(200));

	va_list ap;
	va_start(ap, format);

	/// TODO: rewrite it to no longer use newlib, it is way too heavy
	/// TODO Use ring buffer

	static char buf[128];

	uint32_t ret = vsnprintf(buf, sizeof(buf), format, ap);
	if (ret > 0)
	{
		/// Transfer the buffer to the device
		ptrace_driver->write(buf, strlen(buf));
	}

	va_end(ap);
}

/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------

}/// trace
}    /// application

/// === END OF FILE	================================================================================
