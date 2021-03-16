#Author: Ramneet
PROJECT_NAME = proj_GOL #variable 
CC=gcc                  #compiler
LIB = -lpthread -lncurses
SOURCE= ../source
CFLAG= -c -Wall   #this makes object files

all: pthreads_Project    #all= target; pthreads_Project = dependencies
	@echo "making complete project"
	#gcc ../source/gol.c ../source/cells.c ../source/display.c -lpthread -lncurses -o $(PROJECT_NAME)

pthreads_Project: gol.o cells.o display.o
	$(CC) gol.o cells.o display.o $(LIB) -o $(PROJECT_NAME)   #replace variable with $

gol.o: $(SOURCE)/gol.c
	$(CC) $(CFLAG) $(SOURCE)/gol.c
	@echo "making object file gol.o"
cells.o: $(SOURCE)/cells.c
	$(CC) $(CFLAG) $(SOURCE)/cells.c
	@echo "making object file cells.o"
display.o: $(SOURCE)/display.c
	$(CC) $(CFLAG) $(SOURCE)/display.c
	@echo "making object file display.o"
	
clean:
	rm -rf *o $(PROJECT_NAME)
