/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "fsl_common.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Clock rate on the CLKIN pin */
const uint32_t ExtClockIn = BOARD_EXTCLKINRATE;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
status_t BOARD_InitDebugConsole(void)
{
#if ((SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_SDK) || defined(SDK_DEBUGCONSOLE_UART))
    status_t result;
    CLOCK_EnableClock(kCLOCK_Uart0);               //Enable clock of uart0.
    CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 1U);   // Ser DIV of uart0.
    RESET_PeripheralReset(BOARD_DEBUG_USART_RST);
    result = DbgConsole_Init(BOARD_DEBUG_USART_INSTANCE, BOARD_DEBUG_USART_BAUDRATE, BOARD_DEBUG_USART_TYPE,
                             BOARD_DEBUG_USART_CLK_FREQ);
    assert(kStatus_Success == result);
    return result;
#else
    return kStatus_Success;
#endif
}
