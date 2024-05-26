#!/bin/sh


gcc parent.c -o parent
gcc child.c -o child
#gcc game.c -o game -lglut -lGL -lGLU

./parent 1 
#./game
#rm -f parent
#rm -f child


######################################

# gcc -g main.c -o main
# ./main
# rm -f main
