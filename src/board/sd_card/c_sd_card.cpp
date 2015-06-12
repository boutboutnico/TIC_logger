///
/// \file	c_sd_card.cpp
///	\brief	
///	\date	23/04/2015
/// \author	nboutin
///

#include "sd_card.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================

#include "../chanN/FatFs/src/integer.h"
#include "../chanN/FatFs/src/diskio.h"

#include "response/r1_response.hpp"

/// === Namespaces	================================================================================
/// === Static	Instantiation	====================================================================

SDCard sdcard;

/// === Constants	================================================================================
/// === Public Definitions	========================================================================

extern "C" BYTE SDCard_initialize(void)
{
	return sdcard.initialize();
}

extern "C" BYTE SDCard_read_Single_Block(DWORD _addr, BYTE* _buff, UINT _len)
{
//	R1Response read_Single_Block(uint32_t _addr, uint8_t* _buff, size_t _len);

	R1Response r1 = sdcard.read_Single_Block(_addr, _buff, _len);

	return r1.isComSuccess();
}

extern "C" BYTE SDCard_write_Block(DWORD _addr, const BYTE* _buff, UINT _len)
{
	R1Response r1 = sdcard.write_Block(_addr, _buff, _len);

	return r1.isComSuccess();
}

/// ------------------------------------------------------------------------------------------------
/// === Private Definitions	========================================================================
/// ------------------------------------------------------------------------------------------------
/// === END OF FILE	================================================================================
