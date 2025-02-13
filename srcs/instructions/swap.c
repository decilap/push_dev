#include "./../../includes/push_swap.h"

static void swap(t_stack **head) {
    if (!*head || !(*head)->next)
        return; // Rien à faire si la pile est vide ou contient un seul élément

    t_stack *first = *head;
    t_stack *second = first->next;

    // Échange des pointeurs next
    first->next = second->next;
    second->next = first;
    *head = second; // Mise à jour systématique de la tête
    current_position(*head);
}

static void rev_swap_stack(t_stack **stack, char *operation) {
    swap(stack); // Appelle swap qui effectue l'échange
    ft_putstr_fd(operation, 1); // Affiche l'opération
}

void sa(t_stack **a) {
    rev_swap_stack(a, "sa\n");
}

void sb(t_stack **b) {
    rev_swap_stack(b, "sb\n");
}

void ss(t_stack **a, t_stack **b) {
    rev_swap_stack(a, "");
    rev_swap_stack(b, "ss\n");
}
