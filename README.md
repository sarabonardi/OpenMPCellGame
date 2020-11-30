# OpenMPCellGame

This is a game that follows these rules:
A square matrix of dimensions NxN contains either a 1 or 0 in each position to represent alive (1) cells or dead (0) cells.
A cell's neighbors include the 8 cells surrounding the cell in question, fewer for edge and corner cells.
An alive cell will only stay alive if it has exactly 2 or 3 alive neighbors.
A dead cell can come back to life if it has exactly 3 alive neighbors.
Otherwise, all cells will die in the next generation.

### How to Run the Program

This game is made for a linux machine. To run it, enter the lines below in a command line.
N represents the dimensions of the matrix to compute.
filename is the name of the file that will be output by genmap and input to ompgame.c.
G is the number of generations that the game will undergo.
T is the number of threads that OpenMP will use to execute the program.

chmod 777 automata
chmod 777 genmap
./genmap N filename
gcc -Wall -std=c99 -o automata -fopenmp ompgame.c
./automata G N T filename

### Output:

The output of this game will be a print statement containing the runtime for the given number of threads and a file called "filename.out" containing the final matrix.
