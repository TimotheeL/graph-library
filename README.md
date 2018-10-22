# Graph Library

Linked lists and Graph library implementation in C.
University project developed by Thibault BERTIN and Timothée LAURENT as part of the Graph Theory course (1st year of Master's degree) at the Université de Franche-Comté.

This project allows you to create and manipulate graphs through a command line menu. Thanks to this, you will be able to create or load a graph (directed or not) from a file, add nodes and edges to it and save it.

## Usage

To use this project, place yourself in the root directory of the project (where this README should normally be located) and open a terminal. To build the project, type the command `make`. To launch the project, type`./BIN/main`.

Alternatively, we created a very basic shell script to build and launch the project. You can use it by typing `./build.sh`. You will however need to type the command `chmod +x build.sh` before using it for the first time.

## Load graph

To load a graph from a file, you will need to respect the following format:
```
# maximum number of nodes
11
# directed
n
# node: neighbours
1: (4/5), (7/1), (3/2)
2: (5/4), (7/8)
3: (1/2), (6/8)
4: (7/3), (1/5), (6/5)
5: (2/4), (8/2)
6: (4/5), (3/8)
7: (2/8), (4/3), (1/1)
8: (5/2)
```
Lines starting with the character # will be considered to be comments and will be ignored. Please respect this format accurately.
