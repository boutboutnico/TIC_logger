/*
 * error.h
 *
 *  Created on: 4 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_FSM_DATASET_STATE_ERROR_H_
#define DATA_LINK_FSM_DATASET_STATE_ERROR_H_

/// === Includes	================================================================================

#include "../data_link_state.h"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Class Declarations	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class Error : public DataLinkState
{
	/// === Deleted Constructors	================================================================

	Error(const Error& _s) = delete;
	Error& operator=(const Error& _s) = delete;
	/// Move constructor ???
	/// Move assignment ???

public:
	/// === Public Declarations	====================================================================

	static DataLinkState& instance();

	virtual void marker_STX(DataLinkFSM& _fsm);
	virtual void marker_ETX(DataLinkFSM& _fsm);
	virtual void marker_LF(DataLinkFSM& _fsm);
	virtual void marker_CR(DataLinkFSM& _fsm);
	virtual void nextData(DataLinkFSM& _fsm, uint8_t _d);

protected:
	/// === Protected Declarations	================================================================

	Error();

	virtual void onEnter(DataLinkFSM& _fsm);
	virtual void onExit(DataLinkFSM& _fsm);

private:
	/// === Private Attributs	====================================================================
};

#pragma GCC diagnostic pop

/// === Inline Definitions	========================================================================
}
}
#endif	/// DATA_LINK_FSM_DATASET_STATE_ERROR_H_
/// === END OF FILE	================================================================================
