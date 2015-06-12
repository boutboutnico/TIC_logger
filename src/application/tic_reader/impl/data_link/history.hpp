/// ================================================================================================
///
/// \file	history.hpp
/// \brief
/// \date	11/05/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef APPLICATION_TIC_READER_IMPL_DATA_LINK_HISTORY_HPP_
#define APPLICATION_TIC_READER_IMPL_DATA_LINK_HISTORY_HPP_

/// === Includes	================================================================================

#include "femtin/array.hpp"
#include "femtin/string.hpp"
#include "impl/data_set.h"

#include "system_controller/component_registry.hpp"
#include "datalink_info.h"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{
/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class History
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	History(DataLinkInfo& _info);

	inline void link(application::system_controller::ComponentRegistry& _comp_registry)
	{
		api_ilogger_ = _comp_registry.APILogger();
	}

	bool addDataSet(const femtin::String<DataSet::DATA_SET_MAX_SIZE_>& _str_dataset);

private:
	/// === Private Declarations	================================================================

	bool addDatasetStandard(const DataSet& _dataset);
	bool addDatasetHistoric(const DataSet& _dataset);

	/// === Private Attributes	====================================================================

	application::logger::ILogger* api_ilogger_;

	DataLinkInfo& info_;
	femtin::Array<DataSet, 36> datasets_standard_;
	femtin::Array<DataSet, 23> datasets_historic_;
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_TIC_READER_IMPL_DATA_LINK_HISTORY_HPP_
/// === END OF FILE	================================================================================
