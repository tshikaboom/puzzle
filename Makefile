CC= gcc
CFLAGS= -W -Wall -ansi -pedantic -g
LDFLAGS=
EXEC= MAIN
SRC= contact.c init.c main.c chemin.c backtrack.c
OBJ= $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY : all clean proper

clean :
	rm -f *.o
	rm -f $(EXEC)
proper:
	rm -f *~
