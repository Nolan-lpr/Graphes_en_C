#include "prototypes.h"


/////// MAIN (qui gere les arguments en entree fichier entree/sortie + start/goal) /////
int main(int argc, char **argv) {
    FILE *in = stdin;
    FILE *out = stdout;
    int start = -1;  
    int goal = -1;

    // Gestion des arguments
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 >= argc) {
                printf("Erreur : -i necessite un nom de fichier\n");
                printf("Arguments :\n");
                printf("  -i <fichier_graphe>      : le fichier graphe a lire\n");
                printf("  -o <fichier_dot>         : le fichier dot a produire\n");
                printf("  -start <sommet_depart>   : le sommet de depart\n");
                printf("  -goal <sommet_arrivee>   : le sommet a atteindre\n");
                return 1;
            }
            in = fopen(argv[i + 1], "r");
            if (!in) { 
                printf("Erreur ouverture fichier entree\n"); 
                return 1; 
            }
            i += 2;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                printf("Erreur : -o necessite un nom de fichier\n");
                printf("Arguments :\n");
                printf("  -i <fichier_graphe>      : le fichier graphe a lire\n");
                printf("  -o <fichier_dot>         : le fichier dot a produire\n");
                printf("  -start <sommet_depart>   : le sommet de depart\n");
                printf("  -goal <sommet_arrivee>   : le sommet a atteindre\n");
                return 1;
            }
            out = fopen(argv[i + 1], "w");
            if (!out) { 
                printf("Erreur ouverture fichier sortie\n"); 
                return 1; 
            }
            i += 2;
        } else if (strcmp(argv[i], "-start") == 0) {
            if (i + 1 >= argc) {
                printf("Erreur : -start necessite un numero de sommet\n");
                printf("Arguments :\n");
                printf("  -i <fichier_graphe>      : le fichier graphe a lire\n");
                printf("  -o <fichier_dot>         : le fichier dot a produire\n");
                printf("  -start <sommet_depart>   : le sommet de depart\n");
                printf("  -goal <sommet_arrivee>   : le sommet a atteindre\n");
                return 1;
            }
            start = atoi(argv[i + 1]);
            i += 2;
        } else if (strcmp(argv[i], "-goal") == 0) {
            if (i + 1 >= argc) {
                printf("Erreur : -goal necessite un numero de sommet\n");
                printf("Arguments :\n");
                printf("  -i <fichier_graphe>      : le fichier graphe a lire\n");
                printf("  -o <fichier_dot>         : le fichier dot a produire\n");
                printf("  -start <sommet_depart>   : le sommet de depart\n");
                printf("  -goal <sommet_arrivee>   : le sommet a atteindre\n");
                return 1;
            }
            goal = atoi(argv[i + 1]);
            i += 2;
        } else {
            printf("Argument non reconnu : %s\n", argv[i]);
            printf("Arguments :\n");
            printf("  -i <fichier_graphe>      : le fichier graphe a lire\n");
            printf("  -o <fichier_dot>         : le fichier dot a produire\n");
            printf("  -start <sommet_depart>   : le sommet de depart\n");
            printf("  -goal <sommet_arrivee>   : le sommet a atteindre\n");
            return 1;
        }
    }

    // Lecture du graphe
    clock_t start_read = clock();
    t_graph_mat *g = read_graph_mat(in);
    clock_t end_read = clock();
    double time_read = ((double)(end_read - start_read)) / CLOCKS_PER_SEC;

    // Export en DOT
    clock_t start_dot = clock();
    graph_to_dot_mat(g, out);
    clock_t end_dot = clock();
    double time_dot = ((double)(end_dot - start_dot)) / CLOCKS_PER_SEC;
    
    double time_search;
    double time_kosaraju;

    // Si start ET goal ont ete fournis en arguments, chercher un chemin
    if (start != -1 && goal != -1) {
        // Verification de la validite des sommets
        if (start < 0 || start >= g->size || goal < 0 || goal >= g->size) {
            printf("Erreur : les sommets doivent être entre 0 et %d\n", g->size - 1);
            graph_mat_free(g);
            if (in != stdin) fclose(in);
            if (out != stdout) fclose(out);
            return 1;
        }

        // Recherche d'un chemin entre start et goal
        #ifdef DEBUG
        printf("\nRecherche d'un chemin de %d vers %d :\n", start, goal);
        #endif
        clock_t start_search = clock();
        Recherche_recur_mat(g, start, goal);
        clock_t end_search = clock();
        time_search = ((double)(end_search - start_search)) / CLOCKS_PER_SEC;
        #ifdef DEBUG
        printf("Temps de recherche : %.6f secondes\n", time_search);
        #endif
    }

    // Fermeture fichiers si necessaire
    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);

    // Calcul des composantes fortement connexes
    #ifdef DEBUG
    printf("\n");
    #endif
    clock_t start_kosaraju = clock();
    enum_cfc_kosaraju_mat(g);
    clock_t end_kosaraju = clock();
    

    // Affichage des temps d'execution
    printf("\n=== ANALYSE TEMPORELLE ===\n");
    printf("Temps de lecture du graphe : %.6f secondes\n", time_read);
    printf("Temps d'export en DOT      : %.6f secondes\n", time_dot);
    if (start != -1 && goal != -1) {
        time_kosaraju = ((double)(end_kosaraju - start_kosaraju)) / CLOCKS_PER_SEC;
        printf("Temps de recherche de chemin : %.6f secondes\n", time_search);
    }
    printf("Temps calcul CFC (Kosaraju) : %.6f secondes\n", time_kosaraju);
    printf("==========================\n");

    // Liberation memoire
    graph_mat_free(g);

    return 0;
}









/* LISTES (donnees dans base_fil_rouge) */

//nouvelle liste
// Utilisation : t_list l = list_new();
t_list list_new() { 
    return NULL; 
}

//ajoute un element e en haut de la pile l
t_list list_add_head(t_vertex e, t_list l) {
    t_node *n = malloc(sizeof(*n));
    assert(n != NULL); // Verifier allocation
    n->val = e;        // Stocker la valeur
    n->p_next = l;     // Pointer vers l'ancienne tête
    return n;          // Nouvelle tête
}

//retourne 1 si liste l vide, 0 sinon
int list_is_empty(t_list l) { 
    return l == NULL; 
}

// Affiche la liste l
void list_show(t_list l) {
  t_node * n = l;
  int i = 0;
  while (n != NULL) {
    printf("Maillon %d, valeur = %d\n", i++, n->val);
    n = n->p_next;
  }
}

// Retourne la valeur du premier maillon de la liste l
t_vertex list_get_first_val(t_list l) {
    assert(l != NULL);
    return l->val;
}

// Retire le premier maillon de la liste l et retourne la nouvelle tête
// Utilisation : l = list_remove_head(l);
t_list list_remove_head(t_list l) {
  t_list l2;
  assert(l != NULL);
  l2 = l->p_next;
  free(l);
  return l2;
}

// Libere la liste l de la memoire (maillon par maillon)
// Utilisation : l = list_free(l);
t_list list_free(t_list l) {
  t_node * n = l, * nNext;
  while (n != NULL) {
    nNext = n->p_next;
    free(n);
    n = nNext;
  }
  return NULL;
}

// Retourne un curseur de liste pour parcourir l
// Utilisation : t_node * lc = list_cursor_new(l);
// Remarque : en fait, un curseur est aussi une liste chaînee !
t_node * list_cursor_new(t_list l) {
  return l;
}

// Retourne 1 si la fin de la liste a ete atteinte
// Remarque : la fin d'une liste (NULL) est la même chose qu'une liste vide !
int list_cursor_at_end(t_node * lc) {
  return list_is_empty(lc);
}

// Retourne la valeur du maillon actuellement pointe par lc
// Remarque : ça revient en fait a prendre la valeur du premier maillon de lc !
int list_cursor_get_val(t_node * lc) {
  return list_get_first_val(lc);
}

// Avance le curseur vers le maillon suivant
// Utilisation : lc = list_cursor_next(lc);
t_node * list_cursor_next(t_node * lc) {
  assert(lc != NULL);
  return lc->p_next;
}

/* Fin LISTES */


/* PILES (donnees dans la base_fil_rouge) */

// Cree une nouvelle pile vide
// Utilisation : t_stack * ps = stack_new();
t_stack * stack_new() {
    t_stack *ps = malloc(sizeof(*ps));
    assert(ps != NULL);
    *ps = list_new(); // Liste vide
    return ps;
}

// Affiche tout le contenu d'une pile (pour le debogage seulement)
void stack_show(t_stack * ps) {
  list_show(*ps);
}

// Retourne 1 si la pile *ps est vide, 0 sinon
int stack_is_empty(t_stack * ps) {
  return list_is_empty(*ps);
}

// Empile la valeur e en haut de la pile *ps
void stack_push(t_vertex e, t_stack * ps) {
  *ps = list_add_head(e, *ps);
}

// Depile et retourne la valeur en haut de la pile *ps
t_vertex stack_pop(t_stack * ps) {
  t_vertex res = stack_top(ps);
  *ps = list_remove_head(*ps);
  return res;
}

// Retourne la valeur en haut de la pile *ps sans la depiler
t_vertex stack_top(t_stack * ps) {
  assert(!list_is_empty(*ps));
  return list_get_first_val(*ps);
}

/* Fin PILES */













////Creation d'un graphe vide de n sommets en liste d'adjacence///// 
t_graph_list * graph_list_new(int n) {
    t_graph_list *g = malloc(sizeof(*g));
    assert(g != NULL);
    g->size = n;
    g->adj = malloc(n * sizeof(*(g->adj))); // tableau de listes
    assert(g->adj != NULL);
    for (int i = 0; i < n; i++) g->adj[i] = list_new(); // initialisation
    return g;
}

/* Ajouter arc u->v pour une liste d'adjacence*/
void graph_list_add_arc(t_graph_list *g, t_vertex u, t_vertex v) {
    g->adj[u] = list_add_head(v, g->adj[u]);
}

/* Liberer graphe liste*/
void graph_list_free(t_graph_list *g) {
    for (int i = 0; i < g->size; i++) list_free(g->adj[i]);
    free(g->adj);
    free(g);
}


/* Creer graphe matrice d'adjacence vide n x n */
t_graph_mat * graph_mat_new(int n) {
    t_graph_mat *g = malloc(sizeof(*g));
    assert(g != NULL);
    g->size = n;
    g->m = malloc(n * sizeof(*(g->m)));
    assert(g->m != NULL);
    for (int i = 0; i < n; i++) {
        g->m[i] = calloc(n, sizeof(*(g->m[i]))); // 0 = pas d’arc
        assert(g->m[i] != NULL);
    }
    return g;
}

/* Ajouter arc u->v pour une matrice d'adjacence*/
void graph_mat_add_arc(t_graph_mat *g, t_vertex u, t_vertex v) {
    g->m[u][v] = TRUE;
}

/* Liberer matrice */
void graph_mat_free(t_graph_mat *g) {
    for (int i = 0; i < g->size; i++) free(g->m[i]);
    free(g->m);
    free(g);
}








///// Lecture d'un graphe sur un fichier (version matrice) //// 
t_graph_mat * read_graph_mat(FILE *in) {
    int n, u, v;
    char line[MAX_READ_LINE];

    // Lire le nombre de sommets depuis la premiere ligne
    if (fgets(line, MAX_READ_LINE, in) == NULL) {
        fprintf(stderr, "Erreur lecture nombre de sommets\n");
        return NULL;
    }
    n = atoi(line);
    t_graph_mat *g = graph_mat_new(n);

    // Lire les arcs ligne par ligne
    while (fgets(line, MAX_READ_LINE, in) != NULL) {
        if (sscanf(line, "%d %d", &u, &v) == 2) {
            graph_mat_add_arc(g, u, v);
        }
    }
    return g;
}


////Export des graphes au format DOT (version matrice) //////
void graph_to_dot_mat(t_graph_mat *g, FILE *out) {
    fprintf(out, "digraph G {\n");
    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            if (g->m[i][j]) {
                fprintf(out, "  %d -> %d;\n", i, j);
            }
        }
    }
    fprintf(out, "}\n");
}


/* Inverser tous les arcs du graphe (version matrice) */
t_graph_mat * graph_mat_inverse(t_graph_mat *g) {
    t_graph_mat *gi = graph_mat_new(g->size);
    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++) {
            if (g->m[i][j]) {
                graph_mat_add_arc(gi, j, i); // inverser
            }
        }
    }
    return gi;
}


/////KOSARAJU (VERSION MATRICE) ////

//Parcours du graphe (version matrice)
void Parcours_mat(t_graph_mat *g, t_vertex x, t_bool *marking) {
    if (marking[x]) return;

    marking[x] = TRUE;
    // traitement prefixe
    #ifdef DEBUG
    printf("%d ", x);
    #endif

    // Parcourir tous les successeurs
    for (int i = 0; i < g->size; i++) {
        if (g->m[x][i]) {
            Parcours_mat(g, i, marking);
        }
    }
    // traitement suffixe
}


//Fonction qui initialise les variables et appelle la seconde fonction
void Recherche_recur_mat(t_graph_mat *g, t_vertex x, t_vertex y) {
    t_bool *marking = calloc(g->size, sizeof(t_bool));
    t_stack *stack = stack_new();
    
    int found = Recherche_recur_f_mat(g, x, y, marking, stack);
    
    #ifdef DEBUG
    if (found) {
        printf("Chemin trouve : ");
        
        // Afficher directement en depilant
        if (!stack_is_empty(stack)) {
            printf("%d", stack_pop(stack));
        }
        
        while (!stack_is_empty(stack)) {
            printf(" -> %d", stack_pop(stack));
        }
        printf("\n");
    } else {
        printf("Aucun chemin trouve de %d vers %d\n", x, y);
    }
    #endif
    
    free(marking);
    list_free(*stack);
    free(stack);
}


//Fonction qui effectue le parcours en profondeur (version matrice)
int Recherche_recur_f_mat(t_graph_mat *g, t_vertex x, t_vertex y, t_bool *marking, t_stack *stack) {
    if (x == y) {
        stack_push(x, stack);
        return TRUE;
    }
    
    if (marking[x] == FALSE) {
        marking[x] = TRUE;
        
        // Parcourir tous les successeurs
        for (int w = 0; w < g->size; w++) {
            if (g->m[x][w]) {
                if (Recherche_recur_f_mat(g, w, y, marking, stack)) {
                    stack_push(x, stack);
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}


//Fonction enum (version matrice)
void enum_cfc_kosaraju_mat(t_graph_mat *g) {
    int n = g->size;
    t_bool *marking = calloc(n, sizeof(t_bool));
    int *order = malloc(n * sizeof(int));

    // 1) Premier parcours pour calculer l'ordre suffixe
    Kosaraju_1_mat(g, marking, order);

    // 2) Graphe inverse
    t_graph_mat *gi = graph_mat_inverse(g);

    // 3) Deuxieme parcours sur graphe inverse
    Kosaraju_2_mat(gi, order);

    graph_mat_free(gi);
    free(marking);
    free(order);
}


//Premier parcours recursif de l'algorithme de Kosaraju (version matrice)
void Kosaraju_1_mat(t_graph_mat *g, t_bool marking[], int order[]) {
    //t_bool *marking[g->size];
    for (int i = 0 ; i < g->size ; i++) {
        marking[i] = FALSE;
    }
    int step = 0;
    //order
    for (int x = 0 ; x < g->size ; x ++) {
        step = Kosaraju_1_recur_mat(g,x,marking,order,step);
    }
}


//Appels recursifs pour le premier parcours de Kosaraju (version matrice)
int Kosaraju_1_recur_mat(t_graph_mat *g, t_vertex x, t_bool *marking, int *order, int step) {
    if (marking[x] == FALSE) {
        marking[x] = TRUE;
        //partie "pour chaque successeur y de x", a priori juste mais non-testee
        t_bool y;
        for (int i = 0 ; i < g->size ; i++) {
            y = (g->m)[x][i];
            if (y == TRUE) {
                step = Kosaraju_1_recur_mat(g, i, marking, order, step);
            }
        }
        order[x] = step;
        step++;
        
    }
    return step;
}


//Deuxieme parcours recursif de l'algorithme de Kosaraju (version matrice)
void Kosaraju_2_mat(t_graph_mat *g, int order[]) {
    int n = g->size;
    t_bool marking[n];
    int inv_order[n];
    for (int i = 0 ; i < n ; i++) {
        marking[i] = FALSE;
    }
    int nb_scc = 0;
    //order
    for (int x = 0 ; x < n ; x ++) {
        inv_order[(n-1) - order[x]] = x;
    }
    for (int x = 0 ; x < n ; x ++) {
        if (Kosaraju_2_recur_mat(g, inv_order[x], marking)) {
            nb_scc++;
            #ifdef DEBUG
            printf("\n");            
            printf("CFC %d : ", nb_scc);

            #endif
        }
    }
    #ifdef DEBUG
    printf("%d composantes fortement connexes trouvees", nb_scc);
    #endif
}


//Appels recursifs pour le deuxieme parcours de Kosaraju (version matrice)
t_bool Kosaraju_2_recur_mat(t_graph_mat *g, t_vertex x, t_bool marking[]) {
    if (marking[x]) {
        return FALSE;
    }
    else {
        marking[x] = TRUE;
        #ifdef DEBUG
        printf("%d ", x);
        #endif
        t_bool y;
        for (int i = 0 ; i < g->size ; i++) {
            y = (g->m)[x][i];
            if (y == TRUE) { 
                Kosaraju_2_recur_mat(g, i, marking);
            }
        }

        return TRUE;
    }
}

