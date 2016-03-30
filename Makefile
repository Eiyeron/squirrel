
SQUIRREL=.
MAKE=make

sq32: folders
	cd squirrel; $(MAKE)
	cd sqstdlib; $(MAKE)
	cd sq; $(MAKE)

sqprof: folders
	cd squirrel; $(MAKE) sqprof
	cd sqstdlib; $(MAKE) sqprof
	cd sq; $(MAKE) sqprof

sq64: folders
	cd squirrel; $(MAKE) sq64
	cd sqstdlib; $(MAKE) sq64
	cd sq; $(MAKE) sq64

sqnspire: folders
	cd squirrel; $(MAKE) sqnspire
	cd sqstdlib; $(MAKE) sqnspire
	cd sq; $(MAKE) sqnspire

folders:
	mkdir -p lib
	mkdir -p bin
