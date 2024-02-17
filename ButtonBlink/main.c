/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define GLOBALPORT 0U
#define BLUE_LED_PIN 16U
#define BUTTON_PIN 12U

gpio_pin_config_t OutputConfig = {
    kGPIO_DigitalOutput,
    0,
};

gpio_pin_config_t InputConfig = {
    kGPIO_DigitalInput,
    0,
};

#define ButonRead() GPIO_PinRead(GPIO, GLOBALPORT, BUTTON_PIN)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
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

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init output LED GPIO. */

    GPIO_PortInit(GPIO, GLOBALPORT);
    GPIO_PinInit(GPIO, GLOBALPORT, BLUE_LED_PIN, &OutputConfig);
    GPIO_PinInit(GPIO, GLOBALPORT, BUTTON_PIN, &InputConfig);
    /* Board pin init */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();

    /* Set systick reload value to generate 1ms interrupt */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    while (1)
    {
        /* Delay 1000 ms */
        SysTick_DelayTicks(100U);
        if (ButonRead())
            GPIO_PinWrite(GPIO, GLOBALPORT, 1u << BLUE_LED_PIN, 1);
        else
            GPIO_PinWrite(GPIO, GLOBALPORT, 1u << BLUE_LED_PIN, 0);
    }
}
