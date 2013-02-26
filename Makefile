CC= gcc
CFLAGS= -W -Wall -Iinclude -ansi -pedantic #-g
LDFLAGS= -lm
LIB=lib
SRC=src
OBJ=obj
BIN=bin
EXEC= PUZZLE


all : directories $(EXEC)

#Creation bin , obj , lib
directories : ${OBJ} ${LIB} ${BIN}

${OBJ}:
	mkdir ${OBJ}
${BIN}:
	mkdir ${BIN}
${LIB}:
	mkdir ${LIB}

#Fichier Executable
$(EXEC) : $(OBJ)/init.o $(OBJ)/contact.o $(OBJ)/chemin.o $(OBJ)/backtrack.o $(OBJ)/parser.o $(OBJ)/main.o
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

# Fichiers Objet
$(OBJ)/init.o : $(SRC)/init.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) 

$(OBJ)/contact.o : $(SRC)/contact.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJ)/chemin.o : $(SRC)/chemin.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJ)/backtrack.o : $(SRC)/backtrack.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJ)/parser.o : $(SRC)/parser.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

$(OBJ)/main.o : $(SRC)/main.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

# Bibliotheques
$(LIB)/exemple.a : $(OBJ)/exemple.o
	ar -rs $@ $^


.PHONY : all clean proper

#Nettoyage
clean :
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(EXEC)
	rm -rf ${OBJ} ${BIN} ${LIB}
proper:
	rm -f *~
	rm -f $(SRC)/*~

# Lancement
run:
	./$(BIN)/$(EXEC)
