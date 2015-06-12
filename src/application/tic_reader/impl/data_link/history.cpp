/// ================================================================================================
///
/// \file	history.cpp
/// \brief
/// \date	11/05/2015
/// \author	nboutin
///
/// ================================================================================================

#include "history.hpp"
using namespace application::tic_reader;

/// === Includes	================================================================================

#include "logger/i_logger.hpp"
#include "diag/Trace.h"

/// === Namespaces	================================================================================

using namespace femtin;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

History::History(DataLinkInfo& _info)
		: api_ilogger_(NULL), info_(_info), datasets_standard_()
{
	datasets_standard_[0].setLabel(String<DataSet::LABEL_MAX_SIZE_>("ADSC"));
	datasets_standard_[1].setLabel(String<DataSet::LABEL_MAX_SIZE_>("VTIC"));
	datasets_standard_[2].setLabel(String<DataSet::LABEL_MAX_SIZE_>("DATE"));
	datasets_standard_[3].setLabel(String<DataSet::LABEL_MAX_SIZE_>("NGTF"));
	datasets_standard_[4].setLabel(String<DataSet::LABEL_MAX_SIZE_>("LTARF"));
	datasets_standard_[5].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EAST"));
	datasets_standard_[6].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF01"));
	datasets_standard_[7].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF02"));
	datasets_standard_[8].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF03"));
	datasets_standard_[9].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF04"));
	datasets_standard_[10].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF05"));
	datasets_standard_[11].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF06"));
	datasets_standard_[12].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF07"));
	datasets_standard_[13].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF08"));
	datasets_standard_[14].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF09"));
	datasets_standard_[15].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASF10"));
	datasets_standard_[16].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASD01"));
	datasets_standard_[17].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASD02"));
	datasets_standard_[18].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASD03"));
	datasets_standard_[19].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EASD04"));
	datasets_standard_[20].setLabel(String<DataSet::LABEL_MAX_SIZE_>("IRMS1"));
	datasets_standard_[21].setLabel(String<DataSet::LABEL_MAX_SIZE_>("URMS1"));
	datasets_standard_[22].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PREF"));
	datasets_standard_[23].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PCOUP"));
	datasets_standard_[24].setLabel(String<DataSet::LABEL_MAX_SIZE_>("SINSTS"));
	datasets_standard_[25].setLabel(String<DataSet::LABEL_MAX_SIZE_>("SMAXSN"));
	datasets_standard_[26].setLabel(String<DataSet::LABEL_MAX_SIZE_>("SMAXSN-1"));
	datasets_standard_[27].setLabel(String<DataSet::LABEL_MAX_SIZE_>("UMOY1"));
	datasets_standard_[28].setLabel(String<DataSet::LABEL_MAX_SIZE_>("STGE"));
	datasets_standard_[29].setLabel(String<DataSet::LABEL_MAX_SIZE_>("MSG1"));
	datasets_standard_[30].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PRM"));
	datasets_standard_[31].setLabel(String<DataSet::LABEL_MAX_SIZE_>("RELAIS"));
	datasets_standard_[32].setLabel(String<DataSet::LABEL_MAX_SIZE_>("NTARF"));
	datasets_standard_[33].setLabel(String<DataSet::LABEL_MAX_SIZE_>("NJOURF"));
	datasets_standard_[34].setLabel(String<DataSet::LABEL_MAX_SIZE_>("NJOURF+1"));
	datasets_standard_[35].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PJOURF+1"));

	datasets_historic_[0].setLabel(String<DataSet::LABEL_MAX_SIZE_>("ADCO"));
	datasets_historic_[1].setLabel(String<DataSet::LABEL_MAX_SIZE_>("OPTARIF"));
	datasets_historic_[2].setLabel(String<DataSet::LABEL_MAX_SIZE_>("ISOUSC"));
	datasets_historic_[3].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BASE"));
	datasets_historic_[4].setLabel(String<DataSet::LABEL_MAX_SIZE_>("HCHC"));
	datasets_historic_[5].setLabel(String<DataSet::LABEL_MAX_SIZE_>("HCHP"));
	datasets_historic_[6].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EJPHN"));
	datasets_historic_[7].setLabel(String<DataSet::LABEL_MAX_SIZE_>("EJPHM"));
	datasets_historic_[8].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHCJB"));
	datasets_historic_[9].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHPJB"));
	datasets_historic_[10].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHCJW"));
	datasets_historic_[11].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHPJW"));
	datasets_historic_[12].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHCJR"));
	datasets_historic_[13].setLabel(String<DataSet::LABEL_MAX_SIZE_>("BBRHPJR"));
	datasets_historic_[14].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PEJP"));
	datasets_historic_[15].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PTEC"));
	datasets_historic_[16].setLabel(String<DataSet::LABEL_MAX_SIZE_>("DEMAIN"));
	datasets_historic_[17].setLabel(String<DataSet::LABEL_MAX_SIZE_>("IINST"));
	datasets_historic_[18].setLabel(String<DataSet::LABEL_MAX_SIZE_>("ADPS"));
	datasets_historic_[19].setLabel(String<DataSet::LABEL_MAX_SIZE_>("IMAX"));
	datasets_historic_[20].setLabel(String<DataSet::LABEL_MAX_SIZE_>("PAPP"));
	datasets_historic_[21].setLabel(String<DataSet::LABEL_MAX_SIZE_>("HHPHC"));
	datasets_historic_[22].setLabel(String<DataSet::LABEL_MAX_SIZE_>("MOTDETAT"));
}

/// ------------------------------------------------------------------------------------------------

bool History::addDataSet(const femtin::String<DataSet::DATA_SET_MAX_SIZE_>& _str_dataset)
{
	bool b_result = false;
	DataSet dataset(_str_dataset, info_.getTICVersion());

	if (info_.getTICVersion() >= 2)
	{
		b_result = addDatasetStandard(dataset);
	}
	else if (info_.getTICVersion() == 1)
	{
		b_result = addDatasetHistoric(dataset);
	}
	else
	{
		return false;
	}

	/// Log it to memory
	if (b_result == true)
	{
		logger::dataset_t t_dataset;

		if (info_.getTICVersion() >= 2)
		{
			memcpy(t_dataset.file_name_, datasets_standard_[0].data().c_str(), 8);
		}
		else if (info_.getTICVersion() == 1)
		{
			memcpy(t_dataset.file_name_, datasets_historic_[0].data().c_str(), 8);
		}

		memcpy(&t_dataset.file_name_[8], ".txt", 5);

		memset(t_dataset.str_, 0x00, sizeof(char) * logger::dataset_t::size_);
		memcpy(t_dataset.str_, _str_dataset.c_str(), _str_dataset.size());

		api_ilogger_->log(t_dataset);
	}

	return b_result;
}

/// === Private Definitions	========================================================================

bool History::addDatasetStandard(const DataSet& _dataset)
{
	/// Wait for first ADSC label
	if (datasets_standard_[0].data().empty() == true)
	{
		if (_dataset.label() != datasets_standard_[0].label())
		{
			return false;
		}
	}

	/// Look for dataset
	size_t i = 0;
	for (; i < datasets_standard_.max_size(); i++)
	{
		if (datasets_standard_[i].label() == _dataset.label())
		{
			break;
		}
	}

	/// Not found ?
	if (i == datasets_standard_.max_size()) return false;

	/// Check for new data or timestamp
	if (datasets_standard_[i].checksum() != _dataset.checksum())
	{
		/// Update Data
		datasets_standard_[i].setData(_dataset.data());

		/// Update Timestamp
		if (_dataset.timestamp().isTimestamp() == true)
		{
			datasets_standard_[i].setTimestamp(_dataset.timestamp());
		}

		/// Update Checksum
		datasets_standard_[i].setChecksum(_dataset.checksum());

		return true;
	}

	return false;
}

/// ------------------------------------------------------------------------------------------------

bool History::addDatasetHistoric(const DataSet& _dataset)
{
	/// Wait for first ADCO label
	if (datasets_historic_[0].data().empty() == true)
	{
		if (_dataset.label() != datasets_historic_[0].label())
		{
			return false;
		}
	}

	/// Look for dataset
	size_t i = 0;
	for (; i < datasets_historic_.max_size(); i++)
	{
		if (datasets_historic_[i].label() == _dataset.label())
		{
			break;
		}
	}

	/// Not found ?
	if (i == datasets_historic_.max_size()) return false;

	/// Check for new data or timestamp
	if (datasets_historic_[i].checksum() != _dataset.checksum())
	{
		/// Update Data
		datasets_historic_[i].setData(_dataset.data());

		/// Update Checksum
		datasets_historic_[i].setChecksum(_dataset.checksum());

		return true;
	}

	return false;
}

/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
