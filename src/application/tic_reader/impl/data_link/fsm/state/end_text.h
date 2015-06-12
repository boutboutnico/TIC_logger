/*
 * wait_start_text.h
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_FSM_STATE_END_TEXT_H_
#define DATA_LINK_FSM_STATE_END_TEXT_H_

#include "../data_link_state.h"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

class EndText : public DataLinkState
{
	EndText(const EndText& _s) = delete;
	EndText& operator=(const EndText& _s) = delete;
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
	virtual void onEnter(DataLinkFSM& _fsm);
	EndText();
};

#pragma GCC diagnostic pop
}}
#endif /* DATA_LINK_FSM_STATE_END_TEXT_H_ */
