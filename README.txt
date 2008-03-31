Stribog the sensing platform README file.

For license and copyright notes see 'copyright'.

ATTENTION stribog is in his alpha stage. he is not functional yet.

The project is located at http://savannah.nongnu.org/projects/stribog

SOME TECHNICAL NOTES FOLLOW

This project consists of hardware and software sections. the former is
developed with gEDA, the latter with GNU toolchains.

Hardware contains a 3-axis {magnetoresistive compass, accelerometer,
(optionally) gyroscope} and an ARM-based microcontroller to manage all.

Software includes programs for MCU to test and align hardware parts,
to perform the measurements; the software part also has some programs
for POSIX host to receive obtained data.

Stribog is primarily designed on LPC2138, but actually LPC213[46] can be used,
too. the only change will be in ld scripts (2138.ld and ram2138.ld), as shown 
in comments there.

The board will be programmed via serial port using bootstrap loader.
you can use any existing one (on Unix live 
lpc_host_tools by Holly Gates <hgates@eink.com>, 
lpc21isp by Martin Maurer <Martin.Maurer@clibb.de> 
 and Aeolus Development http://aeolusdevelopment.com
lpc2k_pgm by Paul Stoffregen (http://www.pjrc.com/arm/lpc2k_pgm)

on Windows they have Philips flash ISP utility)

If you use them, you'll have to adjust input files format (.hex, .srec 
and so on) with arm-elf-objcopy(1). I don't know precisely
how to do this.


I wrote my own host-side bootstrap loader (sw/host/elk) because
 1) some of those programs (like lpc21isp) lack clear terms of use,
 2) other (like Philips utility) are neither free nor capable to run 
    on a free OS,
 3) some (like lpc2k_pgm) have graphic user interface and I don't like this,
 4) I wouldn't add external dependencies when possible.

My tools are hardly functional, but they work somehow for me and they are free.

There are two linker scripts in sw/target/src directory: ram2138.ld and
2138.ld. the former is currently used (the program is to be just loaded into RAM
and run), the latter was tested some time ago and will be corrected again when 
stribog needs to keep his program in ROM.

The program is written in C (the ld scripts don't support C++). 
main() is executed in supervisor mode. no THUMB code. fast interrupt reserved. 
VPB divider equals 4, as by default. PLL is configured to multiply by 4.

The program will run from RAM, when possible. even when written in ROM, boot.s
will copy it to RAM. the program uses single library: libgcc.a. 
all computations should be in fixed point.

Busy VIC slots: 3 (timer0), 4 (timer1), 5 and 6 (ADC), 7 (UART1), 8 (UART0) 

Time functions (tempus.h) are based on timer1. it uses VIC vectored interrupt
slot 4. this module receives PPS at CAP1.2 (signal A), too.

UART0 is the auxiliary port to get GPS data; uses VIC slot 8

UART1 is the basic port; uses VIC slot 7

ADC use VIC slots 5 and 6; magnetic module functions used in such way
(see magex.c, multa.c) that ADC sampling frequency defines frequency of
set/reset pulses. this frequency is adjusted to be an integer of 50 Hz.

Magnetoresistive sensors work not so far from the absolute maximum value 
for set/reset strap duty cycle. carelessly increasing the sampling frequency 
can DAMAGE the sensors.

Timer0 is occupied by accelerometers; VIC slot 3

HOW TO INSTALL DEVELOPMENT TOOLS

First, we shall need binutils and gcc for ARM. we go to http://www.gnu.org and
get binutils and gcc. generally, we use the latest releases, though there is 
nothing dependent on any supernew features in stribog. currently we use 
binutils-2.18 with gcc-4.2.2. we used also binutils-2.17, binutils-2.16.1, 
binutils-2.16, gcc-3.4.6, gcc-4.0.1, gcc-4.0.3, gcc-4.1.1, gcc-4.1.2, gcc-4.2.2.
they should work, too.

binutils-2.15 don't work because their ld don't undestand expressions like
_arm_stack_bottom = ORIGIN(ram) + LENGTH(ram) - 4;
this has been fixed in 'trunc' branch of stribog.

Follow (with some changes) instructions from http://www.gnuarm.com
($ is for our shell prompt)
$ export armprefix=$HOME/arm
                   (or where you want them to live. you must have write access
		    thither)
$ gpg --verify binutils-2.18.tar.bz2.sig && tar xjf binutils-2.18.tar.bz2
$ mkdir bui;cd bui
$ ../binutils-2.18/configure --target=arm-elf --prefix=$armprefix --enable-interwork --enable-multilib
$ make all install
$ export PATH=$armprefix/bin:$PATH; rm -fr *;cd ..
         (add this path in your shell profile after install, too)
$ gpg --verify gcc-4.2.3.tar.bz2.sig && tar xjf gcc-4.2.3.tar.bz2;cd bui
$ ../gcc-4.2.3/configure --target=arm-elf --prefix=$armprefix --enable-interwork --enable-multilib --enable-languages=c --disable-libssp
$ make all install

That's all. we don't need newlib, and stribog main board has no contacts 
to connect with gdb.

This sequence worked on RedHat 7.3 and Fedora Core 4 (32-bit).
binutils-2.18 won't build themselves on RedHat 7.3 without slightly editing.

--disable-libssp is mandatory for gcc-4.1.2 and later
(currently up to gcc-4.3.0). otherwize the compiler
will not build itself.

gcc-4.3.0 have new dependency, MPFR. current version of MPFR, 2.3.1,
requires gmp-4.1 or later; RedHat 7.3 has gmp-4.0.1.
after you install MPFR at prefix=$PREFIX you'll probably need to add 
$PREFIX/lib to your LD_LIBRARY_PATH shell variable and append --with-mpfr=$PREFIX
to the command line configuring the gcc (e.g. after --disable-libssp)

Auxiliary targets (such as sw/auxilia/odo and sw/auxilia/coil) are based on
AVR. their target programs are built with avr-binutils, avr-gcc and avr-libc.
instructions how to build this toolchain can be found in avr-libc 
documentation. for historical reasons we use uisp to load programs into these 
processors. generally avrdude is much better. they all live in 
http://savannah.gnu.org

It is much more problematic to install gEDA and friends. you'll need them if
you want to edit the hardware part of stribog.

HOW TO USE GIT

GIT is the revision control system used by the project.

Here is a typical ~/.gitconfig file contents
(please replace the names and email with yours):
<<<EOF
[user]
 name = Ineiev (favourite host)
 email = ineiev@users.sourceforge.net
[core]
 editor = vim
EOF

If you are a maintainer, your usual spells are
(replace ineiev with your login name)

$ git clone ineiev@git.savannah.nongnu.org:/srv/git/stribog.git
 to get a new local repository

$ git remote add savannah ineiev@git.savannah.nongnu.org:/srv/git/stribog.git
 to add a reference for the public repository

$ git push savannah feb2008
 to push into savannah local branch named 'feb2008' 
 (non-existent will be created)

$ git push savannah
 to push into savannah all local branches

$ git push savannah :refs/heads/feb2008
 to remove branch feb2008 from remote savannah

For anonymous access, use these:

$ git clone git://git.savannah.nongnu.org/stribog.git
 to make your local repository

$ git checkout -b feb2008 origin/feb2008
 to make a local branch feb2008 based on fetched origin/feb2008

$ git fetch
 to update copies of remote branches

$ git pull
 to fetch all remote branches and merge
 one of them into your current branch

Common to both access types:

$ git checkout master
 to switch to existing branch 'master'

$ git add .
 to cache the changes in your files against
 the current branch most recent commit

$ git diff
 to see what will be "git add"ed

$ git diff --cached
 to see what has been "git add"ed but not 
 "git commit"ed

$ git branch
 to list the local repository branches

$ git branch -r
 to list the public repositories branches

$git commit
 to move the changes to your current branch

$git show
 to see the latest commit description
