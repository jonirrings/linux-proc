# plugin Makefile

COPTS = -O2 -g
CFLAGS = $(COPTS) -fPIC
LDFLAGS = -shared

SUBDIRS = story_apple
PLUGINS = alien_ton.so

all: $(PLUGINS)
	for d in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$d all; done

%.so: %.c
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^

clean:
	rm -f *.o *.so *.a
	for d in $(SUBDIRS); do $(MAKE) $(MFLAGS) -C $$d clean; done

depend:
	$(CPP) -M $(CFLAGS) *.c >.depend
