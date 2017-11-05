IDIR=include
SDIR=src
ODIR=obj
CC=gcc
CFLAGS=-I $(IDIR)

_DEPS=ui.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o ui.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o main.bin $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o main.bin
