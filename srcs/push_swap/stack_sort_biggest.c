#include "./../../includes/push_swap.h"

/**
 * @brief Place le plus petit élément de la pile `a` au sommet.
 * 
 * Cette fonction effectue des rotations (`ra` ou `rra`) sur la pile `a` jusqu'à ce que le plus petit
 * élément se trouve en tête de pile.  Elle utilise la fonction `get_smallest_node` pour identifier
 * le plus petit élément et vérifie son emplacement par rapport à la médiane pour optimiser les rotations.
 *
 * @param a Un pointeur vers la tête de la pile a.
 */
void	min_on_top(t_stack **a) 
{
	while ((*a)->nbr != get_smallest_node(*a)->nbr) 
{       if (get_smallest_node(*a)->above_median) 
			ra(a);
		else
			rra(a);
	}
}

/**
 * @brief Déplace le nœud le moins coûteux de la pile `a` vers la pile `b`.
 * 
 * Cette fonction identifie le nœud le moins coûteux à déplacer dans la pile `a`
 * (en utilisant `get_cheapest_node`) et effectue les rotations nécessaires pour le placer
 * au sommet avant de le pousser vers `b` avec `pb`.
 */
void move_a_to_b(t_stack **a, t_stack **b) {
    
    t_stack *cheapest_node;

    cheapest_node = get_cheapest_node(*a);
    while (*a != cheapest_node || *b != cheapest_node->target_node) {
        if ((*a != cheapest_node && cheapest_node->above_median) &&
            (*b != cheapest_node->target_node && cheapest_node->target_node->above_median)) {
            rr(a, b);
        } else if ((*a != cheapest_node && !cheapest_node->above_median) &&
                   (*b != cheapest_node->target_node && !cheapest_node->target_node->above_median)) {
            rrr(a, b);
        } else {
            prep_for_push(a, cheapest_node, 'a');
            prep_for_push(b, cheapest_node->target_node, 'b');
        }
    }
    // Pousser le nœud le moins coûteux vers la pile b
    pb(b, a);
}

/**
 * @brief Déplace le nœud du sommet de la pile `b` vers la pile `a`.
 * 
 * Cette fonction prépare la pile `a` en plaçant le nœud cible (dans `a`) du nœud au sommet de `b`
 * en haut de la pile `a` avant d'effectuer le push avec `pa`.
 * @param a Un pointeur vers la tête de la pile a.
 * @param b Un pointeur vers la tête de la pile b.
 */
void move_b_to_a(t_stack **a, t_stack **b) 
{
    prep_for_push(a, (*b)->target_node, 'a'); // S'assurer que le nœud cible de `b` dans `a` est au sommet de la pile
    pa(a, b); 
}

/**
 * @brief Définit les nœuds cibles de la pile `b` dans la pile `a` pour le tri final.
 * 
 * Pour chaque nœud de `b`, cette fonction trouve le nœud le plus proche dans `a` qui est plus grand.
 * Si aucun nœud plus grand n'est trouvé, le nœud cible devient le plus petit nœud de `a`.
 * @param a Un pointeur vers la tête de la pile a.
 * @param b Un pointeur vers la tête de la pile b.
 */
void push_b_to_a(t_stack *a, t_stack *b) {

    t_stack *current_a;
    t_stack *target_node;
    long best_match_index;

    while (b) 
    {
        best_match_index = LONG_MAX;
        target_node = NULL;
        current_a = a;
        while (current_a) 
        {
            if (current_a->nbr > b->nbr && current_a->nbr < best_match_index)
            {
                best_match_index = current_a->nbr;
                target_node = current_a;
            }
            current_a = current_a->next;
        }
        if (target_node == NULL)
            b->target_node = get_smallest_node(a);
        else
            b->target_node = target_node;
        b = b->next;
    }
}

/**
 * @brief Trie la pile `a` en utilisant un algorithme de tri par fusion.
 * 
 * Cette fonction gère le tri de la pile `a` lorsqu'elle contient plus de 3 éléments. Elle utilise
 * une approche de tri par fusion en déplaçant itérativement les éléments les moins coûteux de `a`
 * vers `b`, puis en ramenant les éléments de `b` vers `a` dans le bon ordre.
 *
 * @param a Un pointeur vers la tête de la pile a.
 * @param b Un pointeur vers la tête de la pile b.
 */
void	sort_biggest(t_stack **a, t_stack **b) 
{
	int	len_a; 

	len_a = get_stack_size(*a);
	if (len_a-- > 3) 
		pb(b, a);
	if (len_a-- > 3) 
		pb(b, a);
	while (len_a-- > 3) 
	{
		init_nodes_a(*a, *b); 
		move_a_to_b(a, b); 
	}
	sort_three(a);
	while (*b) 
	{
		push_b_to_a(*a, *b); 
		move_b_to_a(a, b);
    }
	min_on_top(a); 
}



