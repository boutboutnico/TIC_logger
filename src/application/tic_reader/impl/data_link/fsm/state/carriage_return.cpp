/// ================================================================================================
///
/// \file	carriage_return.cpp
/// \brief
/// \date	02/04/2015
/// \author	nboutin
///
/// ================================================================================================

#include "carriage_return.h"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include "femtin/string.hpp"
#include "../data_link_fsm.h"
#include "line_feed.h"
#include "end_text.h"
#include "error.h"

/// === Namespaces	================================================================================

using namespace std;

/// === Public Definitions	========================================================================

DataLinkState& CarriageReturn::instance()
{
	static CarriageReturn instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void CarriageReturn::marker_STX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void CarriageReturn::marker_ETX(DataLinkFSM& _fsm)
{
	logDataSet(_fsm);

	setState(_fsm, EndText::instance());
}

/// ------------------------------------------------------------------------------------------------

void CarriageReturn::marker_LF(DataLinkFSM& _fsm)
{

	logDataSet(_fsm);

	setState(_fsm, LineFeed::instance());
}

/// ------------------------------------------------------------------------------------------------

void CarriageReturn::marker_CR(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void CarriageReturn::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
	setState(_fsm, Error::instance());
}

#pragma GCC diagnostic pop

/// === Protected Definitions	====================================================================

CarriageReturn::CarriageReturn()
		: b_checksum(false)
{

}

/// ------------------------------------------------------------------------------------------------

void CarriageReturn::onEnter(DataLinkFSM& _fsm)
{
	b_checksum = false;

	_fsm.getInfo().incLine();

	/// Current TIC version is known
	if (_fsm.getInfo().getTICVersion() != 0)
	{
		if (DataSet::checkChecksum(_fsm.getData(), _fsm.getInfo().getTICVersion()) == true)
		{
			b_checksum = true;
		}
		else
		{
			/// Checksum error
			_fsm.getInfo().incChecksumError();
		}
	}
	/// TIC Version detection
	else
	{
		/// Is TIC historic
		if (DataSet::checkChecksum(_fsm.getData(), 1) == true)
		{
			b_checksum = true;
			_fsm.getInfo().setTICVersion(1);
		}
		else if (DataSet::checkChecksum(_fsm.getData(), 2) == true)
		{
			b_checksum = true;
			_fsm.getInfo().setTICVersion(2);
		}
	}
}

/// === Private Definitions	========================================================================

void CarriageReturn::logDataSet(DataLinkFSM& _fsm)
{
	if (b_checksum == true)
	{
		_fsm.getHistory().addDataSet(_fsm.getData());
	}
	else
	{
		volatile uint8_t stop = 0;
		stop++;
	}
}

/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
