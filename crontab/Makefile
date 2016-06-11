# crontab Makefile

DSTDIR = ../test
BINDIR = $(DSTDIR)/bin
PLGDIR = $(DSTDIR)/plugins
ETCDIR = $(DSTDIR)/etc

INSTALL = install

TARGETS = crontab

HEADERS = crontab.h plug.h option.h util.h

CRONSRCS = main.c cron_task.c plug_task.c option.c util.c \
		tasks/task_alarm.c tasks/task_fib.c

CRONOBJS = main.o cron_task.o plug_task.o option.o util.o \
		tasks/task_alarm.o tasks/task_fib.o

COPTS = -O2 -Wall -g
#INCDIRS = 
CFLAGS = $(COPTS) $(INCDIRS)

LIBS = -lpthread -ldl
#LDFLAGS = 

all: $(TARGETS)

crontab: $(CRONOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o crontab $(CRONOBJS) $(LIBS)

install: $(BINDIR) $(BINDIR)/crontab

$(BINDIR)/crontab:
	$(INSTALL) -c -m 555 crontab $@

$(BINDIR):
	$(INSTALL) -d -m 755 $@

clean: 
	rm -f $(CRONOBJS) $(TARGETS)

depend:
	$(CPP) -M $(CFLAGS) $(CRONSRCS) >.depend
