# crontab Makefile

TARGETS = crontab

HEADERS = crontab.h plug.h

CRONSRCS = main.c cron_task.c plug_task.c \
		tasks/task_alarm.c tasks/task_fib.c

CRONOBJS = main.o cron_task.o plug_task.o \
		tasks/task_alarm.o tasks/task_fib.o

COPTS = -O2 -Wall -g
#INCDIRS = 
CFLAGS = $(COPTS) $(INCDIRS)

LIBS = -lpthread -ldl
#LDFLAGS = 

all: $(TARGETS)

crontab: $(CRONOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o crontab $(CRONOBJS) $(LIBS)

clean: 
	rm -f $(CRONOBJS) $(TARGETS)

depend:
	$(CPP) -M $(CFLAGS) $(CRONSRCS) >.depend
