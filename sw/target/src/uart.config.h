/*header to compile-time configure LPC2138 uarts
Copyright (C) 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This file is a part of stribog.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/

/*In the original configuration uart1 is connected to
host PC while uart0 gets data from GPS and odometer
when SWAP_UARTS is defined the uarts are swapped.
the non-swapped mode is useful when we need
writing the measurements from the very beginning;
the swapped is more convenient when we have got a GPS
and don't want to change the connections*/
#if HAVE_CONFIG_H
 #include<config.h>
#else
 #define SWAP_UARTS	(1)
#endif
#if !SWAP_UARTS
 #define UIIR_0 U0IIR
 #define UIER_0 U0IER
 #define ULSR_0 U0LSR
 #define UTHR_0 U0THR
 #define URBR_0 U0RBR
 #define ULCR_0 U0LCR
 #define UDLL_0 U0DLL
 #define UDLM_0 U0DLM
 #define UFCR_0 U0FCR
 #define VIC_UART_0 VIC_UART0
 #define SELECT_PIN_0 PINSEL0=(PINSEL0&PINSEL0_TXD0MASK&PINSEL0_RXD0MASK)\
   |PINSEL0_TXD0|PINSEL0_RXD0
 #define SELECT_LOADER_PIN SELECT_PIN_0
 #define SELECT_UART_0_PIN
 #define UIIR_1 U1IIR
 #define UIER_1 U1IER
 #define ULSR_1 U1LSR
 #define UTHR_1 U1THR
 #define URBR_1 U1RBR
 #define ULCR_1 U1LCR
 #define UDLL_1 U1DLL
 #define UDLM_1 U1DLM
 #define UFCR_1 U1FCR
 #define VIC_UART_1 VIC_UART1
 #define SELECT_PIN_1 PINSEL0=(PINSEL0&PINSEL0_TXD1MASK&PINSEL0_RXD1MASK)\
   |PINSEL0_TXD1|PINSEL0_RXD1
#else
 #define UIIR_0 U1IIR
 #define UIER_0 U1IER
 #define ULSR_0 U1LSR
 #define UTHR_0 U1THR
 #define URBR_0 U1RBR
 #define ULCR_0 U1LCR
 #define UDLL_0 U1DLL
 #define UDLM_0 U1DLM
 #define UFCR_0 U1FCR
 #define VIC_UART_0 VIC_UART1
 #define SELECT_PIN_0 PINSEL0=(PINSEL0&PINSEL0_TXD1MASK&PINSEL0_RXD1MASK)\
   |PINSEL0_TXD1|PINSEL0_RXD1
 #define UIIR_1 U0IIR
 #define UIER_1 U0IER
 #define ULSR_1 U0LSR
 #define UTHR_1 U0THR
 #define URBR_1 U0RBR
 #define ULCR_1 U0LCR
 #define UDLL_1 U0DLL
 #define UDLM_1 U0DLM
 #define UFCR_1 U0FCR
 #define VIC_UART_1 VIC_UART0
 #define SELECT_PIN_1 PINSEL0=(PINSEL0&PINSEL0_TXD0MASK&PINSEL0_RXD0MASK)\
   |PINSEL0_TXD0|PINSEL0_RXD0
 #define SELECT_LOADER_PIN SELECT_PIN_1
 #define SELECT_UART_0_PIN SELECT_PIN_0
#endif
