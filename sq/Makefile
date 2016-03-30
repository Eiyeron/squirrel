SQUIRREL= ..


OUT= $(SQUIRREL)/bin/sq
INCZ= -I$(SQUIRREL)/include -I. -I$(SQUIRREL)/sqlibs
LIBZ= -L$(SQUIRREL)/lib
LIB= -lsquirrel -lsqstdlib

OBJS= sq.o

SRCS= sq.c


sq32:
	g++ -O2 -fno-exceptions -fno-rtti -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sqprof:
	g++ -O2 -pg -fno-exceptions -fno-rtti -pie -gstabs -g3 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sq64:
	g++ -O2 -m64 -fno-exceptions -fno-rtti -D_SQ64 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sqnspire:
	nspire-g++ -O2 -fno-exceptions -fno-rtti -o $(OUT).elf $(SRCS) $(INCZ) $(LIBZ) $(LIB)
	# Nspire executable file generation
	genzehn --input $(OUT).elf --output $(OUT).zehn $(ZEHNFLAGS)
	make-prg $(OUT).zehn $(OUT).tns
	rm $(OUT).zehn
