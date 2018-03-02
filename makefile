IDIR=include
SDIR=src
ODIR=obj
CC=gcc
CFLAGS=-I $(IDIR)

_DEPS=ui.h commands.h string.h color.h metodos.h bc.h parser.h ast.h array.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o ui.o commands.o string.o bc.o parser.o ast.o array.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o main.bin $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.o main.bin
