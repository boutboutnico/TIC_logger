///
/// \file	sd_card.cpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_worked
///

#include "sd_card.hpp"
using namespace board::sd_card;

/// === Includes	================================================================================

#include <cstring>
#include <assert.h>

#include "femtin/crc/crc7.hpp"

#include "response/r1_response.hpp"
#include "response/r2_response.hpp"
#include "response/r3_response.hpp"
#include "response/r7_response.hpp"

#include "diag/Trace.h"

/// === Namespaces	================================================================================

/// === Constants	================================================================================

const uint8_t CMD_MASK = 0x40;

const uint8_t CMD0_CRC = 0x95;
const uint8_t CMD55_CRC = 0x65;
const uint8_t CMD58_CRC = 0xFD;

const size_t CMD0_RESP_SIZE = 1;
const size_t CMD8_RESP_SIZE = 5;
const size_t CMD17_RESP_SIZE = 1;
const size_t CMD24_RESP_SIZE = 1;
const size_t CMD55_RESP_SIZE = 1;
const size_t CMD58_RESP_SIZE = 5;
const size_t CMD59_RESP_SIZE = 1;
const size_t ACMD41_RESP_SIZE = 1;

/// === Tools	====================================================================================

///// uint8_t u8[] = {0x01, 0x23, 0x45, 0x67};
///// uint32_t = 0x01234567;
/// TODO use template
uint32_t convert32(uint8_t* _val);
uint32_t convert32(uint8_t* _val)
{
	uint32_t result = 0;
	result |= (_val[3] << 0);
	result |= (_val[2] << 8);
	result |= (_val[1] << 16);
	result |= (_val[0] << 24);

	return result;
}

/// === Public Definitions	========================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

SDCard::SDCard()
{
	clear();

//	initialize();
}

/// ------------------------------------------------------------------------------------------------

bool SDCard::initialize()
{
	/// Wake up SD Card
	bool b_result = initalization_sequence();
	assert(b_result);

	/// Switch SD Card to SPI Mode
	R1Response r1 = go_Idle_State();
//	assert(r1.isComSuccess() && r1.isIdleState());
	if (r1.isComSuccess() == true)
	{
		if (r1.isIdleState() == false)
		{
			/// Already in SPI Mode
			return true;
		}
	}

	/// Verify SD Memory Card interface operating condition
	R7Response r7;

	do
	{
		r7 = send_IF_Cond(VHS::VOLTAGE_2_7V_3_6V, CHECK_PATTERN);
	}
	while (r7.checkPattern() != CHECK_PATTERN);

//	assert(r7.checkPattern() == CHECK_PATTERN);
	assert(r7.isIllegalCommand() == false);

	/// Check Voltage Range
	R3Response r3 = read_OCR();

	/// Start initialization and to check if the card has completed initialization.
	do
	{
		r1 = SD_Send_OP_Cond(Capacity::HIGH_CAPACITY);
	}
	while (r1.isIdleState() == true);

	/// Check Card capacity
	r3 = read_OCR();
//	assert(r3.capacity() == Capacity::STANDARD_CAPACITY);

	if (r3.capacity() == Capacity::STANDARD_CAPACITY)
	{
		trace_puts("Capacity::STANDARD_CAPACITY");
	}
	else if (r3.capacity() == Capacity::HIGH_CAPACITY)
	{
		trace_puts("Capacity::HIGH_CAPACITY");
	}
	else
	{
		return false;
	}

	/// Enable CRC
//	r1 = CRC_On_Off(true);	TODO CRC16 CCITT for read command...

	/// Change SPI Speed
	b_result = sdcard_driver_.speed(SPI_BAUDRATEPRESCALER_16);
	assert(b_result);

///// Set block length to 512 bytes
//	r1 = set_BlockLen(512);
//	assert(r1.r1() == 0);

	volatile uint8_t stop = 0;
	stop++;

	return b_result;
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::go_Idle_State()
{
	bool b_result = sendCommand(Command_e::CMD0, NULL, 0, R1Response::SIZE);

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R7Response SDCard::send_IF_Cond(VHS _vhs, uint8_t _check_pattern)
{
	Argument_t args[2] = { { static_cast<uint8_t>(_vhs), 8 }, { _check_pattern, 0 } };

	bool b_result = sendCommand(Command_e::CMD8, args, 2, CMD8_RESP_SIZE);

	return R7Response(resp_[0], convert32(&resp_[1]), b_result);
}

/// ------------------------------------------------------------------------------------------------

//R1Response SDCard::send_CSD()
//{
////	bool b_result = sendCommand(Command_e::CMD9, NULL, 0, R1Response::SIZE);
////
////	return R1Response(resp_[0], b_result);
//}

/// ------------------------------------------------------------------------------------------------

R2Response SDCard::send_Status()
{
	bool b_result = sendCommand(Command_e::CMD13, NULL, 0, R2Response::SIZE);

	return R2Response(resp_[0], resp_[1], b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::set_BlockLen(uint32_t _block_len)
{
	Argument_t args[1] = { { _block_len, 0 } };

	bool b_result = sendCommand(Command_e::CMD16, args, 1, R1Response::SIZE);

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::read_Single_Block(uint32_t _addr, uint8_t* _buff, size_t _len)
{
	/// --- Construct command

	Argument_t args[1] = { { _addr, 0 } };

	constructCommand(Command_e::CMD17, args, 1);

	/// --- Send command

	sdcard_driver_.CS_Low();

	bool b_result = sdcard_driver_.write(cmd_, CMD_SIZE);

	waitNcr();

	do
	{
		b_result &= sdcard_driver_.read(resp_, CMD17_RESP_SIZE);
	}
	while (resp_[0] != 0);

	do
	{
		b_result &= sdcard_driver_.read(resp_, CMD17_RESP_SIZE);
	}
	while (resp_[0] != 0xFE);

//	waitNrc();

//	waitNac();

	sdcard_driver_.read(_buff, _len);

	const size_t crc_len = 2;
	uint8_t crc[crc_len];
	sdcard_driver_.read(crc, crc_len);

	waitNrc();

///// Wait card is busy
//	uint8_t busy = 0;
//	do
//	{
//		b_result &= sdcard_driver_.read(&busy, 1);
//	}
//	while (busy == 0);

	sdcard_driver_.CS_High();

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::write_Block(uint32_t _addr, const uint8_t* _buff, size_t _len)
{
	/// --- Construct command

	Argument_t args[1] = { { _addr, 0 } };

	constructCommand(Command_e::CMD24, args, 1);

	/// --- Send command

	sdcard_driver_.CS_Low();

	bool b_result = sdcard_driver_.write(cmd_, CMD_SIZE);

//	waitNcr();

	do
	{
		b_result &= sdcard_driver_.read(resp_, CMD24_RESP_SIZE);
	}
	while (resp_[0] != 0);

//	sdcard_driver_.write(0xFF);
	sdcard_driver_.write(0xFE);

	sdcard_driver_.write(_buff, _len);

	uint8_t dummy[2] = { 0xFF, 0xFF };
	sdcard_driver_.write(dummy, 2);

	uint8_t resp = 0;
	b_result &= sdcard_driver_.read(&resp, 1);

	if ((resp & 0x1F) != 0x05)
	{
		b_result = false;
	}

	/// Wait card is busy
	uint8_t busy = 0;
	do
	{
		b_result &= sdcard_driver_.read(&busy, 1);
	}
	while (busy == 0);

	waitNrc();

	sdcard_driver_.CS_High();

	/// TODO remove ?
	send_Status();

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::app_Cmd()
{
	bool b_result = sendCommand(Command_e::CMD55, NULL, 0, CMD55_RESP_SIZE);

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R3Response SDCard::read_OCR()
{
	bool b_result = sendCommand(Command_e::CMD58, NULL, 0, CMD58_RESP_SIZE);

	return R3Response(resp_[0], convert32(&resp_[1]), b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::CRC_On_Off(bool _on)
{
	Argument_t args[1] = { { _on, 0 } };

	bool b_result = sendCommand(Command_e::CMD59, args, 1, CMD59_RESP_SIZE);

	return R1Response(resp_[0], b_result);
}

/// ------------------------------------------------------------------------------------------------

R1Response SDCard::SD_Send_OP_Cond(Capacity _hcs)
{
	app_Cmd();

	Argument_t args[1] = { { static_cast<uint8_t>(_hcs), 30 } };

	bool b_result = sendCommand(Command_e::ACMD41, args, 1, ACMD41_RESP_SIZE);

	return R1Response(resp_[0], b_result);
}

#pragma GCC diagnostic pop

/// === Private Definitions	========================================================================

bool SDCard::initalization_sequence()
{
	const size_t cmdFF_size = 10;
	uint8_t cmdFF[cmdFF_size] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	sdcard_driver_.CS_High();
	return sdcard_driver_.write(cmdFF, cmdFF_size);
}

/// ------------------------------------------------------------------------------------------------

void SDCard::clear()
{
	memset(cmd_, 0x00, sizeof(uint8_t) * CMD_SIZE);
	memset(resp_, 0xFF, sizeof(uint8_t) * RESP_SIZE);
}

/// ------------------------------------------------------------------------------------------------

bool SDCard::sendCommand(	Command_e _cmd_e,
							const Argument_t* _args,
							size_t _args_count,
							size_t _resp_len,
							bool _CS_stay_low)
{
	/// TODO mutex ?

	/// --- Construct command

	constructCommand(_cmd_e, _args, _args_count);

	/// --- Send command

	sdcard_driver_.CS_Low();

	bool b_result = sdcard_driver_.write(cmd_, CMD_SIZE);

	waitNcr();

	b_result &= sdcard_driver_.read(resp_, _resp_len);

	waitNrc();

	if (_CS_stay_low == false)
	{
		sdcard_driver_.CS_High();
	}

	return b_result;
}

void SDCard::constructCommand(Command_e _cmd_e, const Argument_t* _args, size_t _args_count)
{
	/// Clear Command and Response buffer
	clear();

	/// Set Start bit, Transmission bit and Command index
	cmd_[0] = CMD_MASK | static_cast<uint8_t>(_cmd_e);

	/// Set arguments
	/// TODO nullptr ?
	for (size_t i = 0; i < _args_count && _args != NULL; i++)
	{
		/// 0 <= pos_ <= 31
		assert(_args[i].pos_ < sizeof(_args[i].val_) * 8);

		uint32_t tmp = _args[i].val_ << _args[i].pos_;

		cmd_[4] |= static_cast<uint8_t>(tmp >> 0);
		cmd_[3] |= static_cast<uint8_t>(tmp >> 8);
		cmd_[2] |= static_cast<uint8_t>(tmp >> 16);
		cmd_[1] |= static_cast<uint8_t>(tmp >> 24);
	}

	/// Set CRC7 and End bit
	cmd_[5] = getCRC(_cmd_e, cmd_, CMD_SIZE - 1) | 0x01;
}

/// ------------------------------------------------------------------------------------------------

void SDCard::waitNcr()
{
	const size_t cmdNcr_size = 1;
	uint8_t cmdNcr = 0xFF;
	sdcard_driver_.write(&cmdNcr, cmdNcr_size);
}

void SDCard::waitNrc()
{
	const size_t cmdNrc_size = 1;
	uint8_t cmdNrc = 0xFF;
	sdcard_driver_.write(&cmdNrc, cmdNrc_size);
}

void SDCard::waitNac()
{
	const size_t cmdNac_size = 1;
	uint8_t cmdNac = 0xFF;
	sdcard_driver_.write(&cmdNac, cmdNac_size);
}

/// ------------------------------------------------------------------------------------------------

uint8_t SDCard::getCRC(Command_e _cmd_e, const uint8_t* _data, size_t _size)
{
	uint8_t crc = 0x00;

	switch (_cmd_e)
	{
	case Command_e::CMD0:
	{
		crc = CMD0_CRC;
		break;
	}

	case Command_e::CMD55:
	{
		crc = CMD55_CRC;
		break;
	}

	case Command_e::CMD58:
	{
		crc = CMD58_CRC;
		break;
	}

	case Command_e::CMD8:
	case Command_e::CMD13:
	case Command_e::CMD59:
	default:
	{
		crc = crc7::crc7(crc, _data, _size);
		break;
	}

	}

	return crc;
}

/// === END OF FILE	================================================================================
