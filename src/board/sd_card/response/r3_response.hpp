///
/// \file	r7_response.hpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_SD_CARD_RESPONSE_R3_RESPONSE_HPP_
#define APPLICATION_SD_CARD_RESPONSE_R3_RESPONSE_HPP_

/// === Includes	================================================================================

#include <cstdint>

#include "../sd_card_def.hpp"
#include "r1_response.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace sd_card
{
/// === Constants	================================================================================

const uint32_t cardCapacityStatus = 0x40000000;
const uint32_t cardPowerUpStatus = 0x80000000;

/// === Class Declarations	========================================================================

class R3Response : public R1Response
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// --- Member Functions	--------------------------------------------------------------------

	R3Response();
	R3Response(const uint8_t _r1, const uint32_t _r3, const bool _is_com_success);

	R3Response(const R3Response &) = delete;
	R3Response & operator=(const R3Response &) = delete;

	R3Response(R3Response &&) = default;
	R3Response & operator=(R3Response &&) = default;

	/// --- Accessors	----------------------------------------------------------------------------

	/// Card capacity status bit
	/// 1 if card is High Capacity SD Memory Card.
	/// 0 indicates that the card is Standard Capacity SD Memory Card.
	inline Capacity capacity() const;

	/// Card power up status bit, this status bit is set if the card power up procedure
	/// has been finished.
	inline bool isPowerUpFinished() const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	uint32_t r3_;

};

/// === Inlines Declarations	====================================================================

inline Capacity R3Response::capacity() const
{
	if (isPowerUpFinished() == true)
	{
		return (r3_ & cardCapacityStatus) ? Capacity::HIGH_CAPACITY : Capacity::STANDARD_CAPACITY;
	}
	else
	{
		return Capacity::ERROR;
	}
}

/// ------------------------------------------------------------------------------------------------

inline bool R3Response::isPowerUpFinished() const
{
	return (r3_ & cardPowerUpStatus) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_RESPONSE_R3_RESPONSE_HPP_
/// === END OF FILE	================================================================================

