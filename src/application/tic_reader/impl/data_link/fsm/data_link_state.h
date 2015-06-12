/*
 * data_link_state.h
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_FSM_DATA_LINK_STATE_H_
#define DATA_LINK_FSM_DATA_LINK_STATE_H_

/// === Includes	================================================================================

#include <cstdint>

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Forward Declarations	====================================================================

class DataLinkFSM;

/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class DataLinkState
{
	/// === Friend Declarations	====================================================================

	friend class DataLinkFSM;

public:
	/// === Public Declarations	====================================================================

	virtual void marker_STX(DataLinkFSM& _fsm) = 0;
	virtual void marker_ETX(DataLinkFSM& _fsm) = 0;
	virtual void marker_LF(DataLinkFSM& _fsm) = 0;
	virtual void marker_CR(DataLinkFSM& _fsm) = 0;
	virtual void nextData(DataLinkFSM& _fsm, uint8_t _d) = 0;

protected:
	/// === Protected Declarations	================================================================

	virtual void onEnter(DataLinkFSM& _fsm);
	virtual void onExit(DataLinkFSM& _fsm);

	void setState(DataLinkFSM& _fsm, DataLinkState& _s);
};

#pragma GCC diagnostic pop
}
}
#endif	/// DATA_LINK_FSM_DATA_LINK_STATE_H_
/// === END OF FILE	================================================================================
