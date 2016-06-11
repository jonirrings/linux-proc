# top-level Makefile for crontab

DSTDIR = ./test
BINDIR = $(DSTDIR)/bin
PLGDIR = $(DSTDIR)/plugins
ETCDIR = $(DSTDIR)/etc

INSTALL = install

all:
	cd crontab; $(MAKE) $(MFLAGS) all
	cd plugins; $(MAKE) $(MFLAGS) all

install: install-progs install-etc

install-progs:
	cd crontab; $(MAKE) $(MFLAGS) install
	cd plugins; $(MAKE) $(MFLAGS) install

install-etc: $(ETCDIR) $(ETCDIR)/options

$(ETCDIR)/options:
	$(INSTALL) -c -m 644 crontab/options $@

$(ETCDIR):
	$(INSTALL) -d -m 755 $@

clean:
	cd crontab; $(MAKE) $(MFLAGS) clean
	cd plugins; $(MAKE) $(MFLAGS) clean
