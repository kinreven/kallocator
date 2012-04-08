# /*
# * File:	Makefile
# * Author:	Kevin Ren <kinreven@gmail.com>
# * Brief:	This file is a general Makefile templete
# *			it is work under MingW or Cygwin for Windows only.
# *
# * $Date:: 2011-12-15 22:13:20 #$
# *
# */

CC		:= gcc
AR		:= ar
ECHO	:= echo
CP		:= cp -f
RM		:= rm -f

TARGET	+= sample.exe

CCFLAGS += -Wall
CCFLAGS	+= -I.
ifeq ($(dbg), 1)
CCFLAGS	+= -g
CCFLAGS += -D__DEBUG=1
else
CCFLAGS	+= -O2
endif

ASFLAGS += -Wall

OBJS	+= safemem.o
OBJS	+= kallocator.o
OBJS	+= sample.o

LIBS	:= 

.c.o:
	@$(ECHO) "Compiling $<..."
	@$(CC) $(CCFLAGS) -c $<

.S.o:
	@$(ECHO) "Compiling $<..."
	@$(CC) $(ASFLAGS) $(CCFLAGS) -c $<
	
all: $(TARGET)

$(TARGET) : $(OBJS)
	@$(CC) -o $(TARGET) $(OBJS) -static $(LIBS)
	@$(ECHO) "***" $(TARGET) "is built successfully! ***"

.PHONY: clean
clean:
	@$(RM) $(OBJS)
	@$(RM) $(TARGET)
