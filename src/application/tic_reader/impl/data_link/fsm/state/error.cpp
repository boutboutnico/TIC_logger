/*
 * frame_state.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "error.h"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include "../data_link_fsm.h"
#include "line_feed.h"
#include "start_text.h"

/// === Namespaces	================================================================================

/// === Public Definitions	========================================================================

DataLinkState& Error::instance()
{
	static Error instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void Error::marker_STX(DataLinkFSM& _fsm)
{
	setState(_fsm, StartText::instance());
	_fsm.getInfo().incSuccessiveError();
}

/// ------------------------------------------------------------------------------------------------

void Error::marker_ETX(DataLinkFSM& _fsm)
{
	_fsm.getInfo().incSuccessiveError();
}

/// ------------------------------------------------------------------------------------------------

void Error::marker_LF(DataLinkFSM& _fsm)
{
	setState(_fsm, LineFeed::instance());
	_fsm.getInfo().incSuccessiveError();
}

/// ------------------------------------------------------------------------------------------------

void Error::marker_CR(DataLinkFSM& _fsm)
{
	_fsm.getInfo().incSuccessiveError();
}

/// ------------------------------------------------------------------------------------------------

void Error::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
	_fsm.getInfo().incSuccessiveError();
}

#pragma GCC diagnostic pop

/// === Protected Definitions	====================================================================

Error::Error()
{

}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void Error::onEnter(DataLinkFSM& _fsm)
{

}

/// ------------------------------------------------------------------------------------------------

void Error::onExit(DataLinkFSM& _fsm)
{
	_fsm.getInfo().resetSuccessiveError();
}

#pragma GCC diagnostic pop

/// ------------------------------------------------------------------------------------------------

/// === END OF FILES	============================================================================
