# #!/bin/sh


# gcc parent.c -o parent
# gcc child.c -o child
# #gcc game.c -o game -lglut -lGL -lGLU

# ./parent 1 
# stop
# #./game
# #rm -f parent
# #rm -f child


# ######################################

# # gcc -g main.c -o main
# # ./main
# # rm -f main


# ########################3
# #########################



CC=gcc
CFLAGS=-g
LIBS=-lglut -lGL -lGLU

all: parent child #game

parent: parent.c
	$(CC) parent.c -o parent

child: child.c
	$(CC) child.c -o child

# game: game.c
# 	$(CC) game.c -o game $(LIBS)

clean:
	rm -f parent child game
# Here's how you can use this Makefile:

# Save the Makefile to a file named Makefile.
# Open a terminal and navigate to the directory containing the Makefile.
# Type make to build the executables parent, child, and game.
# Type make clean to remove the executables.
# Note that the clean target is provided to remove the executables after they have been built. This is useful to avoid cluttering the directory with unnecessary files.