///
/// \file	r1_response.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///

#include "r1_response.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================
/// === Namespaces	================================================================================
/// === Public Definitions	========================================================================

R1Response::R1Response()
		: r1_(0), is_com_success_(false)
{

}

R1Response::R1Response(const uint8_t _val, const bool _is_com_success)
		: r1_(_val), is_com_success_(_is_com_success)
{

}

/// === Private Definitions	========================================================================
/// === END OF FILE	================================================================================
