///
/// \file	timestamp.h
///	\brief	
///	\date	2 avr. 2015
/// \author	nb_work
///
#ifndef DATA_LINK_TIMESTAMP_H_
#define DATA_LINK_TIMESTAMP_H_

/// === Includes	================================================================================

#include "femtin/string.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Class Declarations	========================================================================

class Timestamp
{
public:
	/// === Public Constants	====================================================================

	static const uint8_t TIMESTAMP_MAX_SIZE_ = 13;

	/// === Public Declarations	====================================================================

	Timestamp()
	 : str_()
	{
	}

	template<size_t L>
	Timestamp& operator=(const femtin::String<L>& _s)
	{
		str_ = _s;
		return *this;
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline bool isTimestamp() const
	{
		return (str_.empty() == true) ? false : true;
	}

	inline const femtin::String<TIMESTAMP_MAX_SIZE_>& str() const
	{
		return str_;
	}

private:
	/// === Private Attributs	====================================================================

	femtin::String<TIMESTAMP_MAX_SIZE_> str_;

};

/// === Inline Definitions	========================================================================

/// ------------------------------------------------------------------------------------------------
}/// tic_reader
}    /// application
#endif	/// DATA_LINK_TIMESTAMP_H_
/// === END OF FILE	================================================================================
