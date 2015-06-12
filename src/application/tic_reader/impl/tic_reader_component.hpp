///
/// \file	template.hpp
///	\brief	
///	\date	dd/mm/yyyy
/// \author	author
///
#ifndef APPLICATION_TIC_READER_IMPL_TIC_READER_COMPONENT_HPP_
#define APPLICATION_TIC_READER_IMPL_TIC_READER_COMPONENT_HPP_

/// === Includes	================================================================================

#include "system_controller/icomponent.hpp"

#include "tic_reader_service.hpp"
#include "tic_reader_task.hpp"

/// === Namespaces	================================================================================

namespace application
{

namespace tic_reader
{
/// === Forward Declarations	====================================================================
/// === Enumerations	============================================================================
/// === Class Declarations	========================================================================

class TICReaderComponent : public system_controller::IComponent
{
public:
	/// === Constants	============================================================================
	/// === Public Declarations	====================================================================

	TICReaderComponent();

	/// --- Component interface	--------------------------------------------------------------------

	virtual const femtin::String<COMPONENT_NAME_LEN_MAX>& name() const;

	virtual void* getAPIService();

	virtual bool initialize(system_controller::ComponentRegistry& _comp_reg);

	virtual bool start();

private:
	/// === Private Declarations	================================================================
	/// === Private Attributs	====================================================================

	TICReaderService service_;
	TICReaderTask task_;

};

/// === Inlines Declarations	====================================================================

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// APPLICATION_TIC_READER_IMPL_TIC_READER_COMPONENT_HPP_
/// === END OF FILE	================================================================================
