#include "./../includes/push_swap.h"

// Calcule le coût pour déplacer un élément vers le haut ou le bas de la pile.
// Le coût est la distance minimale entre l'index actuel et le haut ou le bas de la pile.
static int	calculate_cost(int index, int len)
{
	return (index <= len / 2) ? index : len - index;
}

// Calcule le coût pour pousser un nœud de la pile 'a' vers la pile 'b'.
// Le coût est basé sur la distance à parcourir dans les deux piles pour atteindre les positions cibles.
// Si les nœuds sont du même côté de la médiane dans les deux piles, le coût est le maximum des distances.
// Sinon, le coût est la somme des distances.
// Si le nœud cible est NULL (pas de cible dans 'b'), le coût est simplement la distance dans 'a'.
static void calc_push_cost(t_stack *node, int len_a, int len_b) {
    if (!node || !node->target_node) {  // Gestion du cas où node ou target_node est NULL
        node->push_cost = calculate_cost(node->index, len_a);
        return;
    }

    int cost_a = calculate_cost(node->index, len_a);
    int cost_b = calculate_cost(node->target_node->index, len_b);

    // Simplification avec des ternaires
    node->push_cost = (
        (node->above_median == node->target_node->above_median) ?
        ((cost_a > cost_b) ? cost_a : cost_b) :
        (cost_a + cost_b)
    );
}

// Calcule le coût de push pour chaque nœud de la pile 'a'.
// Itère sur la pile 'a' et appelle `calc_push_cost` pour chaque nœud.
void     cost_analysis_a(t_stack *a, t_stack *b) {
    
    int len_a;
    int len_b;

    len_a = get_stack_size(a);
    len_b = get_stack_size(b);
    while (a)
    {
        calc_push_cost(a, len_a, len_b);
        a = a->next;
    }
}

