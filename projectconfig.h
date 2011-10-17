/**************************************************************************/
/*! 
    @file     projectconfig.h
    @author   K. Townsend (microBuilder.eu)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2010, microBuilder SARL
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef _PROJECTCONFIG_H_
#define _PROJECTCONFIG_H_

#include "lpc134x.h"
#include "sysdefs.h"

/*=========================================================================
    BOARD SELECTION

    Because several boards use this code library with sometimes slightly
    different pin configuration, you will need to specify which board you
    are using by enabling one of the following definitions. The code base
    will then try to configure itself accordingly for that board.
    -----------------------------------------------------------------------*/
    #define CFG_BRD_LPC1343_REFDESIGN
    // #define CFG_BRD_LPC1343_TFTLCDSTANDALONE_USB
    // #define CFG_BRD_LPC1343_TFTLCDSTANDALONE_UART
    // #define CFG_BRD_LPC1343_802154USBSTICK
/*=========================================================================*/


/**************************************************************************
    PIN USAGE
    -----------------------------------------------------------------------
    This table tries to give an indication of which GPIO pins and 
    peripherals are used by the available drivers and SW examples.  Only
    dedicated GPIO pins available on the LPC1343 Reference Board are shown
    below.  Any unused peripheral blocks like I2C, SSP, ADC, etc., can
    also be used as GPIO if they are available.

                PORT 1        PORT 2                PORT 3 
                =========     =================     =======
                8 9 10 11     1 2 3 4 5 6 7 8 9     0 1 2 3

    SDCARD      . .  .  .     . . . . . . . . .     X . . .
    PWM         . X  .  .     . . . . . . . . .     . . . .
    STEPPER     . .  .  .     . . . . . . . . .     X X X X
    CHIBI       X X  X  .     . . . . . . . . .     . . . .
    ILI9325/8   X X  X  X     X X X X X X X X X     . . . X
    ST7565      X X  X  X     X X X X X X X X X     . . . X
    ST7735      . .  .  .     X X X X X X . . .     . . . .
    SHARPMEM    . .  .  .     X X X X . . . . .     . . . .
    SSD1306     . .  .  .     X X X . X X . . .     . . . .
    MCP121      . .  .  .     . . . . . . . . .     . X . .

                TIMERS                    SSP     ADC         UART
                ======================    ===     =======     ====
                16B0  16B1  32B0  32B1    0       0 1 2 3     0

    SDCARD      .     .     .     .       X       . . . .     .
    PWM         .     X     .     .       .       . . . .     .
    PMU [1]     .     .     X     .       .       . . . .     .
    USB         .     .     .     X       .       . . . .     .
    STEPPER     .     .     X     .       .       . . . .     .
    CHIBI       x     .     .     .       X       . . . .     .
    ILI9325/8   .     .     .     .       .       X X X X     .
    ST7565      .     .     .     .       .       X X X X     .
    ST7535      .     .     .     .       .       . . . .     .
    SHARPMEM    .     .     .     .       .       . . . .     .
    SSD1306     .     .     .     .       .       . . . .     .
    INTERFACE   .     .     .     .       .       . . . .     X[2]

    [1]  PMU uses 32-bit Timer 0 for SW wakeup from deep-sleep.  This timer
         can safely be used by other peripherals, but may need to be
         reconfigured when you wakeup from deep-sleep.
    [2]  INTERFACE can be configured to use either USBCDC or UART

 **************************************************************************/


/**************************************************************************
    I2C Addresses
    -----------------------------------------------------------------------
    The following addresses are used by the different I2C sensors included
    in the code base [1]

                                HEX       BINARY  
                                ====      ========
    ISL12022M (RTC)             0xDE      1101111x
    ISL12022M (SRAM)            0xAE      1010111x
    LM75B                       0x90      1001000x
    MCP24AA                     0xA0      1010000x
    MCP4725                     0xC0      1100000x
    TSL2561                     0x72      0111001x
    TCS3414                     0x72      0111001x

    [1]  Alternative addresses may exists, but the addresses listed in this
         table are the values used in the code base

 **************************************************************************/

/*=========================================================================
    CORE CPU SETTINGS
    -----------------------------------------------------------------------

    CFG_CPU_CCLK    Value is for reference only.  'core/cpu/cpu.c' must
                    be modified to change the clock speed, but the value
                    should be indicated here since CFG_CPU_CCLK is used by
                    other peripherals to determine timing.

    -----------------------------------------------------------------------*/
    #define CFG_CPU_CCLK                (72000000)  // 1 tick = 13.88nS
/*=========================================================================*/


/*=========================================================================
    SYSTICK TIMER
    -----------------------------------------------------------------------

    CFG_SYSTICK_DELAY_IN_MS   The number of milliseconds between each tick
                              of the systick timer.

    -----------------------------------------------------------------------*/
    #define CFG_SYSTICK_DELAY_IN_MS     (1)
/*=========================================================================*/


/*=========================================================================
    UART
    -----------------------------------------------------------------------

    CFG_UART_BAUDRATE         The default UART speed.  This value is used 
                              when initialising UART, and should be a 
                              standard value like 57600, 9600, etc.  
                              NOTE: This value may be overridden if
                              another value is stored in EEPROM!
    CFG_UART_BUFSIZE          The length in bytes of the UART RX FIFO. This
                              will determine the maximum number of received
                              characters to store in memory.

    -----------------------------------------------------------------------*/
    #define CFG_UART_BAUDRATE           (115200)
    #define CFG_UART_BUFSIZE            (512)
    
/*=========================================================================*/


/*=========================================================================
    SSP
    -----------------------------------------------------------------------

    CFG_SSP0_SCKPIN_2_11      Indicates which pin should be used for SCK0
    CFG_SSP0_SCKPIN_0_6

    -----------------------------------------------------------------------*/
    #define CFG_SSP0_SCKPIN_0_6
    
/*=========================================================================*/


/*=========================================================================
    ON-BOARD LED
    -----------------------------------------------------------------------

    CFG_LED_PORT              The port for the on board LED
    CFG_LED_PIN               The pin for the on board LED
    CFG_LED_ON                The pin state to turn the LED on (0 = low, 1 = high)
    CFG_LED_OFF               The pin state to turn the LED off (0 = low, 1 = high)

    -----------------------------------------------------------------------*/
    #define CFG_LED_PORT                (2)
    #define CFG_LED_PIN                 (10)
    #define CFG_LED_ON                  (0)
    #define CFG_LED_OFF                 (1)
    
/*=========================================================================*/


/*=========================================================================
    USB
    -----------------------------------------------------------------------

    CFG_USBHID                If this field is defined USB HID support will
                              be included.  Currently uses ROM-based USB HID
    CFG_USBCDC                If this field is defined USB CDC support will
                              be included, with the USB Serial Port speed
                              set to 115200 BPS by default
    CFG_USBCDC_BAUDRATE       The default TX/RX speed.  This value is used 
                              when initialising USBCDC, and should be a 
                              standard value like 57600, 9600, etc.
    CFG_USBCDC_INITTIMEOUT    The maximum delay in milliseconds to wait for
                              USB to connect.  Must be a multiple of 10!
    CFG_USBCDC_BUFFERSIZE     Size of the buffer (in bytes) that stores
                              printf data until it can be sent out in
                              64 byte frames.  The buffer is required since
                              only one frame per ms can be sent using USB
                              CDC (see 'puts' in systeminit.c).

    -----------------------------------------------------------------------*/
    #define CFG_USB_VID                   (0x239A)
    #define CFG_USB_PID                   (0x1002)

    // #define CFG_USBHID
    #define CFG_USBCDC
    #define CFG_USBCDC_BAUDRATE         (115200)
    #define CFG_USBCDC_INITTIMEOUT      (5000)
    #define CFG_USBCDC_BUFFERSIZE       (256)
    
/*=========================================================================*/


/*=========================================================================
    PRINTF REDIRECTION
    -----------------------------------------------------------------------

    CFG_PRINTF_UART           Will cause all printf statements to be 
                              redirected to UART
    CFG_PRINTF_USBCDC         Will cause all printf statements to be
                              redirect to USB Serial
    CFG_PRINTF_NEWLINE        This is typically "\r\n" for Windows or
                              "\n" for *nix

    Note: If no printf redirection definitions are present, all printf
    output will be ignored.
    -----------------------------------------------------------------------*/
	// #define CFG_PRINTF_UART
	#define CFG_PRINTF_USBCDC
	#define CFG_PRINTF_NEWLINE          "\r\n"
    
/*=========================================================================*/


/*=========================================================================
  CONFIG FILE VALIDATION
  -------------------------------------------------------------------------
  Basic error checking to make sure that incompatible defines are not 
  enabled at the same time, etc.

  =========================================================================*/

#if !defined CFG_BRD_LPC1343_REFDESIGN && !defined CFG_BRD_LPC1343_TFTLCDSTANDALONE_USB && !defined CFG_BRD_LPC1343_TFTLCDSTANDALONE_UART && !defined CFG_BRD_LPC1343_802154USBSTICK
  #error "You must defined a target board (CFG_BRD_LPC1343_REFDESIGN or CFG_BRD_LPC1343_TFTLCDSTANDALONE or CFG_BRD_LPC1343_TFTLCDSTANDALONE_UART or CFG_BRD_LPC1343_802154USBSTICK)"
#endif

#if defined CFG_PRINTF_USBCDC && defined CFG_PRINTF_UART
  #error "CFG_PRINTF_UART or CFG_PRINTF_USBCDC cannot both be defined at once"
#endif

#if defined CFG_PRINTF_USBCDC && !defined CFG_USBCDC
  #error "CFG_PRINTF_CDC requires CFG_USBCDC to be defined as well"
#endif

#if defined CFG_USBCDC && defined CFG_USBHID
  #error "Only one USB class can be defined at a time (CFG_USBCDC or CFG_USBHID)"
#endif

#if defined CFG_SSP0_SCKPIN_2_11 && defined CFG_SSP0_SCKPIN_0_6
  #error "Only one SCK pin can be defined at a time for SSP0"
#endif

#if !defined CFG_SSP0_SCKPIN_2_11 && !defined CFG_SSP0_SCKPIN_0_6
  #error "An SCK pin must be selected for SSP0 (CFG_SSP0_SCKPIN_2_11 or CFG_SSP0_SCKPIN_0_6)"
#endif

#endif
