CC= gcc
CFLAGS= -W -Wall -ansi -pedantic -g
LDFLAGS= -L $(LIB) -lm -lpuzzle
INCFLAGS= -Iinclude
LIB=lib
SRC=src
OBJ=obj
BIN=bin
EXEC= PUZZLE

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif


all : directories $(EXEC)

#Creation bin , obj , lib
directories : ${OBJ} ${LIB} ${BIN}

${OBJ}:
	mkdir -p ${OBJ}
${BIN}:
	mkdir -p ${BIN}
${LIB}:
	mkdir -p ${LIB}

#Fichier Executable
$(EXEC) : $(OBJ)/main.o $(LIB)/libpuzzle.a
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

# Fichiers Objet
$(OBJ)/init.o : $(SRC)/init.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS) 

$(OBJ)/contact.o : $(SRC)/contact.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/chemin.o : $(SRC)/chemin.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/backtrack.o : $(SRC)/backtrack.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/parser.o : $(SRC)/parser.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCFLAGS)

# Bibliotheques
$(LIB)/libpuzzle.a : $(OBJ)/init.o $(OBJ)/contact.o $(OBJ)/chemin.o $(OBJ)/backtrack.o $(OBJ)/parser.o
	ar -rs $@ $^


.PHONY : all clean proper

#Nettoyage
clean :
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(EXEC)
	rm -f $(LIB)/*
	rm -f sol*

proper:
	rm -f *~
	rm -f $(SRC)/*~
	rm -f include/*~

cleanall: clean
	rm -r $(OBJ)
	rm -r $(BIN)
	rm -r $(LIB)

# Lancement
run1:
	./$(BIN)/$(EXEC)
run2:
	./$(BIN)/$(EXEC) Puzzle.puzzle 1
run3:
	./$(BIN)/$(EXEC) Puzzle.puzzle 2
run4:
	./$(BIN)/$(EXEC) Puzzle.puzzle 3
