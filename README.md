# Graphes_en_C
This is a C project on directed graphs. 

The goal of this project is to represent directed graphs using adjacency matrices and singly linked lists. 

Starting from an input file containing a series of number pairs representing the graph’s edges, the program must find :
- Strongly Connected Components (SCCs) of the graph
- represent the graph using Graphviz after converting it into a .dot file
- find a path starting from a specific vertex provided by the user
- evaluate the performance of the two implementations (list-based and matrix-based) for optimization purposes.


Usage example: 

./main_list -start 0 -goal 16000 -o graph1.dot  -i graph_16498_PC-biogrid.txt

OR 

./main_matrix -start 0 -goal 16000 -o graph1.dot  -i graph_16498_PC-biogrid.txt.
