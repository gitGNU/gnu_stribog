#just templates for a target
CC=gcc
CFLAGS=$(CPPFLAGS) -Wall $(OPTFLAGS)
CXX=g++
CXXFLAGS=$(CFLAGS)
LD=g++
LFLAGS=-lm $(OPTFLAGS)
compiled=$(foreach m, $(modules), $(src)/$(m).c)
autohead="\#generated automatically with bash(1), echo(1), gcc(1) and sed(1)"
all: $(TARGETS) $(o)/autodeps.mk
#TODO: remove sed dependency
$(o)/autodeps.mk:$(Macul)/dirs.stamp $(compiled) $(included)
	echo $(autohead) > $@
	for i in $(compiled);do $(CC) -MM $$i | sed -e"s%^\([^ ]\)%$(o)/\1%" >> $@;done
maintainer-clean:
	rm -fr $(bin) $(Macul) $(o)
clean:
	rm -f `find $(o) -type f |grep -v "\(autodeps\.mk$$\)"`
.PHONY: all clean maintainer-clean
DIRS=$(bin) $(o) $(Macul)
$(Macul)/dirs.stamp:
	mkdir -p $(DIRS)
	date > $@
$(o)/%.o:$(src)/%.c $(Macul)/dirs.stamp 
	$(CC) -c $(CFLAGS) -o $@ $<
$(o)/%.o:$(src)/%.cxx $(Macul)/dirs.stamp 
	$(CXX) -c $(CXXFLAGS) -o $@ $<
$(bin)/%:$(o)/%.o
	$(LD) $(LFLAGS) $^ -o $@
include $(o)/autodeps.mk
#This program is a part of the stribog host software section
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>
