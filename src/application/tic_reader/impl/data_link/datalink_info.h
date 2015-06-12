///
/// \file	controller.h
///	\brief	
///	\date	3 avr. 2015
/// \author	nb_work
///
#ifndef DATA_LINK_IMPL_DATALINK_INFO_H_
#define DATA_LINK_IMPL_DATALINK_INFO_H_

/// === Includes	================================================================================

#include <cstdint>

#include "femtin/average.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Class Declarations	========================================================================

/// \class	
/// \brief
/// \date	3 avr. 2015
/// \author	nb_work
class DataLinkInfo
{
public:
	/// === Public Declarations	====================================================================

	DataLinkInfo();

	/// --- Accessors	----------------------------------------------------------------------------

	inline uint8_t getTICVersion() const
	{
		return tic_version_;
	}

	inline void setTICVersion(uint8_t _tic_version)
	{
		tic_version_ = _tic_version;
	}

	void incFrame();

	inline uint32_t getFrameCount() const
	{
		return frame_count_;
	}

	inline void incLine()
	{
		line_count_++;
	}

	inline uint32_t getLineCount() const
	{
		return line_count_;
	}

	inline uint32_t getLinePerFrameAverage() const
	{
		return line_per_frame_average_;
	}

	inline void incChecksumError()
	{
		checksum_error_++;
	}

	inline uint32_t getChecksumError() const
	{
		return checksum_error_;
	}

	inline void incSuccessiveError()
	{
		successive_error_++;
	}

	inline void resetSuccessiveError()
	{
		successive_error_ = 0;
	}

	inline uint32_t getSuccessiveError() const
	{
		return successive_error_;
	}

private:
	/// === Private Attributes	====================================================================

	uint8_t tic_version_;
	uint32_t frame_count_;
	uint32_t line_count_;
	uint32_t line_per_frame_average_;
	uint32_t checksum_error_;
	uint32_t successive_error_;
};

/// === Inline Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}
}
#endif	/// DATA_LINK_IMPL_DATALINK_INFO_H_
/// === END OF FILE	================================================================================
