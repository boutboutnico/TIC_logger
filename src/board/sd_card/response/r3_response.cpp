///
/// \file	r3_response.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///

#include "r3_response.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================
/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================

R3Response::R3Response()
		: R1Response(), r3_(0)
{

}

R3Response::R3Response(const uint8_t _r1, const uint32_t _r3, const bool _is_com_success)
		: R1Response(_r1, _is_com_success), r3_(_r3)
{

}

/// === Private Definitions	========================================================================
/// === END OF FILE	================================================================================
