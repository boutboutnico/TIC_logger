/*
 * wait_start_text.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "start_text.h"
using namespace application::tic_reader;

/// === INCLUDES	================================================================================

#include "../data_link_fsm.h"
#include "line_feed.h"
#include "error.h"

/// === NAMESPACES	================================================================================

using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

DataLinkState& StartText::instance()
{
	static StartText instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void StartText::marker_STX(DataLinkFSM& _fsm)
{
	/// Double start frame
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void StartText::marker_ETX(DataLinkFSM& _fsm)
{
	/// Empty frame
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void StartText::marker_LF(DataLinkFSM& _fsm)
{
	setState(_fsm, LineFeed::instance());
}

/// ------------------------------------------------------------------------------------------------

void StartText::marker_CR(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void StartText::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
	/// No start line
	setState(_fsm, Error::instance());
}

#pragma GCC diagnostic pop

/// === PRIVATE DEFINITIONS	========================================================================

StartText::StartText()
{

}

/// === END OF FILES	============================================================================
