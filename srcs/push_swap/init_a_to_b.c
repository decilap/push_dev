#include "./../../includes/push_swap.h"

/**
 * @brief Définit le nœud cible pour chaque nœud de la pile `a` dans la pile `b`.
 * 
 * Pour chaque nœud de `a`, cette fonction trouve le nœud le plus proche dans `b` qui est plus petit.
 * Si aucun nœud plus petit n'est trouvé, le nœud cible devient le plus grand nœud de `b`.
 * @param a Un pointeur vers la tête de la pile a.
 * @param b Un pointeur vers la tête de la pile b.
 */
static void     set_target_a(t_stack *a, t_stack *b) {
    t_stack *current_b;
    t_stack *target_node;
    long best_match_index;

    while (a) {
        best_match_index = LONG_MIN;
        target_node = NULL;  // Réinitialisation pour chaque nœud de A
        current_b = b;
        while (current_b) {
            if (current_b->nbr < a->nbr && current_b->nbr > best_match_index)
            {
                best_match_index = current_b->nbr;
                target_node = current_b;
            }
            current_b = current_b->next;
        }
        if (target_node == NULL)
            a->target_node = get_biggest_node(b);
        else
            a->target_node = target_node;
        a = a->next;
    }
}


/**
 * @brief Cette fonction identifie et marque le nœud le moins coûteux à déplacer de la pile `a` vers `b`.
 *        Elle parcourt la pile `a`, compare les coûts de push de chaque nœud, et marque le nœud
 *        ayant le coût minimal comme étant le nœud le moins coûteux.
 */
static void     set_cheapest_node(t_stack *stack) 
{
    long cheapest_value = LONG_MAX; 
    t_stack *cheapest_node = NULL;

    if (!stack)
        return ;

    while (stack) 
    {
        if (stack->push_cost < cheapest_value) 
        {
            cheapest_value = stack->push_cost; 
            cheapest_node = stack; 
        }
        stack = stack->next; 
    }

    if (cheapest_node) 
        cheapest_node->cheapest = true; 
}

/**
 * @brief Cette fonction calcule l'index et la position par rapport à la médiane de chaque nœud de la pile.
 *        Elle parcourt la pile et affecte à chaque nœud son index (position dans la pile) et un booléen
 *        indiquant s'il se trouve au-dessus ou en-dessous de la médiane.
 */
void    current_position(t_stack *stack)
{
    int i ;
    int median;
    int size;

    if (!stack)
        return ;
    i = 0; 
    size = get_stack_size(stack);
    median = size / 2; 
    while (stack) 
    {
        stack->index = i; 
        stack->above_median = (i <= median); // Attribuer directement la médiane
        stack = stack->next; 
        ++i;
    }
}

/**
 * @brief Cette fonction prépare la pile `a` pour le tri en définissant les nœuds cibles, 
 *        les coûts de push et en identifiant le nœud le moins coûteux. Elle utilise les fonctions
 *        `set_target_a`, `cost_analysis_a` et `set_cheapest_node`.
 */
void	init_nodes_a(t_stack *a, t_stack *b) //Define a function that combines all the functions needed to prepare stack `a`, ready for our pushing and sorting. These functions set the data inside the node's structure
{
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest_node(a);
}
