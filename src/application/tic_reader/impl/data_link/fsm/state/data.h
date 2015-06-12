/*
 * frame_state.h
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_FSM_DATASET_STATE_DATA_H_
#define DATA_LINK_FSM_DATASET_STATE_DATA_H_

#include "../data_link_state.h"
#include "../../impl/data_set.h"
/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class Data : public DataLinkState
{
	Data(const Data& _s) = delete;
	Data& operator=(const Data& _s) = delete;
	/// Move constructor ???
	/// Move assignment ???

public:
	static DataLinkState& instance();

	virtual void marker_STX(DataLinkFSM& _fsm);
	virtual void marker_ETX(DataLinkFSM& _fsm);
	virtual void marker_LF(DataLinkFSM& _fsm);
	virtual void marker_CR(DataLinkFSM& _fsm);
	virtual void nextData(DataLinkFSM& _fsm, uint8_t _d);

protected:

	Data();

};

#pragma GCC diagnostic pop
}
}
#endif /* DATA_LINK_FSM_DATASET_STATE_DATA_H_ */
