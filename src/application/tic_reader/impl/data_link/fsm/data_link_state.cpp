/*
 * data_link_state.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "data_link_state.h"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include "data_link_fsm.h"

/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================
/// === Protected Definitions	====================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void DataLinkState::onEnter(DataLinkFSM& _fsm)
{

}

/// ------------------------------------------------------------------------------------------------

void DataLinkState::onExit(DataLinkFSM& _fsm)
{

}

#pragma GCC diagnostic pop

/// ------------------------------------------------------------------------------------------------

void DataLinkState::setState(DataLinkFSM& _fsm, DataLinkState& _s)
{
	onExit(_fsm);

	_fsm.setState(_s);

	_s.onEnter(_fsm);
}

/// === END OF FILES	============================================================================
