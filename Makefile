## Makefile

binary 		= smtp_probe
compiler 	= cc
flags		= -g3 -Wall
includes	= -I.
libraries	=
cflags		= $(flags) $(includes) $(libraries)
label		= -- $(binary) BETA version --

sources		= smtp_probe.c finger.c misc.c network.c probe.c
objects		= $(sources:.c=.o)

default		: readme objects binary

readme		:
		@cat WutCodeDo

objects		:
		@for f in $(sources); do echo compiling $$f; \
		$(compiler) -c $$f $(cflags); done

binary		:
		@echo compiling $(binary)
		@$(compiler) -o $(binary) $(objects) $(cflags)
		@strip $(binary)

debug		: objects
		@echo compiling $(binary) in debug mode
		@$(compiler) -o $(binary) $(objects) $(cflags) -lefence -L.

release		:
		@echo creating release
		rm -f *.o *~ .*~ a.out core $(binary)
		cd .. && tar czf $(binary).tgz $(binary)/

clean		:
		rm -f *.o *~ .*~
