# plugin Makefile

COPTS = -O2 -g
CFLAGS = $(COPTS) -fPIC
LDFLAGS = -shared

PLUGINS = alien_ton.so

all: $(PLUGINS)

%.so: %.c
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^

clean:
	rm -f *.o *.so *.a

depend:
	$(CPP) -M $(CFLAGS) *.c >.depend
