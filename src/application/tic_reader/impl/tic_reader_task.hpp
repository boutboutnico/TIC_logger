/*
 * tsk_reader.h
 *
 *  Created on: 31 mars 2014
 *      Author: Nico_user
 */

#ifndef TSK_READER_H_
#define TSK_READER_H_

/// === Includes	================================================================================

#include "femtin/freeRTOS_wrapper/task/task.hpp"
#include "femtin/ring_buffer.hpp"

#include "drivers/tic_driver.hpp"
#include "data_link/data_link.h"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class TICReaderTask : public os::Task, femtin::Observer<board::mcu::TICDriver_Data>
{
public:
	/// === Public Constants	====================================================================
	/// === Public Declarations	====================================================================

	TICReaderTask();

	bool initialize(system_controller::ComponentRegistry& _comp_reg);

	virtual void run();

	void update(const board::mcu::TICDriver_Data& _data) const;

private:
	/// === Private Constants	====================================================================

	static const uint16_t RX_BUFFER_SIZE_ = 512;

	/// === Private Declarations	================================================================
	/// === Private Attributes	====================================================================

	board::mcu::TICDriver tic_driver_;

	/// mutable because update is const
	mutable femtin::Ring_Buffer<RX_BUFFER_SIZE_> rbuf_rx_;
	DataLink datalink_;

};

#pragma GCC diagnostic pop

/// === Inlines Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}
}
#endif	/// TSK_READER_H_
/// === END OF FILE	================================================================================
