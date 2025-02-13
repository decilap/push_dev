#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdbool.h> //To use bool flags, e.g, to print or not to print
# include <limits.h> //To define MIN and MAX macros
# include "../libft/libft.h"

typedef struct s_stack // Structure contenant des données entre accolades {}. `s_` pour structure
{
    int                 nbr; // Le nombre à trier
    int                 index; // La position du nombre dans la pile
    int                 push_cost; // Le nombre total de commandes
    bool                above_median; // Utilisé pour calculer `push_cost` (au-dessus de la médiane)
    bool                cheapest; // Le nœud le moins coûteux en commandes
    struct s_stack  *target_node; // Le nœud cible d'un nœud dans la pile opposée
    struct s_stack  *next; // Un pointeur vers le nœud suivant
}   t_stack; // Le "nom abrégé", "t_stack_node". `t_` pour type

// STACK ERRORS
void  handle_stack_error(t_stack **a);
void  free_stack_memory(t_stack **a);
void  free_split_memory(char **split);
int   check_duplicate_error(long num, char **args, int current_index);

// STACK INIT A TO B
void    init_nodes_a(t_stack *a, t_stack *b);
void    current_position(t_stack *stack);

// STACK COST
void     cost_analysis_a(t_stack *a, t_stack *b);

// STACK INIT
t_stack	    *get_cheapest_node(t_stack *stack);
void        init_stack_a(char **str, t_stack **a);
void        prep_for_push(t_stack **stack, t_stack *head, char stack_name);

// STACK UTILS
t_stack     *get_last_node(t_stack *stack);
t_stack     *get_biggest_node(t_stack *stack);
t_stack     *get_smallest_node(t_stack *stack);
int         get_stack_size(t_stack *stack);
int         is_stack_sorted(t_stack *stack);

// STACK INSTRUCTIONS
void			sa(t_stack **a);
void			sb(t_stack **b);
void			ss(t_stack **a, t_stack **b);
void			ra(t_stack **a);
void			rb(t_stack **b);
void			rr(t_stack **a, t_stack **b);
void			rra(t_stack **a);
void			rrb(t_stack **b);
void			rrr(t_stack **a, t_stack **b);
void			pa(t_stack **a, t_stack **b);
void			pb(t_stack **b, t_stack **a);

//ALOGORTHM
void			sort_three(t_stack **a);
void			sort_biggest(t_stack **a, t_stack **b); 


void    print_stack(t_stack *head);

#endif