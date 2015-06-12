/// ================================================================================================
///
/// \file	data_set.hpp
/// \brief
/// \date	02/04/2015
/// \author	nboutin
///
/// ================================================================================================
#ifndef DATA_LINK_DATA_SET_H_
#define DATA_LINK_DATA_SET_H_

/// === Includes	================================================================================

#include "femtin/string.hpp"
#include "femtin/buffer.hpp"

#include "timestamp.h"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === Class Declarations	========================================================================

class DataSet
{
public:
	/// === Public Constants	====================================================================

	static const char LF = 0x0A;
	static const char CR = 0x0D;
	static const char HT = 0x09;
	static const char SP = 0x20;

	static const uint8_t LABEL_MAX_SIZE_ = 8;
	static const uint8_t DATA_MAX_SIZE_ = 98;
	static const uint8_t CHECKSUM_MAX_SIZE_ = 1;
	static const uint8_t CHECKSUM_MIN_ = 0x20;
	static const uint8_t CHECKSUM_MAX_ = 0x5F;
	static const uint8_t DATA_SET_MAX_SIZE_ = 3 + LABEL_MAX_SIZE_ + Timestamp::TIMESTAMP_MAX_SIZE_
												+ DATA_MAX_SIZE_ + CHECKSUM_MAX_SIZE_;

	/// === Public Declarations	====================================================================

	DataSet();

	DataSet(const femtin::String<DATA_SET_MAX_SIZE_>& _dataset, uint8_t _tic_version);

	/// --- Accessors	----------------------------------------------------------------------------

	const femtin::String<LABEL_MAX_SIZE_>& label() const
	{
		return label_;
	}

	void setLabel(const femtin::String<LABEL_MAX_SIZE_>& _s)
	{
		label_ = _s;
	}

	inline const Timestamp& timestamp() const
	{
		return timestamp_;
	}

	inline void setTimestamp(const Timestamp& _timestamp)
	{
		timestamp_ = _timestamp;
	}

	const femtin::String<DATA_MAX_SIZE_>& data() const
	{
		return data_;
	}

	void setData(const femtin::String<DATA_MAX_SIZE_>& _s)
	{
		data_ = _s;
	}

	inline char checksum() const
	{
		return checksum_;
	}

	inline void setChecksum(char _checksum)
	{
		checksum_ = _checksum;
	}

	/// --- Operations	----------------------------------------------------------------------------

	/// \brief	Checksum = (S1 & 0x3F) + 0x20
	template<size_t L>
	static bool checkChecksum(const femtin::String<L>& _str, uint8_t _tic_version)
	{
		uint32_t s1 = 0;

		size_t i = 0;
		for (; i < _str.size() - 1; i++)
		{
			s1 += _str[i];
		}

		if (_tic_version >= 2)
		{
			s1 = (s1 & 0x03F) + 0x20;
			return ((char) s1 == _str[i]) ? true : false;
		}
		else
		{
			s1 -= SP;
			s1 = (s1 & 0x03F) + 0x20;
			return ((char) s1 == _str[i]) ? true : false;
		}
	}

private:
	/// === Private Attributs	====================================================================

	femtin::String<LABEL_MAX_SIZE_> label_;
	Timestamp timestamp_;
	femtin::String<DATA_MAX_SIZE_> data_;
	char checksum_;
};

/// === Inline Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
}/// tic_reader
}    /// application
#endif	/// DATA_LINK_DATA_SET_H_
/// === END OF FILE	================================================================================
