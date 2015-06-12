/*
 * tsk_reader.cpp
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#include "tic_reader_task.hpp"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include <cstring>

#include "femtin/freeRTOS_wrapper/delay.hpp"
#include "femtin/freeRTOS_wrapper/direct_task_notification/direct_task_notification.hpp"

#include "appli_conf.hpp"
#include "led/led.hpp"

#include "trace/trace.hpp"
//#include "diag/Trace.h"

/// === Namespaces	================================================================================

using namespace os;
using namespace board::mcu;
using namespace board::led;
using namespace application::system_controller;
using namespace application::trace;

/// === Public Definitions	========================================================================

TICReaderTask::TICReaderTask()
		: 	Task(application::TIC_READER_TASK_NAME.c_str(), application::TIC_READER_TASK_STACK_SIZE,
					application::TIC_READER_TASK_PRIO),
			tic_driver_(),
			rbuf_rx_(),
			datalink_()
{
	suspend();
}

/// ------------------------------------------------------------------------------------------------

bool TICReaderTask::initialize(ComponentRegistry& _comp_reg)
{
	datalink_.link(_comp_reg);
	return tic_driver_.subscribe(*this);
}

/// ------------------------------------------------------------------------------------------------

void TICReaderTask::run()
{
	uint32_t notification_value = 0;
	uint8_t read8 = 0;

	volatile size_t capacity = 0;
	volatile uint32_t frame_count = 0;
	volatile uint32_t line_count = 0;
	volatile uint32_t checksum_error = 0;
	volatile uint32_t line_per_frame_aveg = 0;

	/// --- Initialization	------------------------------------------------------------------------

	tic_driver_.start();

	const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

	uint32_t i = 0;

	for (;;)
	{
//		trace_putc('1');
		trace_puts("ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`");
		trace_puts("abcdefghijklmnopqrstuvwxyz{|}~");
		trace_printf("val=%d\n", i++);
		trace_printf("%d\n", 1234);				//"1234"
		trace_printf("%6d,%3d%%\n", -200, 5);   //"  -200,  5%"
		trace_printf("%-6u\n", 100);			//"100   "
		trace_printf("%ld\n", 12345678L);		//"12345678"
		trace_printf("%04x\n", 0xA3);			//"00a3"
		trace_printf("%08LX\n", 0x123ABC);		//"00123ABC"
		trace_printf("%016b\n", 0x550F);		//"0101010100001111"
		trace_printf("%s\n", "String");			//"String"
		trace_printf("%-4s\n", "abc");			//"abc "
		trace_printf("%4s\n", "abc");			//" abc"
		trace_printf("%c\n", 'a');				//"a"
		trace_printf("%f\n", 10.0);            	//<xprintf lacks floating point support>
		vTaskDelay(xDelay);
	}

	/// --- Infinite Loop	------------------------------------------------------------------------

	for (;;)
	{
		notification_value = os::notifyTake(true, 5000);

		if (notification_value == 1)
		{
			board::led::LED_Green.toggle();

			while (rbuf_rx_.size() > 0)
			{
				read8 = rbuf_rx_.read<uint8_t>();
				datalink_.nextData(read8);
			}

			/// Detect speed error and change
			if (datalink_.getInfo().getSuccessiveError() >= 20)
			{
				board::led::LED_Red.on();

				if (tic_driver_.speed() == 1200)
				{
					tic_driver_.speed(9600);
				}
				else if (tic_driver_.speed() == 9600)
				{
					tic_driver_.speed(1200);
				}
			}
			else
			{
				board::led::LED_Red.off();
			}

			capacity = rbuf_rx_.capacity();
			frame_count = datalink_.getInfo().getFrameCount();
			line_count = datalink_.getInfo().getLineCount();
			line_per_frame_aveg = datalink_.getInfo().getLinePerFrameAverage();
			checksum_error = datalink_.getInfo().getChecksumError();
		}
		else
		{
		}
	}
}

/// ------------------------------------------------------------------------------------------------

void TICReaderTask::update(const TICDriver_Data& _data) const
{
	if (_data.error_ == false)
	{
		for (size_t i = 0; i < _data.array_ptr_.max_size(); i++)
		{
			rbuf_rx_.add<uint8_t>(_data.array_ptr_[i]);
		}
		os::notifyGiveISR(handle());
	}
}

/// === END OF FILE	================================================================================
