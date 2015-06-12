/*
 * data_link_fsm.h
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_FSM_DATA_LINK_FSM_H_
#define DATA_LINK_FSM_DATA_LINK_FSM_H_

/// === Includes	================================================================================

#include "../impl/frame.h"
#include "../impl/data_set.h"
#include "../datalink_info.h"
#include "../history.hpp"

#include "data_link_state.h"
#include "state/error.h"

/// === Namespaces	================================================================================

namespace application
{

/// === Forward Declarations	====================================================================

namespace tic_reader
{

/// === Class Declarations	========================================================================

class DataLinkFSM
{
	/// === Friend Declarations	====================================================================

	friend class DataLinkState;

public:
	/// === Public Declarations	====================================================================

	DataLinkFSM(DataLinkInfo& _info, History& _history)
			: current_state_(&Error::instance()), info_(_info), history_(_history), data_()
	{

	}

	/// --- Transitions	----------------------------------------------------------------------------

	inline void marker_STX()
	{
		current_state_->marker_STX(*this);
	}

	inline void marker_ETX()
	{
		current_state_->marker_ETX(*this);
	}

	inline void marker_LF()
	{
		current_state_->marker_LF(*this);
	}

	inline void marker_CR()
	{
		current_state_->marker_CR(*this);
	}

	inline void nextData(uint8_t _d)
	{
		current_state_->nextData(*this, _d);
	}

	/// --- Accessors	----------------------------------------------------------------------------

	inline femtin::String<DataSet::DATA_SET_MAX_SIZE_>& getData()
	{
		return data_;
	}

	inline DataLinkInfo& getInfo()
	{
		return info_;
	}

	inline History& getHistory()
	{
		return history_;
	}

private:
	/// === Private Declarations	================================================================

	inline void setState(DataLinkState& _s)
	{
		current_state_ = &_s;
	}

	/// === Private Attributs	====================================================================

	DataLinkState* current_state_;

	DataLinkInfo& info_;
	History& history_;

	femtin::String<DataSet::DATA_SET_MAX_SIZE_> data_;

};
}
}
#endif /* DATA_LINK_FSM_DATA_LINK_FSM_H_ */
/// === END OF FILE	================================================================================
