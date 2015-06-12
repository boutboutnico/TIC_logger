/// ================================================================================================
///
/// \file	carriage_return.hpp
/// \brief
/// \date	02/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef DATA_LINK_FSM_DATASET_STATE_CARRIAGE_RETURN_H_
#define DATA_LINK_FSM_DATASET_STATE_CARRIAGE_RETURN_H_

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

class CarriageReturn : public DataLinkState
{
public:
	/// === Public Declarations	====================================================================

	CarriageReturn(const CarriageReturn& _s) = delete;
	CarriageReturn& operator=(const CarriageReturn& _s) = delete;
	/// Move constructor ???
	/// Move assignment ???

	static DataLinkState& instance();

	virtual void marker_STX(DataLinkFSM& _fsm);
	virtual void marker_ETX(DataLinkFSM& _fsm);
	virtual void marker_LF(DataLinkFSM& _fsm);
	virtual void marker_CR(DataLinkFSM& _fsm);
	virtual void nextData(DataLinkFSM& _fsm, uint8_t _d);

protected:
	/// === Protected Declarations	================================================================

	virtual void onEnter(DataLinkFSM& _fsm);

	CarriageReturn();

private:
	/// === Private Declarations	================================================================

	void logDataSet(DataLinkFSM& _fsm);

	/// === Private Attributs	====================================================================

	bool b_checksum;
};

#pragma GCC diagnostic pop

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}
}
#endif	/// DATA_LINK_FSM_DATASET_STATE_CARRIAGE_RETURN_H_
/// === END OF FILE	================================================================================
