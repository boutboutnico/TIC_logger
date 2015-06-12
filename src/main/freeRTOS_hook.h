///
/// \file	freeRTOS_hook.h
///	\brief	
///	\date	3 mars 2015
/// \author	nb_work
///
#ifndef FREERTOS_HOOK_H_
#define FREERTOS_HOOK_H_

/// === INCLUDES	============================================================================

#include "FreeRTOS.h"

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
#include "task.h"
#endif

/// === NAMESPACE	============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

#if ( configUSE_IDLE_HOOK > 0 )
  void
  vApplicationIdleHook (void);
#endif

#if  (configUSE_TICK_HOOK > 0)
  void
  vApplicationTickHook (void);
#endif

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
void
vApplicationStackOverflowHook (xTaskHandle pxTask, signed char *pcTaskName);
#endif

#if (configUSE_MALLOC_FAILED_HOOK > 0)
void
vApplicationMallocFailedHook (void);
#endif

#ifdef __cplusplus
}
#endif

/// === INLINE DEFINITIONS	====================================================================

#endif	/// FREERTOS_HOOK_H_
/// === END OF FILE	============================================================================
