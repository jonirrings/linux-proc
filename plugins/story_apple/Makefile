# story_apple Makefile

COPTS = -O2 -g
CFLAGS = $(COPTS) -fPIC
LIBS = -lpthread
LDFLAGS = -shared

APPOBJS = pick_apple.o eat_apple.o pick_eat.o

PLUGINS = story_apple.so

all: $(PLUGINS)

story_apple.so: $(APPOBJS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so *.a
