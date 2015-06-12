/*
 Femtin V0.0.1 - Copyright (C) 2015 Nicolas Boutin.
 All rights reserved

 This file is part of the Femtin distribution.

 Femtin is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License (version 2) as published by the
 Free Software Foundation.

 Femtin is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.
 */

/// ================================================================================================
///
/// \file	trace.hpp
/// \brief
/// \date	dd/mm/yyyy
/// \author	nboutin
///
/// ================================================================================================
#ifndef FOLDER_TEMPLATE_HPP_
#define FOLDER_TEMPLATE_HPP_

/// === Includes	================================================================================
/// === Namespaces	================================================================================

namespace application
{

namespace trace
{

void trace_initialize();
void trace_putc(const char _c);
void trace_puts(const char* _s);
void trace_printf(const char* format, ...);

/// ------------------------------------------------------------------------------------------------
}/// name
}    /// sub_name

#endif	/// FOLDER_TEMPLATE_HPP_
/// === END OF FILE	================================================================================
