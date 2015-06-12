///
/// \file	r7_response.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///

#include "r7_response.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================
/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================

R7Response::R7Response()
		: R1Response(), r7_(0)
{

}

R7Response::R7Response(const uint8_t _r1, const uint32_t _r7, const bool _is_com_success)
		: R1Response(_r1, _is_com_success), r7_(_r7)
{

}

/// === Private Definitions	========================================================================
/// === END OF FILE	================================================================================
