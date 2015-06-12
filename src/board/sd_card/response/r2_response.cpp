///
/// \file	r2_response.cpp
///	\brief	
///	\date	04/052015
/// \author	nboutin
///

#include "r2_response.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================
/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================

R2Response::R2Response()
		: R1Response(), r2_(0)
{

}

R2Response::R2Response(const uint8_t _r1, const uint8_t _r2, const bool _is_com_success)
		: R1Response(_r1, _is_com_success), r2_(_r2)
{

}

/// === Private Definitions	========================================================================
/// === END OF FILE	================================================================================
