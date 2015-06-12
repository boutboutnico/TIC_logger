///
/// \file	frame.h
///	\brief	
///	\date	2 avr. 2015
/// \author	nb_work
///
#ifndef DATA_LINK_FRAME_H_
#define DATA_LINK_FRAME_H_

/// === INCLUDES	================================================================================
/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{

/// === CLASS	====================================================================================
/// \class	
/// \brief
/// \date	2 avr. 2015
/// \author	nb_work

class Frame
{
public:
	/// === Public Constants	====================================================================

	static const uint8_t STX = 0x02;
	static const uint8_t ETX = 0x03;
};

/// === INLINE DEFINITIONS	========================================================================

}
}
#endif	/// DATA_LINK_FRAME_H_
/// === END OF FILE	================================================================================
