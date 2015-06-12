///
/// \file	sd_card.hpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_SD_CARD_SD_CARD_HPP_
#define APPLICATION_SD_CARD_SD_CARD_HPP_

/// === Includes	================================================================================

#include "../board/drivers/sdcard_driver.hpp"
#include "sd_card_def.hpp"

/// === Namespaces	================================================================================

namespace board
{

namespace sd_card
{
/// === Forward Declarations	====================================================================

class R1Response;
class R2Response;
class R3Response;
class R7Response;

/// === Enumerations	============================================================================

/// TODO 	check at compilation time command, parameter and response compatibility
///			Use constexpr ?

enum class Command_e
	: uint8_t
	{
		CMD0 = 0,
	CMD8 = 8,
//	CMD9 = 9,
	CMD13 = 13,
	CMD16 = 16,
	CMD17 = 17,
	CMD24 = 24,
	ACMD41 = 41,
	CMD55 = 55,
	CMD58 = 58,
	CMD59 = 59,
};

/// === Class Declarations	========================================================================

class SDCard
{
public:
	/// === Constants	============================================================================

	static const uint8_t CMD_SIZE = 6;
	static const uint8_t RESP_SIZE = 6;
	static const uint8_t CHECK_PATTERN = 0xAA;

	/// === Public Declarations	====================================================================

	SDCard();

	bool initialize();

	/// CMD0
	R1Response go_Idle_State();

	/// CMD8
	R7Response send_IF_Cond(VHS _vhs, uint8_t _check_pattern);

	/// CMD9
//	R1Response send_CSD();

/// CMD13
	R2Response send_Status();

	/// CMD16
	R1Response set_BlockLen(uint32_t _block_len);

	/// CMD17
	R1Response read_Single_Block(uint32_t _addr, uint8_t* _buff, size_t _len);

	/// CMD24
	R1Response write_Block(uint32_t _addr, const uint8_t* _buff, size_t _len);

	/// CMD55
	R1Response app_Cmd();

	/// CMD58
	/// OCR Operation Conditions Register
	R3Response read_OCR();

	/// CMD59
	R1Response CRC_On_Off(bool _on);

	/// ACMD51
	R1Response SD_Send_OP_Cond(Capacity _hcs);

private:
	/// === Private Structures	====================================================================

	struct Argument_t
	{
		uint32_t val_;
		uint8_t pos_;
	};
	/// === Private Declarations	================================================================

	/// \brief	SD Card Physical Layer - 6.4.1.1 Power Up Time
	bool initalization_sequence();

	void clear();

	bool sendCommand(	Command_e _cmd_e,
						const Argument_t* _args,
						size_t _args_count,
						size_t _resp_len,
						bool _CS_stay_low = false);

	void constructCommand(Command_e _cmd_e, const Argument_t* _args, size_t _args_count);

	/// Command Response
	void waitNcr();

	/// Timing between Card Response to new Host Command
	void waitNrc();

	/// Card reponse Acknowledgment before Data Block
	void waitNac();

	uint8_t getCRC(Command_e _cmd_e, const uint8_t* _data, size_t _size);

	/// === Private Attributs	====================================================================

	board::mcu::SDCardDriver sdcard_driver_;
	uint8_t cmd_[CMD_SIZE];
	uint8_t resp_[RESP_SIZE];
};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_SD_CARD_HPP_
/// === END OF FILE	================================================================================
