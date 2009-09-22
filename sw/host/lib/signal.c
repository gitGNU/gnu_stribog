/* wrap-around standard signal handling routines
Copyright (C) 2008, 2009\
 Ineiev<ineiev@users.berlios.de>, super V 93
This program is a part of the stribog host software section

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

/*The purpose of the library is to terminate the application
having received usual signals (SIGINT, SIGTERM etc);
the application resources are freed
by functions registered with atexit()

C89 implementation (via signal()) is theoretically unreliable:
it may behave badly when receiving several signals at a time */

/*define SIGNALS_TEST to non-zero to compile a test*/
#ifndef SIGNALS_TEST
# define SIGNALS_TEST 0
#endif
#if SIGNALS_TEST
static int signals_count;
#endif
#if HAVE_CONFIG_H
# include<config.h>
#else
# define RETSIGTYPE void
#endif
#if HAVE_SIG_ATOMIC_T
#else
 typedef int sig_atomic_t;
#endif
#include"sbg_signal.h"
#ifndef SIG_ERR
 /* works for BSD 4.3 */
#define SIGNAL_RETURN_INVALID(a) -1==(int)(a)
#else
#define SIGNAL_RETURN_INVALID(a) SIG_ERR==(a)
#endif
#include<stdlib.h>
#include<stdio.h>
enum local_constants
{sigarray_size=SIGTERM+1,max_distinct_signal=sigarray_size-1};
static volatile sig_atomic_t
/*non-null value of signal_numbers[i] indicates that
 a signal number i+1 has been handled*/
 signal_numbers[sigarray_size],
 signal_caught;/*any signal caught*/
static RETSIGTYPE
sig_hunter(int sig)
{
#if HAVE_SIGACTION
#else
/*'non-persistent' platforms set the signal action to SIG_DFL,
so we want to reestablish our handler; this actually may not work
when two different signals appear simultaneously; that is
why sigaction() should be used when possible*/
 signal(sig,sig_hunter);
#endif
 if((!SIGNALS_TEST)||(sig==SIGINT))signal_caught=!0;
 if(sig<=max_distinct_signal&&sig>0)
  signal_numbers[sig]=!0;
#if SIGNALS_TEST
 signals_count++;
#endif
 return(RETSIGTYPE)0;
}
static const int
handled_list[]=/*array of handled signals*/
{
#ifdef SIGQUIT
 SIGQUIT,/*SIGQUIT is a POSIX feature; C89 lacks it*/
#endif
#ifdef SIGHUP
 SIGHUP,/*the same as SIGQUIT*/
#endif
 SIGINT,SIGTERM
};
#if HAVE_SIGACTION
static sigset_t sa_mask;/*accumulated mask for all handled signals*/
static void
setup_sa_mask(void)
{int i;sigemptyset(&sa_mask);
 for(i=0;i<sizeof(handled_list)/sizeof*handled_list;i++)
  sigaddset(&sa_mask,handled_list[i]);
}
#else
static void
setup_sa_mask(void){}
#endif
static int
setup_a_signal(int sig)
{
#if HAVE_SIGACTION
 struct sigaction sa;
 if(sigaction(sig,0,&sa))return!0;
 if(SIG_IGN==sa.sa_handler)return 0;
 if(sigaddset(&sa_mask,sig))return!0;
 sa.sa_mask=sa_mask;sa.sa_handler=sig_hunter;
 sa.sa_flags=0;return sigaction(sig,&sa,0);
#else
 if(SIG_IGN==signal(sig,sig_hunter))
  return SIGNAL_RETURN_INVALID(signal(sig,SIG_IGN));
 return 0;
#endif
}
int
init_signals(void)
{int i;setup_sa_mask();
 for(i=0;i<sizeof(handled_list)/sizeof*handled_list;i++)
  if(setup_a_signal(handled_list[i]))return!0;
 return 0;
}
static void
output_signal_name(int sig)
{if(sig<0)
 {fprintf(stderr,"INDEFINITE SIGNAL CAUGHT\n");
  return;
 }
 switch(sig)
 {case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
#ifdef SIGQUIT
  case SIGQUIT:fprintf(stderr,"USER-REQUESTED ABORT\n");break;
#endif
#ifdef SIGHUP
  case SIGHUP:fprintf(stderr,"HANGUP\n");break;
#endif
  default:fprintf(stderr,"UNKNOWN SIGNAL %i CAUGHT\n",sig);
 }
}
void
check_signals(int exit_code)
{int i,vex=!0;if(!signal_caught)return;
 for(i=sigarray_size-1;i>0;i--)
  if(signal_numbers[i])
  {output_signal_name(i);vex=0;}
 if(vex)output_signal_name(-1);
 exit(exit_code);
}
#if SIGNALS_TEST
static void
report_all(void)
{printf("signals count: %i\n",signals_count);}
int
main(void)
{init_signals();atexit(report_all);
 while(1)check_signals(1);return 0;
}
#endif
