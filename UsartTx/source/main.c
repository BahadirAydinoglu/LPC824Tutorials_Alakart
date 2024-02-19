/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"

#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
volatile uint32_t g_systickCounter;

uint16_t sayi = 0;
char TxBuffer[32];

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* Enable clock of uart0. */
    CLOCK_EnableClock(kCLOCK_Uart0);
    /* Ser DIV of uart0. */
    CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 1U);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    PRINTF("hello world.\r\n");

    while (1)
    {
        sayi++;
        sprintf(TxBuffer, "Sayi: %u\r\n", sayi);
        USART_WriteBlocking(USART0, (uint8_t *)TxBuffer, sizeof(TxBuffer));
        PRINTF("%u\r\n", sayi * 10);

        // EXAMPLE_USARTSendToTerminal();
        SysTick_DelayTicks(1000);
    }
}
