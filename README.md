# Graphes_en_C
Projet en C sur les graphes orientés. 

Le but de ce projet est représenter les graphes orientés par matrices et par listes simplement chainéesde. Il s'agit, à partir d'un fichier d'entrée lu contenant une série de paires de nombres représentant ses arcs, de trouver : 
- Les Composantes Fortements Connexes (CFC) du graph
- Le représenter avec Graphviz après l'avoir convertit en fichier graph (.dot)
- Trouver un chemin à partir d'un sommet particulier entrée par l'utilisateur
- Déterminer la performance des 2 programmes par liste et par matrice à des fins d'optimisation.

Explication d'utilisation : 

./main_liste -start 0 -goal 16000 -o graphe1.dot -i graph_16498_PC-biogrid.txt

OU 

./main_matrice -start 0 -goal 16000 -o graphe1.dot -i graph_16498_PC-biogrid.tx
