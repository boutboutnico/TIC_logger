/// ================================================================================================
///
/// \file	data_set.cpp
/// \brief
/// \date	02/04/2015
/// \author	nboutin
///
/// ================================================================================================
#include "data_set.h"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include "diag/Trace.h"

/// === Namespaces	================================================================================

using namespace femtin;

/// === Public Definitions	========================================================================

DataSet::DataSet()
		: label_(), timestamp_(), data_(), checksum_(0)
{

}

/// ------------------------------------------------------------------------------------------------

DataSet::DataSet(const String<DataSet::DATA_SET_MAX_SIZE_>& _dataset, uint8_t _tic_version)
		: timestamp_(), checksum_(0)
{
	/// VTIC >= 02
	/// TIC Standard
	if (_tic_version >= 2)
	{
		size_t count = _dataset.count(HT);

		size_t pos_first = 0;
		size_t pos_last = _dataset.find(HT);

		label_ = _dataset.substr(0, pos_last);

		/// 3 HT means dataset contains timestamp
		if (count == 3)
		{
			pos_first = pos_last + 1;
			pos_last = _dataset.find(HT, pos_first);
			timestamp_ = _dataset.substr(pos_first, pos_last - pos_first);
		}

		pos_first = pos_last + 1;
		pos_last = _dataset.find(HT, pos_first);
		data_ = _dataset.substr(pos_first, pos_last - pos_first);

		pos_first = pos_last + 1;
		checksum_ = _dataset.c_str()[pos_first];
	}
	/// VTIC == 1
	/// TIC Historic
	else if (_tic_version == 1)
	{
		size_t pos_first = 0;
		size_t pos_last = _dataset.find(SP);

		label_ = _dataset.substr(0, pos_last);

		pos_first = pos_last + 1;
		pos_last = _dataset.find(SP, pos_first);
		data_ = _dataset.substr(pos_first, pos_last - pos_first);

		pos_first = pos_last + 1;
		checksum_ = _dataset.c_str()[pos_first];
	}
	else
	{
		trace_puts("[DataSet] !!! TIC VERSION !!!");
	}
}

/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
