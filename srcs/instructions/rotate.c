#include "./../../includes/push_swap.h"

static void rotate(t_stack **stack) {
    if (!*stack || !(*stack)->next) // Rien à faire si la pile est vide ou a un seul élément
        return;

    t_stack *first;
    t_stack *temp;
    
    first = *stack;
    *stack = (*stack)->next; // Le second élément devient la tête
    temp = *stack;
    while (temp->next) // Aller au dernier élément
        temp = temp->next;
    temp->next = first; // Le premier élément devient le dernier
    first->next = NULL; // Le dernier élément n'a plus de suivant
    current_position(*stack);
}

static void rotate_stack(t_stack **stack, char *operation) {
    rotate(stack);
    ft_putstr_fd(operation, 1);
}

void    ra(t_stack **a)
{
    rotate_stack(a, "ra\n"); 
}

void  rb(t_stack **b)
{
    rotate_stack(b, "rb\n");
}

void rr(t_stack **a, t_stack **b) {
    rotate_stack(a, "");
    rotate_stack(b, "rr\n");
}
