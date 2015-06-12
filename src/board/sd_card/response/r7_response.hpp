///
/// \file	r7_response.hpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_SD_CARD_RESPONSE_R7_RESPONSE_HPP_
#define APPLICATION_SD_CARD_RESPONSE_R7_RESPONSE_HPP_

/// === Includes	================================================================================

#include <cstdint>

#include "r1_response.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace sd_card
{
/// === Constants	================================================================================
/// === Class Declarations	========================================================================

class R7Response : public R1Response
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	/// --- Member Functions	--------------------------------------------------------------------

	R7Response();
	R7Response(const uint8_t _r1,const uint32_t _r7, const bool _is_com_success);

	R7Response(const R7Response &) = delete;
	R7Response & operator=(const R7Response &) = delete;

	R7Response(R7Response &&) = default;
	R7Response & operator=(R7Response &&) = default;

	/// --- Accessors	----------------------------------------------------------------------------

	inline uint8_t checkPattern() const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	uint32_t r7_;

};

/// === Inlines Declarations	====================================================================

inline uint8_t R7Response::checkPattern() const
{
	return r7_ & 0xFF;
}

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_RESPONSE_R7_RESPONSE_HPP_
/// === END OF FILE	================================================================================

