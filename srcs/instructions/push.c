#include "./../../includes/push_swap.h"

static void push(t_stack **dst, t_stack **src) {
    if (!*src) // Si la pile b est vide, rien à faire
        return;
    t_stack *node = *src;
    *src = (*src)->next; // Mise à jour de la pile b (le premier élément est supprimé)
    node->next = *dst; // Le premier élément de b devient le premier de a
    *dst = node; // Mise à jour de la tête de la pile a

    current_position(*dst);
    current_position(*src);
}

static void rev_push_stack(t_stack **dst, t_stack **src, char *operation) {
    push(dst, src);
    ft_putstr_fd(operation, 1);
}

void    pa(t_stack **a, t_stack **b)
{
    rev_push_stack(a, b, "pa\n");
}

void    pb(t_stack **b, t_stack **a)
{
    rev_push_stack(b, a, "pb\n");
}
