///
/// \file	sd_card_def.hpp
///	\brief	
///	\date	17 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_SD_CARD_SD_CARD_DEF_HPP_
#define APPLICATION_SD_CARD_SD_CARD_DEF_HPP_

/// === Namespaces	================================================================================

namespace board
{

namespace sd_card
{

/// === Enumerations	============================================================================

enum class VHS
	: uint8_t
	{
		NOT_DEFINED = 0x00,
	VOLTAGE_2_7V_3_6V = 0x01,
	RESERVED_LOW_VOLTAGE_RANGE = 0x02,
};

/// ------------------------------------------------------------------------------------------------

enum class Capacity
	: uint8_t
	{
		STANDARD_CAPACITY = 0,
	HIGH_CAPACITY = 1,
	ERROR,
};

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_SD_CARD_DEF_HPP_
/// === END OF FILE	================================================================================
