# crontab Makefile

TARGETS = crontab

HEADERS = cron_task.h

CRONSRCS = main.c crontab.c tasks/task_alarm.c

CRONOBJS = main.o crontab.o tasks/task_alarm.o

COPTS = -O2 -Wall -g
#INCDIRS = 
CFLAGS = $(COPTS) $(INCDIRS)

LIBS = -lpthread
LDFLAGS = $(LIBS)

all: $(TARGETS)

crontab: $(CRONOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o crontab $(CRONOBJS) $(LIBS)

clean: 
	rm -f $(CRONOBJS) $(TARGETS)

depend:
	$(CPP) -M $(CFLAGS) $(CRONSRCS) >.depend

