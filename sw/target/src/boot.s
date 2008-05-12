/*LPC213[2468] boot program
Copyright (C) 2006, 2008\
 D.Ineiev <ineiev@yahoo.co.uk>, super V 93

This file has been written for the stribog project.

stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
.set	mode_usr, 0x10
.set	mode_fiq, 0x11
.set	mode_irq, 0x12
.set	mode_sv, 0x13
.set	mode_abt, 0x17
.set	mode_un, 0x1B
.set	mode_sys, 0x1F
.set	i_bit, 0x80
.set	f_bit, 0x40
.set	un_stack, 0
.set	ab_stack, 0
.set	fiq_stack, 0
.set	irq_stack, 0x400
.set	sv_stack, 0x40
.text
.code 32
.align 0
reset:/*test whether the program runs from RAM*/
	mov	r8,#4
	tst	pc,r8,lsl #28
/*remap the vectors for RAM-based programs*/
	movne	r8,#2
	ldrne	r9,memmap
	strne	r8,[r9]
/*load initialized data from ROM:
when the program is linked to be loaded
via LPC2138 bootstrap loader into RAM,
 _rom_data_begin = _rom_data_end
when the program is to be loaded from ROM into RAM
and then executed, the range
 [_rom_data_begin.._rom_data_end]
contains both the data and the application code*/
	ldr	r7,rom_begin
	ldr	r6,rom_end
	ldr	r8,ram_begin
init_data:
	cmp	r7,r6
	ldmmiia	r7!,{r9,r10,r11,r12}
	stmmiia	r8!,{r9,r10,r11,r12}
	bmi	init_data
	/*clear uninitialized memory*/
	ldr	r7,bss_begin
	ldr	r8,bss_end
	mov	r9,#0
	mov	r10,r9
	mov	r11,r9
	mov	r12,r9
clr_bss:cmp	r7,r8
	stmmiia	r7!,{r9,r10,r11,r12}
	bmi	clr_bss
	/*initialize stacks*/
	ldr	r0, stack_bot
	msr	CPSR_c, #i_bit|f_bit|mode_un
	mov	sp, r0
	sub	r0, r0, #un_stack
	msr	CPSR_c, #i_bit|f_bit|mode_abt
	mov	sp, r0
	sub	r0, r0, #ab_stack
	msr	CPSR_c, #i_bit|f_bit|mode_fiq
	mov	sp, r0
	sub	r0, r0, #fiq_stack
	msr	CPSR_c, #i_bit|f_bit|mode_irq
	mov	sp, r0
	sub	r0, r0, #irq_stack
	msr	CPSR_c, #i_bit|f_bit|mode_sv
	mov	sp, r0
/*	sub	r0, r0, #sv_stack
	msr	CPSR_c,	#i_bit|f_bit|mode_sys
	mov	sp, r0*/
	mov	fp,r9
	mov	r7,r9
	msr	CPSR_c,	#f_bit|mode_sv /*ineiev couldn't make LPC2138 
                                          interrupt in user mode*/
	ldr	pc,main_addr/*b main won't reach RAM from ROM*/
main_addr:	.word main
memmap:		.word	0xE01FC040
rom_begin:	.word	_rom_data_begin
rom_end:	.word	_rom_data_end
bss_begin:	.word	_bss_data_begin
bss_end:	.word	_bss_data_end
stack_bot:	.word	_arm_stack_bottom
ram_begin:	.word	_arm_ram_begin
.section .vectors
.code 32
.align 0
	ldr	pc,reset_addr
	ldr	pc,undef_addr
	ldr	pc,swi_addr
	ldr	pc,pabt_addr
	ldr	pc,dabt_addr
	nop
	ldr	pc,[pc,#-0xFF0]
	ldr	pc,fiq_addr
reset_addr:	.word reset
undef_addr:
swi_addr:
pabt_addr:
dabt_addr:
irq_addr:
fiq_addr:	.word loop	
loop:	b	./*this is an endless loop*/
.section .ramvectors /*these will be the RAM copy of vectors loaded from ROM*/
.code 32
.align 0
	ldr	pc,ram_reset_addr
	ldr	pc,ram_undef_addr
	ldr	pc,ram_swi_addr
	ldr	pc,ram_pabt_addr
	ldr	pc,ram_dabt_addr
	nop
	ldr	pc,[pc,#-0xFF0]
	ldr	pc,ram_fiq_addr
ram_reset_addr:	.word reset
ram_undef_addr:
ram_swi_addr:
ram_pabt_addr:
ram_dabt_addr:
ram_irq_addr:
ram_fiq_addr:	.word loop	
