///
/// \file	r1_response.hpp
///	\brief	
///	\date	16 avr. 2015
/// \author	nb_work
///
#ifndef APPLICATION_SD_CARD_RESPONSE_R1_RESPONSE_HPP_
#define APPLICATION_SD_CARD_RESPONSE_R1_RESPONSE_HPP_

/// === Includes	================================================================================

#include <cstdint>

/// === Namespaces	================================================================================

namespace board
{

namespace sd_card
{
/// === Constants	================================================================================

const uint8_t inIdleState = 0x01;
const uint8_t eraseReset = 0x02;
const uint8_t illegalCommand = 0x04;
const uint8_t comCRCError = 0x08;
const uint8_t eraseSequenceError = 0x10;
const uint8_t addressError = 0x20;
const uint8_t parameterError = 0x40;

/// === Class Declarations	========================================================================

class R1Response
{
public:
	/// === Constants	============================================================================

	static const uint8_t SIZE = 1;

	/// === Public Declarations	====================================================================

	/// --- Member Functions	--------------------------------------------------------------------

	R1Response();
	R1Response(const uint8_t _val, const bool _is_com_success);

	R1Response(const R1Response &) = delete;
	R1Response & operator=(const R1Response &) = delete;

	R1Response(R1Response &&) = default;
	R1Response & operator=(R1Response &&) = default;

	/// --- Accessors	----------------------------------------------------------------------------

	inline uint8_t r1() const;

	/// \brief	SPI communication error
	inline bool isComSuccess() const;

	/// \brief	The card is in idle state and running the initializing process.
	inline bool isIdleState() const;

	/// \brief	An erase sequence was cleared before executing because an out of erase sequence
	///			command was received.
	inline bool isEraseSequenceCleared() const;

	/// \brief	An illegal command code was detected.
	inline bool isIllegalCommand() const;

	/// \brief	The CRC check of the last command failed.
	inline bool isCommunicationCRCError() const;

	/// \brief	Erase sequence error: An error in the sequence of erase commands occurred.
	inline bool isErrorInEraseSequence() const;

	/// \brief	Address error: A misaligned address that did not match the block length
	///			 was used in the command.
	inline bool isAddressError() const;

	/// \brief	Parameter error: The command's argument (e.g. address, block length) was outside
	///			the allowed range for this card.
	inline bool isParameterError() const;

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	uint8_t r1_;
	bool is_com_success_;
};

/// === Inlines Declarations	====================================================================

inline uint8_t R1Response::r1() const
{
	return r1_;
}

/// ------------------------------------------------------------------------------------------------

inline bool R1Response::isComSuccess() const
{
	return is_com_success_;
}

/// ------------------------------------------------------------------------------------------------

inline bool R1Response::isIdleState() const
{
	return (r1_ & inIdleState) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isEraseSequenceCleared() const
{
	return (r1_ & eraseReset) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isIllegalCommand() const
{
	return (r1_ & illegalCommand) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isCommunicationCRCError() const
{
	return (r1_ & comCRCError) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isErrorInEraseSequence() const
{
	return (r1_ & eraseSequenceError) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isAddressError() const
{
	return (r1_ & addressError) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
inline bool R1Response::isParameterError() const
{
	return (r1_ & parameterError) ? true : false;
}

/// ------------------------------------------------------------------------------------------------
}/// sd_card
}    /// application

#endif	/// APPLICATION_SD_CARD_RESPONSE_R1_RESPONSE_HPP_
/// === END OF FILE	================================================================================

