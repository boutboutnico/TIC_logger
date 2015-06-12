///
/// \file	r2_response.hpp
///	\brief	
///	\date	04/05/2015
/// \author	nboutin
///
#ifndef APPLICATION_SD_CARD_RESPONSE_R2_RESPONSE_HPP_
#define APPLICATION_SD_CARD_RESPONSE_R2_RESPONSE_HPP_

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

class R2Response : public R1Response
{
public:
	/// === Constants	============================================================================

	static const uint8_t SIZE = 2;

	/// === Public Declarations	====================================================================

	/// --- Member Functions	--------------------------------------------------------------------

	R2Response();
	R2Response(const uint8_t _r1, const uint8_t _r2, const bool _is_com_success);

	R2Response(const R2Response &) = delete;
	R2Response & operator=(const R2Response &) = delete;

	R2Response(R2Response &&) = default;
	R2Response & operator=(R2Response &&) = default;

	/// --- Accessors	----------------------------------------------------------------------------

	inline uint8_t r2() const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	uint8_t r2_;

};

/// === Inlines Declarations	====================================================================

inline uint8_t R2Response::r2() const
{
	return r2_;
}

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_RESPONSE_R3_RESPONSE_HPP_
/// === END OF FILE	================================================================================

