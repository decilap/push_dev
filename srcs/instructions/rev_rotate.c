#include "./../../includes/push_swap.h"

static void rev_rotate(t_stack **stack) {
    if (!*stack || !(*stack)->next) // Rien à faire si la pile est vide ou a un seul élément
        return;
    t_stack *second_last = *stack;
    while (second_last->next && second_last->next->next) // Trouver l'avant-dernier élément
        second_last = second_last->next;
    t_stack *last = second_last->next;
    second_last->next = NULL; // Le deuxième dernier élément devient le dernier
    last->next = *stack; // Le dernier élément devient le premier
    *stack = last; // Mise à jour de la tête de la pile
    current_position(*stack);
}

static void rev_rotate_stack(t_stack **stack, char *operation) {
    rev_rotate(stack);
    ft_putstr_fd(operation, 1);
}

void  rra(t_stack **a)
{
    rev_rotate_stack(a, "rra\n");
}

void    rrb(t_stack **b)
{
    rev_rotate_stack(b, "rrb\n");
}

void rrr(t_stack **a, t_stack **b) {
    rev_rotate_stack(a, "");
    rev_rotate_stack(b, "rrr\n");
}
