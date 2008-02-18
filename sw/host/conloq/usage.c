/*conloq: copyleft and usage output
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"usage.h"
#include"error.h"
#include<stdio.h>
void
usage(void)
{printf("conloq 1.02 ("__DATE__"): talk to stribog\n\n"
"This program is a part of the stribog host software section\n\n"
"This program is free software; you can redistribute it and/or modify\n"
"it under the terms of the GNU General Public License as published by\n"
"the Free Software Foundation; either version 3 of the License, or\n"
"(at your option) any later version.\n\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n\n"
"You should have received a copy of the GNU General Public License\n"
"along with this program. If not, see <http://www.gnu.org/licenses/>.\n"
"Copyright (C) 2006, 2007, 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93\n"
"usage: conloq [port]\n default port on GNU is /dev/ttyS1, on Windows -- COM1\n\n"
"all data received are written in [0-9]*conloq.log\n\n"
"for help on keypresses press 'h'\n"
  );
}void
help(void)
{printf("some key assignments:\n"
"'h' help\n'a' toggle adc messages\n'g' toggle gps messages\n"
"'m' turn off all messages\n'n' turn on all messages\n"
"'o' toggle odo messages\n'p' toggle pps messages\n's' toggle stat messages\n"
"'S' show which messages are turned on\n't' toggle temp messages\n"
"'v' toggle verbosity\n'q' quit the programme\n"
"    press any key to continue\n"
  );
}
