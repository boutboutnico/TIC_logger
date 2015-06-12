/*
 * data_link.h
 *
 *  Created on: 2 avr. 2015
 *      Author: nboutin
 */

#ifndef DATA_LINK_DATA_LINK_H_
#define DATA_LINK_DATA_LINK_H_

/// === Includes	================================================================================

#include "fsm/data_link_fsm.h"
#include "datalink_info.h"
#include "history.hpp"

/// === Namespaces	================================================================================

namespace application
{

/// === Forward Declarations	====================================================================

namespace system_controller
{
class ComponentRegistry;
}

namespace tic_reader
{

/// === Class Declarations	========================================================================

class DataLink
{
public:
	/// Public Declarations	========================================================================

	DataLink()
			: info_(), history_(info_), fsm_(info_, history_)
	{
	}

	inline void link(application::system_controller::ComponentRegistry& _comp_registry)
	{
		history_.link(_comp_registry);
	}

	void nextData(uint8_t _d)
	{
		switch (_d)
		{
		case Frame::STX:
		{
			fsm_.marker_STX();
			break;
		}
		case Frame::ETX:
		{
			fsm_.marker_ETX();
			break;
		}
		case DataSet::LF:
		{
			fsm_.marker_LF();
			break;
		}
		case DataSet::CR:
		{
			fsm_.marker_CR();
			break;
		}
		default:
		{
			fsm_.nextData(_d);
			break;
		}
		}
	}

	inline const DataLinkInfo& getInfo()
	{
		return info_;
	}

	inline History& getHistory()
	{
		return history_;
	}

private:
	/// === Private Attributs	====================================================================

	DataLinkInfo info_;
	History history_;
	DataLinkFSM fsm_;

};
}
}
#endif /* DATA_LINK_DATA_LINK_H_ */
/// === END OF FILE	================================================================================
