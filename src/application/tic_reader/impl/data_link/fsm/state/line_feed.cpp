/*
 * frame_state.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "line_feed.h"
using namespace application::tic_reader;

/// === INCLUDES	================================================================================

//#include <iostream>

#include "../data_link_fsm.h"
#include "data.h"
#include "error.h"

/// === NAMESPACES	================================================================================

using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

DataLinkState& LineFeed::instance()
{
	static LineFeed instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void LineFeed::marker_STX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void LineFeed::marker_ETX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void LineFeed::marker_LF(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void LineFeed::marker_CR(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void LineFeed::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
	_fsm.getData().clear();
//	_fsm.getData().add<uint8_t>(_d);
	_fsm.getData() += _d;
	setState(_fsm, Data::instance());
}

#pragma GCC diagnostic pop

/// === PRIVATE DEFINITIONS	========================================================================

LineFeed::LineFeed()
{

}

/// === END OF FILES	============================================================================

