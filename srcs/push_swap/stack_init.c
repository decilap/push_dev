#include "./../../includes/push_swap.h"

/**
 * @brief Ajoute un nouveau nœud à la pile a.
 * 
 * @param stack Un pointeur vers la tête de la pile a.
 * @param n La valeur du nombre à ajouter.
 */
static void	add_node_to_a(t_stack **stack, int n)
{
	t_stack	*node;
	t_stack	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack));
	if (!node)
		return ;
	node->next = NULL;
	node->nbr = n;
	if (!(*stack))
		*stack = node;
	else
    {
		last_node = get_last_node(*stack);
		last_node->next = node; 
	}
}

/**
 * @brief Récupère le nœud le moins coûteux à déplacer de la pile.
 * 
 * @param stack Un pointeur vers la tête de la pile.
 * @return Un pointeur vers le nœud le moins coûteux, ou NULL si la pile est vide.
 */
t_stack	*get_cheapest_node(t_stack *stack) 
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/**
 * @brief Prépare la pile pour le push en déplaçant le nœud cible vers le sommet.
 * 
 * @param stack Un pointeur vers la tête de la pile.
 * @param top_node Le nœud cible à déplacer vers le sommet.
 * @param stack_name Le nom de la pile ('a' ou 'b').
 */
void    prep_for_push(t_stack **stack, t_stack *top_node, char stack_name) // Définit une fonction qui déplace le nœud requis vers le sommet de la pile
{
    while (*stack != top_node) // Tant que le nœud requis n'est pas déjà le premier nœud
    {
        if (stack_name == 'a') // Si ce n'est pas le cas, et que c'est la pile `a`, exécuter ce qui suit
        {
            if (top_node->above_median)
                ra(stack);
            else
                rra(stack);
        }
        else if (stack_name == 'b') // Si ce n'est pas le cas, et que c'est la pile `b`, exécuter ce qui suit
        {
            if (top_node->above_median)
                rb(stack);
            else
                rrb(stack);
        }   
    }
}

/**
 * @brief Initialise la pile a à partir d'un tableau de chaînes de caractères.
 * 
 * @param str Un tableau de chaînes de caractères représentant les nombres à ajouter à la pile.
 * @param a Un pointeur vers la tête de la pile a.
 */
void    init_stack_a(char **str, t_stack **a)
{
    long nbr;
    char **ptr;

    ptr = str;
    while (*ptr)
    {   
        nbr = (long)ft_atoi(*ptr);
        if (!ft_isnumber(*ptr))
            handle_stack_error(a);
        else if(check_duplicate_error(nbr, str, ptr -str))
            handle_stack_error(a);
        if (nbr < INT_MIN || nbr > INT_MAX)
            handle_stack_error(a);
        add_node_to_a(a, nbr);
        ptr++;
    }
}
