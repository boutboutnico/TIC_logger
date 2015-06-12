/*
 * frame_state.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "data.h"
using namespace application::tic_reader;

/// === INCLUDES	================================================================================

#include "../data_link_fsm.h"
#include "carriage_return.h"
#include "error.h"

/// === NAMESPACES	================================================================================

using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

DataLinkState& Data::instance()
{
	static Data instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void Data::marker_STX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void Data::marker_ETX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void Data::marker_LF(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void Data::marker_CR(DataLinkFSM& _fsm)
{
	setState(_fsm, CarriageReturn::instance());
}

/// ------------------------------------------------------------------------------------------------

void Data::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
//	_fsm.getData().add<uint8_t>(_d);
	_fsm.getData() += _d;
}

#pragma GCC diagnostic pop

/// === PRIVATE DEFINITIONS	========================================================================

Data::Data()
{

}

/// === END OF FILES	============================================================================

