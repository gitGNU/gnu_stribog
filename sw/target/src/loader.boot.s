/*LPC213[2468] bootloader initialisation
Copyright (C) 2006, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This file is part of stribog

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
.set	mode_sv, 0x13
.set	i_bit, 0x80
.set	f_bit, 0x40
.text
.code 32
.align 0
reset: /*initialise stacks*/
	ldr	r0, stack_bot
	msr	CPSR_c, #i_bit|f_bit|mode_sv
	mov	sp, r0
	b	main
stack_bot:	.word	_arm_stack_bottom