
BIN = ./bin
SRC = ./src
INC = ./include
OBJ = ./obj

COMMON = $(OBJ)/align.o \
	$(OBJ)/cluster.o \
	$(OBJ)/distancemat.o \
	$(OBJ)/options.o \
	$(OBJ)/util.o \
	$(OBJ)/sequence.o

ALN2TREEOBJ = $(COMMON) $(OBJ)/aln2tree.o $(OBJ)/buildtree.o $(OBJ)/tree.o
ALN2DISTOBJ = $(COMMON) $(OBJ)/aln2dist.o 
DIST2TREEOBJ = $(COMMON) $(OBJ)/dist2tree.o $(OBJ)/buildtree.o $(OBJ)/tree.o
QUICKTREEOBJ = $(COMMON) $(OBJ)/quicktree.o $(OBJ)/buildtree.o $(OBJ)/tree.o


CC	= cc
CFLAGS  = -c -g -I$(INC) -fullwarn
#CC	= -gcc
#CFLAGS  = -c -I$(INC) -O2 -Wall

LFLAGS = -g 

all: $(BIN)/aln2tree $(BIN)/aln2dist $(BIN)/dist2tree $(BIN)/quicktree

quicktree : $(BIN)/quicktree

$(BIN)/quicktree : $(QUICKTREEOBJ)
	$(CC) $(LFLAGS) -o $@ $(QUICKTREEOBJ) -lm

$(BIN)/aln2tree : $(ALN2TREEOBJ)
	$(CC) $(LFLAGS) -o $@ $(ALN2TREEOBJ) -lm

$(BIN)/aln2dist : $(ALN2DISTOBJ)
	$(CC) $(LFLAGS) -o $@ $(ALN2DISTOBJ) -lm

$(BIN)/dist2tree : $(DIST2TREEOBJ)
	$(CC) $(LFLAGS) -o $@ $(DIST2TREEOBJ) -lm

$(OBJ)/quicktree.o : $(SRC)/quicktree.c 
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/aln2tree.o : $(SRC)/aln2tree.c $(INC)/aln2tree.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/dist2tree.o : $(SRC)/dist2tree.c $(INC)/dist2tree.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/aln2dist.o : $(SRC)/aln2dist.c $(INC)/aln2dist.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/align.o : $(SRC)/align.c $(INC)/align.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/buildtree.o : $(SRC)/buildtree.c $(INC)/buildtree.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/cluster.o : $(SRC)/cluster.c $(INC)/cluster.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/distancemat.o : $(SRC)/distancemat.c $(INC)/distancemat.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/sequence.o : $(SRC)/sequence.c $(INC)/sequence.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/tree.o : $(SRC)/tree.c $(INC)/tree.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/util.o : $(SRC)/util.c $(INC)/util.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

$(OBJ)/options.o : $(SRC)/options.c $(INC)/options.h
	$(CC) $(CFLAGS) -o $(OBJ)/$*.o $(SRC)/$*.c

clean:
	rm $(OBJ)/*.o
