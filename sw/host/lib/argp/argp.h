/*emergency argp implementation (header)
Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
/*
This is a limited, poorly tested and straight-forward implementation
to use on systems lacking glibc.*/
enum argp_key_values/*the positive values are option keys*/
{ARGP_KEY_ARG=-1,ARGP_KEY_END=-2};
#if HAVE_ERROR_T
#else
typedef int error_t;
#endif
enum argp_error_values{ARGP_ERR_UNKNOWN=-1};
struct argp_option
{const char*long_option;
 int key;
 const char*arg_name;
 int flags;
 const char*help;
};
enum argp_flags_bits
{OPTION_ARG_OPTIONAL=(1<<0),OPTION_ALIAS=(1<<1)};
struct arguments;
struct argp_state
{struct arguments*input;
 struct argp*argp;
 const char*prog_name;
 int arg_num;
};
typedef error_t(*parse_opt_function_t)
 (int key,char*arg,struct argp_state*state);
struct argp
{struct argp_option*options;
 parse_opt_function_t parse_option;
 const char*args_doc;const char*doc;
};
/*the next two strings MUST be defined in the application sources*/
extern const char*argp_program_version;
extern const char*argp_program_bug_address;
void argp_parse(struct argp*,int argc,char**argv,int,int,struct arguments*);
void argp_usage(struct argp_state*);
