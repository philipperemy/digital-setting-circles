CC=g++
CFLAGS= -W -Wall -ansi -pedantic
LDFLAGS= -lpthread
EXEC=dsc
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

dsc : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	@$(CC) -o $@ -c $< $(CFGLAGS)

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)
