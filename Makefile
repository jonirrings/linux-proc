# top-level Makefile for crontab

all:
	cd crontab; $(MAKE) $(MFLAGS) all
	cd plugins; $(MAKE) $(MFLAGS) all

clean:
	cd crontab; $(MAKE) $(MFLAGS) clean
	cd plugins; $(MAKE) $(MFLAGS) clean
