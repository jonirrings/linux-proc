# story_apple Makefile

DSTDIR = ../../test
BINDIR = $(DSTDIR)/bin
PLGDIR = $(DSTDIR)/plugins
ETCDIR = $(DSTDIR)/etc

INSTALL = install

COPTS = -O2 -g
CFLAGS = $(COPTS) -fPIC
LIBS = -lpthread
LDFLAGS = -shared

APPOBJS = pick_apple.o eat_apple.o pick_eat.o

PLUGINS = story_apple.so

all: $(PLUGINS)

story_apple.so: $(APPOBJS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^ $(LIBS)

install: $(PLGDIR)
	$(INSTALL) -s -c -m 755 story_apple.so $(PLGDIR)

$(PLGDIR):
	$(INSTALL) -d -m 755 $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so *.a
