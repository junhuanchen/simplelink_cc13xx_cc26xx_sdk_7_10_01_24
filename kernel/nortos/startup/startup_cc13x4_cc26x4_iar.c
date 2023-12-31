/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//*****************************************************************************
//
// Check if compiler is IAR
//
//*****************************************************************************
#if !(defined(__IAR_SYSTEMS_ICC__))
    #error "startup_cc13x4_cc26x4_iar.c: Unsupported compiler!"
#endif

// We need intrinsic functions for IAR (if used in source code)
#include <intrinsics.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(driverlib/setup.h)
#include DeviceFamily_constructPath(driverlib/interrupt.h)

//*****************************************************************************
//
//! Forward declaration of the reset ISR and the default fault handlers.
//
//*****************************************************************************
static void nmiISR(void);
static void faultISR(void);
static void intDefaultHandler(void);
extern int main(void);
static void secureFaultHandler(void);

extern void MPUFaultIntHandler(void);
extern void BusFaultIntHandler(void);
extern void UsageFaultIntHandler(void);
extern void SVCallIntHandler(void);
extern void DebugMonIntHandler(void);
extern void PendSVIntHandler(void);
extern void SysTickIntHandler(void);
extern void GPIOIntHandler(void);
extern void I2C0IntHandler(void);
extern void RFCCPE1IntHandler(void);
extern void PKAIntHandler(void);
extern void AONRTCIntHandler(void);
extern void UART0IntHandler(void);
extern void AUXSWEvent0IntHandler(void);
extern void SSI0IntHandler(void);
extern void SSI1IntHandler(void);
extern void RFCCPE0IntHandler(void);
extern void RFCHardwareIntHandler(void);
extern void RFCCmdAckIntHandler(void);
extern void I2SIntHandler(void);
extern void AUXSWEvent1IntHandler(void);
extern void WatchdogIntHandler(void);
extern void Timer0AIntHandler(void);
extern void Timer0BIntHandler(void);
extern void Timer1AIntHandler(void);
extern void Timer1BIntHandler(void);
extern void Timer2AIntHandler(void);
extern void Timer2BIntHandler(void);
extern void Timer3AIntHandler(void);
extern void Timer3BIntHandler(void);
extern void CryptoIntHandler(void);
extern void uDMAIntHandler(void);
extern void uDMAErrIntHandler(void);
extern void FlashIntHandler(void);
extern void SWEvent0IntHandler(void);
extern void AUXCombEventIntHandler(void);
extern void AONProgIntHandler(void);
extern void DynProgIntHandler(void);
extern void AUXCompAIntHandler(void);
extern void AUXADCIntHandler(void);
extern void TRNGIntHandler(void);
extern void OSCIntHandler(void);
extern void AUXTimer2IntHandler(void);
extern void UART1IntHandler(void);
extern void BatMonIntHandler(void);
extern void SSI2IntHandler(void);
extern void SSI3IntHandler(void);
extern void UART2IntHandler(void);
extern void UART3IntHandler(void);
extern void I2C1IntHandler(void);
extern void SWEV1IntHandler(void);
extern void SWEV2IntHandler(void);
extern void SWEV3IntHandler(void);
extern void SWEV4IntHandler(void);

// Default interrupt handlers
#pragma weak MPUFaultIntHandler     = intDefaultHandler
#pragma weak BusFaultIntHandler     = intDefaultHandler
#pragma weak UsageFaultIntHandler   = intDefaultHandler
#pragma weak SVCallIntHandler       = intDefaultHandler
#pragma weak DebugMonIntHandler     = intDefaultHandler
#pragma weak PendSVIntHandler       = intDefaultHandler
#pragma weak SysTickIntHandler      = intDefaultHandler
#pragma weak GPIOIntHandler         = intDefaultHandler
#pragma weak I2C0IntHandler         = intDefaultHandler
#pragma weak RFCCPE1IntHandler      = intDefaultHandler
#pragma weak PKAIntHandler          = intDefaultHandler
#pragma weak AONRTCIntHandler       = intDefaultHandler
#pragma weak UART0IntHandler        = intDefaultHandler
#pragma weak AUXSWEvent0IntHandler  = intDefaultHandler
#pragma weak SSI0IntHandler         = intDefaultHandler
#pragma weak SSI1IntHandler         = intDefaultHandler
#pragma weak RFCCPE0IntHandler      = intDefaultHandler
#pragma weak RFCHardwareIntHandler  = intDefaultHandler
#pragma weak RFCCmdAckIntHandler    = intDefaultHandler
#pragma weak I2SIntHandler          = intDefaultHandler
#pragma weak AUXSWEvent1IntHandler  = intDefaultHandler
#pragma weak WatchdogIntHandler     = intDefaultHandler
#pragma weak Timer0AIntHandler      = intDefaultHandler
#pragma weak Timer0BIntHandler      = intDefaultHandler
#pragma weak Timer1AIntHandler      = intDefaultHandler
#pragma weak Timer1BIntHandler      = intDefaultHandler
#pragma weak Timer2AIntHandler      = intDefaultHandler
#pragma weak Timer2BIntHandler      = intDefaultHandler
#pragma weak Timer3AIntHandler      = intDefaultHandler
#pragma weak Timer3BIntHandler      = intDefaultHandler
#pragma weak CryptoIntHandler       = intDefaultHandler
#pragma weak uDMAIntHandler         = intDefaultHandler
#pragma weak uDMAErrIntHandler      = intDefaultHandler
#pragma weak FlashIntHandler        = intDefaultHandler
#pragma weak SWEvent0IntHandler     = intDefaultHandler
#pragma weak AUXCombEventIntHandler = intDefaultHandler
#pragma weak AONProgIntHandler      = intDefaultHandler
#pragma weak DynProgIntHandler      = intDefaultHandler
#pragma weak AUXCompAIntHandler     = intDefaultHandler
#pragma weak AUXADCIntHandler       = intDefaultHandler
#pragma weak TRNGIntHandler         = intDefaultHandler
#pragma weak OSCIntHandler          = intDefaultHandler
#pragma weak AUXTimer2IntHandler    = intDefaultHandler
#pragma weak UART1IntHandler        = intDefaultHandler
#pragma weak BatMonIntHandler       = intDefaultHandler
#pragma weak SSI2IntHandler         = intDefaultHandler
#pragma weak SSI3IntHandler         = intDefaultHandler
#pragma weak UART2IntHandler        = intDefaultHandler
#pragma weak UART3IntHandler        = intDefaultHandler
#pragma weak I2C1IntHandler         = intDefaultHandler
#pragma weak SWEV1IntHandler        = intDefaultHandler
#pragma weak SWEV2IntHandler        = intDefaultHandler
#pragma weak SWEV3IntHandler        = intDefaultHandler
#pragma weak SWEV4IntHandler        = intDefaultHandler

//*****************************************************************************
//
//! The entry point for the application startup code.
//
//*****************************************************************************
extern void __iar_program_start(void);
int localProgramStart(void);

//*****************************************************************************
//
//! Get stack start (highest address) symbol from linker file.
//
//*****************************************************************************
extern const void *STACK_TOP;

// It is required to place something in the CSTACK segment to get the stack
// check feature in IAR to work as expected
__root static void *dummy_stack @ ".stack";

//*****************************************************************************
//
//! The vector table. Note that the proper constructs must be placed on this to
//! ensure that it ends up at physical address 0x0000.0000 or at the start of
//! the program if located at a start address other than 0.
//
//*****************************************************************************
__root void (*const __vector_table[])(void) @ ".resetVecs" = {
    (void (*)(void)) & STACK_TOP, //  0 The initial stack pointer
    __iar_program_start,          //  1 The reset handler
    nmiISR,                       //  2 The NMI handler
    faultISR,                     //  3 The hard fault handler
    MPUFaultIntHandler,           //  4 The MPU fault handler
    BusFaultIntHandler,           //  5 The bus fault handler
    UsageFaultIntHandler,         //  6 The usage fault handler
    secureFaultHandler,           //  7 The secure fault handler
    0,                            //  8 Reserved
    0,                            //  9 Reserved
    0,                            // 10 Reserved
    SVCallIntHandler,             // 11 SVCall handler
    DebugMonIntHandler,           // 12 Debug monitor handler
    0,                            // 13 Reserved
    PendSVIntHandler,             // 14 The PendSV handler
    SysTickIntHandler,            // 15 The SysTick handler
    //--- External interrupts ---
    GPIOIntHandler,         // 16 AON edge detect
    I2C0IntHandler,         // 17 Interrupt event from I2C0
    RFCCPE1IntHandler,      // 18 RF Core Command & Packet Engine 1
    PKAIntHandler,          // 19 PKA Interrupt event
    AONRTCIntHandler,       // 20 AON RTC
    UART0IntHandler,        // 21 UART0 Rx and Tx
    AUXSWEvent0IntHandler,  // 22 AUX software event 0
    SSI0IntHandler,         // 23 SSI0 Rx and Tx
    SSI1IntHandler,         // 24 SSI1 Rx and Tx
    RFCCPE0IntHandler,      // 25 RF Core Command & Packet Engine 0
    RFCHardwareIntHandler,  // 26 RF Core Hardware
    RFCCmdAckIntHandler,    // 27 RF Core Command Acknowledge
    I2SIntHandler,          // 28 I2S
    AUXSWEvent1IntHandler,  // 29 AUX software event 1
    WatchdogIntHandler,     // 30 Watchdog timer
    Timer0AIntHandler,      // 31 Timer 0 subtimer A
    Timer0BIntHandler,      // 32 Timer 0 subtimer B
    Timer1AIntHandler,      // 33 Timer 1 subtimer A
    Timer1BIntHandler,      // 34 Timer 1 subtimer B
    Timer2AIntHandler,      // 35 Timer 2 subtimer A
    Timer2BIntHandler,      // 36 Timer 2 subtimer B
    Timer3AIntHandler,      // 37 Timer 3 subtimer A
    Timer3BIntHandler,      // 38 Timer 3 subtimer B
    CryptoIntHandler,       // 39 Crypto Core Result available
    uDMAIntHandler,         // 40 uDMA Software
    uDMAErrIntHandler,      // 41 uDMA Error
    FlashIntHandler,        // 42 Flash controller
    SWEvent0IntHandler,     // 43 Software Event 0
    AUXCombEventIntHandler, // 44 AUX combined event
    AONProgIntHandler,      // 45 AON programmable 0
    DynProgIntHandler,      // 46 Dynamic Programmable interrupt
                            //    source (Default: PRCM)
    AUXCompAIntHandler,     // 47 AUX Comparator A
    AUXADCIntHandler,       // 48 AUX ADC new sample or ADC DMA
                            //    done, ADC underflow, ADC overflow
    TRNGIntHandler,         // 49 TRNG event
    OSCIntHandler,          // 50 Combined event from Oscillator control
    AUXTimer2IntHandler,    // 51 AUX Timer2 event 0
    UART1IntHandler,        // 52 UART1 combined interrupt
    BatMonIntHandler,       // 53 Combined event from battery monitor
    SSI2IntHandler,         // 54 SSI2 combined interrupt
    SSI3IntHandler,         // 55 SSI3 combined interrupt
    UART2IntHandler,        // 56 UART2 combined interrupt
    UART3IntHandler,        // 57 UART3 combined interrupt
    I2C1IntHandler,         // 58 Interrupt event from I2C1
    SWEV1IntHandler,        // 59 Software callback event 1
    SWEV2IntHandler,        // 60 Software callback event 2
    SWEV3IntHandler,        // 61 Software callback event 3
    SWEV4IntHandler         // 62 Software callback event 4
};

//*****************************************************************************
//
// Perform early-boot device initialisation.
//
//*****************************************************************************
int localProgramStart(void)
{
    IntMasterDisable();

    //
    // Final trim of device
    //
    SetupTrimDevice();

    /*==================================*/
    /* Choose if segment initialization */
    /* should be done or not.           */
    /* Return: 0 to omit seg_init       */
    /*         1 to run seg_init        */
    /*==================================*/
    return 1;
}

//*****************************************************************************
//
// This function is called by __iar_program_start() early in the boot sequence.
//
//*****************************************************************************
int __low_level_init(void)
{
    /*
     *  Initialize the stack pointer and branch to localProgramStart().
     *  Some debuggers do not load the stack pointer from the reset vector.
     *  This code ensures that the stack pointer is initialized.
     *  The first entry of the vector table is the address of the stack.
     */
    __asm("    mov32 r0, __vector_table\n"
          "    ldr r0, [r0]\n"
          "    mov sp, r0\n"
          "    b localProgramStart");

    // This code is unreachable but the compiler expects a return statement
    return 1;
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives an NMI. This
//! simply enters an infinite loop, preserving the system state for examination
//! by a debugger.
//
//*****************************************************************************
static void nmiISR(void)
{
    //
    // Enter an infinite loop.
    //
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives a fault
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void faultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives a secure fault
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void secureFaultHandler(void)
{
    //
    // Enter an infinite loop.
    //
    while (1) {}
}

//*****************************************************************************
//
//! This is the code that gets called when the processor receives an unexpected
//! interrupt. This simply enters an infinite loop, preserving the system state
//! for examination by a debugger.
//
//*****************************************************************************
static void intDefaultHandler(void)
{
    //
    // Enter an infinite loop.
    //
    while (1) {}
}
