#include "./../../includes/push_swap.h"

/**
 * @brief Calcule la taille de la pile.
 * 
 * Parcourt la pile et compte le nombre de nœuds.
 * @param stack Un pointeur vers le premier nœud de la pile.
 * @return La taille de la pile (nombre de nœuds).
 */
int get_stack_size(t_stack *stack)
{
    int     count;

    if (!stack)
        return (0);
    count = 0;
    while (stack)
    {
        stack = stack->next;
        count++;
    }
    return (count);
}

/**
 * @brief Vérifie si la pile est triée.
 * 
 * Parcourt la pile et vérifie si les nombres sont triés par ordre croissant.
 * @return 1 si la pile est triée, 0 sinon.
 */

int     is_stack_sorted(t_stack *stack)
{
    if (!stack)
        return (0);
    while (stack->next)
    {
       if (stack->nbr > stack->next->nbr)
            return (0); 
       stack = stack->next;
    }
    return (1);
}

/**
 * @brief Récupère le dernier nœud de la pile.
 * 
 * Parcourt la pile jusqu'au dernier nœud.
 * @return Un pointeur vers le dernier nœud de la pile, ou NULL si la pile est vide.
 */

t_stack     *get_last_node(t_stack *stack)
{
    if (!stack)
        return (NULL);
    while (stack->next)
       stack = stack->next;
    return (stack);
}

/**
 * @brief Récupère le nœud contenant le plus grand nombre de la pile.
 * 
 * Parcourt la pile et trouve le nœud contenant le plus grand nombre.
 * @param stack Un pointeur vers le premier nœud de la pile.
 * @return Un pointeur vers le nœud contenant le plus grand nombre, ou NULL si la pile est vide.
 */
t_stack     *get_biggest_node(t_stack *stack)
{
    int    max;
	t_stack	*max_node;

	if (!stack)
		return (NULL);
	max = INT_MIN;
    while (stack)
    {
        if (stack->nbr > max)
        {
            max = stack->nbr;
            max_node = stack;
        }
        stack = stack->next;
    }
    return (max_node);
}

/**
 * @brief Récupère le nœud contenant le plus petit nombre de la pile.
 * 
 * Parcourt la pile et trouve le nœud contenant le plus petit nombre.
 * @param stack Un pointeur vers le premier nœud de la pile.
 * @return Un pointeur vers le nœud contenant le plus petit nombre, ou NULL si la pile est vide.
 */
t_stack     *get_smallest_node(t_stack *stack)
{
    int    min;
	t_stack	*min_node;

	if (!stack)
		return (NULL);
	min = INT_MAX;
    while (stack)
    {
        if (stack->nbr < min)
        {
            min = stack->nbr;
            min_node = stack;
        }
        stack = stack->next;
    }
    return (min_node);
}
