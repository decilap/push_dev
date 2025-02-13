#include "./../../includes/push_swap.h"

/**
 * @brief Cette fonction vérifie s'il y a des doublons dans les arguments passés au programme.
 * 
 * @param num Le nombre à vérifier.
 * @param args Un tableau de chaînes de caractères contenant les arguments.
 * @param current_position La position actuelle dans le tableau args.
 * @return 1 s'il y a un doublon, 0 sinon.
 */
int     check_duplicate_error(long num, char **args, int current_position)
{
    int i;
    
    i = 0;
    // On parcourt le tableau jusqu'à la position actuelle.
    while (i < current_position) {
        if (ft_atoi(args[i]) == num)
            return (1); 
        i++;
    }
    return (0);
}

/**
 * @brief Cette fonction gère les erreurs de la pile. Elle affiche un message d'erreur, libère la mémoire allouée à la pile et quitte le programme.
 * 
 * @param a Un pointeur vers la pile.
 */
void    handle_stack_error(t_stack **a)
{
    ft_putstr_fd("Error\n", 1);
    free_stack_memory(a);
    exit(1);
}

/**
 * @brief Cette fonction libère la mémoire allouée à la pile.
 * 
 * @param a Un pointeur vers la pile.
 */
void    free_stack_memory(t_stack **a)
{
    t_stack *temp;
    t_stack *current;

    if (!a)
        return ;
    current = *a;
    while (current)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
    *a = NULL;
}

/**
 * @brief Cette fonction libère la mémoire allouée par ft_split.
 * 
 * @param split Un tableau de chaînes de caractères alloué par ft_split.
 */
void    free_split_memory(char **split) {
    int i;

    if (!split)
        return;
    i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}
