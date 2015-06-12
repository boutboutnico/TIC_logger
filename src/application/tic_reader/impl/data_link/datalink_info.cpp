///
/// \file	datalink_info.cpp
///	\brief	
///	\date	4 avr. 2015
/// \author	nb_work
///

#include "datalink_info.h"
using namespace application::tic_reader;

/// === Includes	================================================================================
/// === Public Definitions	========================================================================

DataLinkInfo::DataLinkInfo()
		: 	tic_version_(0),
			frame_count_(0),
			line_count_(0),
			line_per_frame_average_(0),
			checksum_error_(0),
			successive_error_(0)
{

}

/// ------------------------------------------------------------------------------------------------

void DataLinkInfo::incFrame()
{
	static uint32_t line_per_frame_count = 0;

	line_per_frame_average_ = femtin::simple_moving_average(frame_count_,
															line_count_ - line_per_frame_count,
															line_per_frame_average_);
	frame_count_++;
	line_per_frame_count = line_count_;
}

/// === END OF FILE	================================================================================
