
// This program sets up SCTimer 0 to produce two counters.
// The counters are set to count at different periods (speeds).
//  See the description at the initial printout.
// The main() function simply configures the timer and does not do anything.

// Modified from NXP Xpresso_SDK, driver_examples 16bit_counter


#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_sctimer.h"

#include <stdbool.h>

#define MAX_UP_COUNTER_VALUE     (0xFFFFU * 256U)
#define MAX_UPDOWN_COUNTER_VALUE (0x1FFFFU * 256U)

static status_t SCTIMER_Calculate16BitCounterConfig(uint64_t rawCountValue,
                                                    uint8_t *prescale,
                                                    uint16_t *matchValue,
                                                    sctimer_event_active_direction_t *activeDir)
{
    status_t status = kStatus_Success;

    if (rawCountValue < MAX_UP_COUNTER_VALUE) {
      *prescale   = (uint8_t)(rawCountValue / 0xFFFFU);
      *matchValue = (uint16_t)(rawCountValue / (*prescale + 1U));
      *activeDir  = kSCTIMER_ActiveIndependent;
    } else if (rawCountValue < MAX_UPDOWN_COUNTER_VALUE) {
      *prescale   = (uint8_t)(rawCountValue / 0x1FFFFU);
      *matchValue = (uint16_t)(0x1FFFFU - rawCountValue / (*prescale + 1));
      *activeDir  = kSCTIMER_ActiveInCountDown;
    } else {
        status = kStatus_Fail;
    }
    return status;
}



int main(void) {
  
    sctimer_config_t sctimerInfo;
    uint32_t eventCounterL, eventCounterH;
    uint32_t sctimerClock;
    uint16_t matchValueL, matchValueH;
    sctimer_event_active_direction_t activeDirL, activeDirH;


    CLOCK_EnableClock(kCLOCK_Uart0);               // Enable clock of uart0.

    CLOCK_SetClkDivider(kCLOCK_DivUsartClk, 1U);   // Ser DIV of uart0.
 
    BOARD_InitBootPins();      // Init board pins,
    BOARD_InitBootClocks();    // Init clock
    BOARD_InitDebugConsole();  // Init debug console (PRINTF)


    CLOCK_EnableClock(kCLOCK_Sct);       // Enable clock of sct.

    sctimerClock = CLOCK_GetFreq(kCLOCK_Irc);

    // Print a note to terminal
    PRINTF("\r\nSCTimer in 16-bit mode.\r\n");
    PRINTF("\r\nBoth 16-bit counters run\n\r");
    PRINTF("and periodicaly toggle an output.\n\r\n\r");
    PRINTF("Counter 'L' runs at 0.1ms period and is connected to OUT2\n\r");
    PRINTF("OUT2 is connected to PIO0_27 using the SWM.\r\n");
    PRINTF("On Alakart, PIO0_27 is the Green LED.\n\r");
    PRINTF("Counter 'H' runs at 0.2ms period and is connected to OUT4\n\r");
    PRINTF("OUT4 is configured to connect to PIO0_16 using the SWM.\r\n");
    PRINTF("On Alakart, PIO0_16 is the Blue LED.\n\r");

    SCTIMER_GetDefaultConfig(&sctimerInfo);

#if defined(SCTIMER_NEED_CHANGE_CLOCK_SOURCE)     // Add judgement for change clock source
    sctimerInfo.clockMode   = DEMO_CLOCK_MODE;
    sctimerInfo.clockSelect = DEMO_CLOCK_SEL;
#endif

    // Switch to 16-bit mode.
    // If we want to use any 16-bit counter, be it the Low 16-bit or the High 16-bit
    //  we need to disable the Unify 32-bit Counter by hardware limit:
    sctimerInfo.enableCounterUnify = false;

    // Calculate prescaler, match value and active direction
    //  for the 16-bit LOW counter for 100ms interval:
    if (SCTIMER_Calculate16BitCounterConfig(MSEC_TO_COUNT(100U, sctimerClock),
					    &sctimerInfo.prescale_l,
					    &matchValueL,
                                            &activeDirL) == kStatus_Fail) {
      PRINTF("\r\nSCTimer 16-bit low counter is out of range\r\n");
      return -1;
    }
    
    // Calculate prescaler, match value and active direction
    //  for the 16-bit HIGH counter for 200ms interval:
    if (SCTIMER_Calculate16BitCounterConfig(MSEC_TO_COUNT(200U, sctimerClock),
					    &sctimerInfo.prescale_h,
					    &matchValueH,
                                            &activeDirH) == kStatus_Fail) {
      PRINTF("\r\nSCTimer 16-bit high counter is out of range\r\n");
      return -1;
    }
    
    // Enable bidirectional mode to extended 16-bit count range:
    if (activeDirL != kSCTIMER_ActiveIndependent){
      sctimerInfo.enableBidirection_l = true;
    }

    if (activeDirH != kSCTIMER_ActiveIndependent){
      sctimerInfo.enableBidirection_h = true;
    }

    // Initialize SCTimer module
    SCTIMER_Init(SCT0, &sctimerInfo);

    // Schedule a match event for the 16-bit low counter every 0.1 seconds
    if (SCTIMER_CreateAndScheduleEvent(SCT0,
				       kSCTIMER_MatchEventOnly,
				       matchValueL,
				       0,
				       kSCTIMER_Counter_L,
                                       &eventCounterL) == kStatus_Fail){
      return -1;
    }

    // Toggle first output when the 16-bit low counter event occurs:
    SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_2, eventCounterL);
    
    // Reset Counter L when the 16-bit low counter event occurs
    SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_L, eventCounterL);

    // Setup the 16-bit low counter event active direction
    SCTIMER_SetupEventActiveDirection(SCT0, activeDirL, eventCounterL);

    // Schedule a match event for the 16-bit high counter every 0.2 seconds
    if (SCTIMER_CreateAndScheduleEvent(SCT0,
				       kSCTIMER_MatchEventOnly,
				       matchValueH,
				       0,
				       kSCTIMER_Counter_H,
                                       &eventCounterH) == kStatus_Fail) {
      return -1;
    }

    // Setup the 16-bit high counter event active direction
    SCTIMER_SetupEventActiveDirection(SCT0, activeDirH, eventCounterH);

    // Toggle second output when the 16-bit high counter event occurs
    SCTIMER_SetupOutputToggleAction(SCT0, kSCTIMER_Out_4, eventCounterH);

    // Reset Counter H when the 16-bit high counter event occurs
    SCTIMER_SetupCounterLimitAction(SCT0, kSCTIMER_Counter_H, eventCounterH);

    // Start the 16-bit low and high counter
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L | kSCTIMER_Counter_H);

    while (1) {
      // SC Timer is doing all the work.
      // main() can simply do nothing.
    }
}
