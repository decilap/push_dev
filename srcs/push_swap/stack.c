#include "./../../includes/push_swap.h"

 static int get_node_value(t_stack *node) {
    return node ? node->nbr : -1; // Retourne -1 si le nœud est NULL
}

void    print_stack(t_stack *head) {
    t_stack *current = head;
    int count = 0;

    printf("+--------------------------------------------------------------------------------+\n");
    printf("| Index | Number | Push Cost | Above Median | Cheapest | Target Node |    Next   |\n");
    printf("+--------------------------------------------------------------------------------+\n");

    while (current != NULL) {
       // printf("| %5d | %6d | %9d | %12s | %8s | %11d | %14d | %14d |\n",
        printf("| %5d | %6d | %9d | %12s | %8s | %11d | %9d |\n",
               current->index,
               current->nbr,
               current->push_cost,
               current->above_median ? "True" : "False",
               current->cheapest ? "True" : "False",
               get_node_value(current->target_node),
            get_node_value(current->next));
        current = current->next;
        count++;
    }

    printf("+-------------------------------------------------------------------------------+\n");
    printf("Total nodes: %d\n", count);
}
 
/**
 * @brief Trie une pile de 3 éléments.
 * 
 * Cette fonction trie une pile contenant exactement 3 éléments en utilisant les instructions sa, ra et rra.
 */
void    sort_three(t_stack **a)
{
    t_stack     *biggest_node;

    biggest_node = get_biggest_node(*a);
    if ((*a)->nbr == biggest_node->nbr)
        ra(a);
    else if((*a)->next->nbr == biggest_node->nbr)
        rra(a);
    if ((*a)->next->nbr < (*a)->nbr)
        sa(a);
}

/**
 * @brief Fonction de tri principale.
 * 
 * Cette fonction délègue le tri de la pile a à la fonction appropriée en fonction de sa taille.
 * Pour les piles de taille 2 ou 3, elle utilise des fonctions de tri spécifiques. Pour les piles plus grandes, elle utilise l'algorithme `sort_biggest`.
 */
static void    sort(t_stack *a, t_stack *b)
{
    if (get_stack_size(a) == 2)
        sa(&a);
    else if (get_stack_size(a) == 3)
        sort_three(&a);
    else
        sort_biggest(&a, &b);
}

/**
 * @brief Vérifie et traite les paramètres passés en ligne de commande.
 * 
 * Cette fonction gère les différents cas d'utilisation des paramètres: un seul argument contenant des nombres séparés par des espaces, ou plusieurs arguments, chacun représentant un nombre. Elle utilise `ft_split` pour gérer le premier cas.
 * @return Un tableau de chaînes de caractères représentant les nombres à trier, ou NULL en cas d'erreur.
 */
static char **check_params(int argc, char **argv)
{
    char **split_argv;
    
    split_argv = NULL; // Important: utiliser une variable temporaire
    if (argc == 2) 
    {
        split_argv = ft_split(argv[1], ' ');
        if (!split_argv) { // Gérer l'erreur d'allocation de ft_split
            ft_putstr_fd("Error\n", 2);
            return (NULL);
        }
        argv = split_argv;
    } 
    else if (argc > 2) 
        argv++;
    return (argv);
}

int main(int argc, char **argv)
{
    t_stack     *a;
    t_stack     *b;

    a = NULL;      
    b = NULL;
    if (argc == 1 || (argc == 2 && !argv[1][0]))
         return (1);
    argv = check_params(argc, argv);
    if (!argv) 
        return (1);
    init_stack_a(argv, &a);
    if (!is_stack_sorted(a))
        sort(a, b);
    if (argc == 2)
        free_split_memory(argv);
    free_stack_memory(&a);
    return (0);
}
