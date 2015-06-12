///
/// \file	i_logger.hpp
///	\brief	
///	\date	27/04/2015
/// \author	nboutin
///
#ifndef APPLICATION_LOGGER_I_LOGGER_HPP_
#define APPLICATION_LOGGER_I_LOGGER_HPP_

/// === Includes	================================================================================

#include "femtin/array.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace logger
{

/// === Forward Declarations	====================================================================

/// === Structures	================================================================================

struct dataset_t
{
	char file_name_[8 + 1 + 3 + 1];	/// "filename.txt"
	static const size_t size_ = 128;
	char str_[size_];
};

/// === Class Declarations	========================================================================

class ILogger
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// TODO use serialize
	virtual bool log(const dataset_t& _dataset) = 0;

};

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_LOGGER_I_LOGGER_HPP_
/// === END OF FILE	================================================================================
