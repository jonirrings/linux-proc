# plugin Makefile

DSTDIR = ../test
BINDIR = $(DSTDIR)/bin
PLGDIR = $(DSTDIR)/plugins
ETCDIR = $(DSTDIR)/etc

INSTALL = install

COPTS = -O2 -g
CFLAGS = $(COPTS) -fPIC
LDFLAGS = -shared

SUBDIRS = story_apple
PLUGINS = alien_ton.so

all: $(PLUGINS)
	for d in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$d all; done

%.so: %.c
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^

install: $(PLGDIR) $(PLUGINS)
	for p in $(PLUGINS); do $(INSTALL) -s -c -m 755 $$p $(PLGDIR); done
	for d in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$d install; done

$(PLGDIR):
	$(INSTALL) -d -m 755 $@

clean:
	rm -f *.o *.so *.a
	for d in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$d clean; done

depend:
	$(CPP) -M $(CFLAGS) *.c >.depend
