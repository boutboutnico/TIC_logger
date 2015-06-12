/*
 * wait_start_text.cpp
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#include "end_text.h"
using namespace application::tic_reader;

/// === INCLUDES	================================================================================

//#include <iostream>

#include "../data_link_fsm.h"
#include "start_text.h"
#include "error.h"

/// === NAMESPACES	================================================================================

using namespace std;

/// === PUBLIC DEFINITIONS	========================================================================

DataLinkState& EndText::instance()
{
	static EndText instance;
	return instance;
}

/// ------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void EndText::marker_STX(DataLinkFSM& _fsm)
{
	setState(_fsm, StartText::instance());
}

/// ------------------------------------------------------------------------------------------------

void EndText::marker_ETX(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void EndText::marker_LF(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void EndText::marker_CR(DataLinkFSM& _fsm)
{
	setState(_fsm, Error::instance());
}

/// ------------------------------------------------------------------------------------------------

void EndText::nextData(DataLinkFSM& _fsm, uint8_t _d)
{
	setState(_fsm, Error::instance());
}

#pragma GCC diagnostic pop

/// === Protected Definitions	====================================================================

EndText::EndText()
{

}

/// ------------------------------------------------------------------------------------------------

void EndText::onEnter(DataLinkFSM& _fsm)
{
	_fsm.getInfo().incFrame();
}

/// === END OF FILES	============================================================================

