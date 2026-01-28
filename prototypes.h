#ifndef prototypes_h
#define prototypes_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


#define DEBUG
#define MAX_READ_LINE 100 // sert pas trop sauf pour limiter la taille d'une ligne lu dans read_graph
#define TRUE 1             
#define FALSE 0          

typedef int t_bool;    
typedef int t_vertex;  // sommet du graphe

//maillon de liste chainee
typedef struct node {
    t_vertex val;            // Valeur du sommet du graphe
    struct node *p_next;     // Pointeur vers le maillon suivant
} t_node;

typedef t_node * t_list;     // definition de la liste chaînee
typedef t_list t_stack;      // Pile de sommets

//////// Prototypes Listes chaînees (donnees dans base_fil_rouge) ////////
t_list list_new();                                  // Creer une liste vide
t_list list_add_head(t_vertex e, t_list l);        // Ajouter un element en tête
int list_is_empty(t_list l);                       // Verifier si la liste est vide
void list_show(t_list l);                          // Affiche la liste l
t_vertex list_get_first_val(t_list l);             // Recuperer la valeur du premier element
t_list list_remove_head(t_list l);                 // Retirer le premier element
t_list list_free(t_list l);                        // Liberer toute la liste
t_node * list_cursor_new(t_list l);               // Curseur de parcours (pointeur sur maillon)
int list_cursor_at_end(t_node *lc);               // Verifier si le curseur est à la fin
t_vertex list_cursor_get_val(t_node *lc);         // Valeur pointee par le curseur
t_node * list_cursor_next(t_node *lc);            // Avancer le curseur d'un maillon

//////// Prototypes Piles (donnees dans base_fil_rouge) ////////
t_stack * stack_new();                            // Creer une pile vide
int stack_is_empty(t_stack *ps);                 // Verifier si la pile est vide
void stack_show(t_stack * ps);                   // Affiche tout le contenu d'une pile
void stack_push(t_vertex e, t_stack *ps);        // Empiler un element
t_vertex stack_pop(t_stack *ps);                 // Depiler un element
t_vertex stack_top(t_stack *ps);                 // Voir l'element au sommet

/////Definition graphes par liste//////
typedef struct {
    int size;        // Nombre de sommets
    t_list *adj;     // Tableau de listes d'adjacence (adj[i] = voisins de i)
} t_graph_list;

///////Definition graphe par matrice/////
typedef struct {
    int size;        // Nombre de sommets
    t_bool **m;      
} t_graph_mat;


//// Prototypes graphes matrices
t_graph_mat * read_graph_mat(FILE *in);                      // Lire graphe depuis fichier
void graph_to_dot_mat(t_graph_mat *g, FILE *out);           // Exporter graphe matrice en DOT
t_graph_mat * graph_mat_inverse(t_graph_mat *g);            // Inverser les arcs

//DFS matrice
void Parcours_mat(t_graph_mat *g, t_vertex x, t_bool *marking);
void Recherche_recur_mat(t_graph_mat *g, t_vertex x, t_vertex y);
int Recherche_recur_f_mat(t_graph_mat *g, t_vertex x, t_vertex y, t_bool *marking, t_stack *stack);

//Kosaraju Matrice
void enum_cfc_kosaraju_mat(t_graph_mat *g);
void Kosaraju_1_mat(t_graph_mat *g, t_bool *marking, int *order);
int Kosaraju_1_recur_mat(t_graph_mat *g, t_vertex x, t_bool *marking, int *order, int step);
void Kosaraju_2_mat(t_graph_mat *g, int *order);
t_bool Kosaraju_2_recur_mat(t_graph_mat *g, t_vertex x, t_bool marking[]);


/////// Prototypes graphes //////
t_graph_list * graph_list_new(int n);                 // Creer un graphe liste vide
void graph_list_add_arc(t_graph_list *g, t_vertex u, t_vertex v); // Ajouter arc u->v
void graph_list_free(t_graph_list *g);               // Liberer graphe liste
t_graph_list * graph_inverse(t_graph_list *g);

t_graph_mat * graph_mat_new(int n);                  // Creer un graphe matrice vide
void graph_mat_add_arc(t_graph_mat *g, t_vertex u, t_vertex v);   // Ajouter arc u->v
void graph_mat_free(t_graph_mat *g);                // Liberer graphe matrice
void graph_to_dot_list(t_graph_list *g, FILE *out); // Exporter graphe liste au format DOT



/////Prototype lecture de graphe depuis un fichier /////
t_graph_list * read_graph_list(FILE *in);



/* ================= DFS – RECHERCHE DE CHEMIN ================= */
void Parcours(t_graph_list *g, t_vertex x, t_bool *marking); // DFS recursif pour trouver chemin



/* ================= KOSARAJU ================= */
int Recherche_recur_f(t_graph_list *g, t_vertex x, t_vertex y, t_bool *marking, t_stack *stack);
void Recherche_recur(t_graph_list *g, t_vertex x, t_vertex y);
void enum_cfc_kosaraju(t_graph_list *g);
void Kosaraju_1(t_graph_list *g, t_bool *marking, int *order);
int Kosaraju_1_recur(t_graph_list *g, t_vertex x, t_bool *marking, int *order, int step);
void Kosaraju_2(t_graph_list *g, int *order);
t_bool Kosaraju_2_recur(t_graph_list *g, t_vertex x, t_bool *marking);


#endif
