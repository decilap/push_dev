\documentclass[a4paper,12pt]{article}
\usepackage[utf8]{inputenc} 
\usepackage[T1]{fontenc} 
\usepackage[french]{babel}
\usepackage{listings}
\usepackage{hyperref}
\usepackage{enumitem}
\usepackage{geometry}
\geometry{margin=2cm}
\title{Documentation Complète du Projet \texttt{push\_swap}}
\author{}
\date{}

\begin{document}
\maketitle

\section{Introduction}
Ce document présente la documentation complète du projet \texttt{push\_swap}, un algorithme de tri optimisé en C qui opère sur des piles. Il s'appuie sur l'analyse du coût de chaque mouvement et sur la détermination d'un nœud cible (\textit{target\_node}) afin d'insérer chaque élément à la bonne position pour obtenir un ordre croissant.

\section{Structure de Données Principale}

\subsection{\texttt{t\_stack}}
Chaque élément de la pile est représenté par la structure \texttt{t\_stack} :

\begin{lstlisting}[language=C]
typedef struct s_stack {
    int                 nbr;          // Le nombre à trier.
    int                 index;        // La position du nœud dans la pile.
    int                 push_cost;    // Coût total (nombre de commandes) pour déplacer le nœud.
    bool                above_median; // Indique si le nœud se situe dans la première moitié de la pile.
    bool                cheapest;     // Marque le nœud le moins coûteux à déplacer.
    struct s_stack     *target_node;  // Nœud cible dans l’autre pile pour une insertion ordonnée.
    struct s_stack     *next;         // Pointeur vers le nœud suivant.
} t_stack;
\end{lstlisting}

\subsubsection*{Champs de la structure}
\begin{itemize}[label=\textbullet]
  \item \textbf{nbr} : La valeur entière à trier.
  \item \textbf{index} : La position dans la pile, mise à jour par la fonction \texttt{current\_position}.
  \item \textbf{push\_cost} : Le nombre de mouvements (rotations/push) nécessaires pour déplacer le nœud à sa position cible.
  \item \textbf{above\_median} : Indique si le nœud se trouve dans la première moitié de la pile (utile pour optimiser les rotations).
  \item \textbf{cheapest} : Indique que ce nœud est le moins coûteux à déplacer.
  \item \textbf{target\_node} : Pointeur vers le nœud dans l’autre pile où cet élément doit être inséré.
  \item \textbf{next} : Pointeur vers le nœud suivant dans la pile.
\end{itemize}

\section{Modules et Fonctions d'Instructions}

\subsection{Rotation (srcs/instructions/rotate.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{rotate(t\_stack **stack)}} : Vérifie que la pile contient au moins deux éléments, déplace le premier élément en fin de pile et met à jour la position des nœuds via \texttt{current\_position}.
  \item \textbf{\texttt{rotate\_stack(t\_stack **stack, char *operation)}} : Appelle \texttt{rotate} puis affiche l'opération (ex. ``ra\textbackslash n'' ou ``rb\textbackslash n'').
  \item \textbf{\texttt{ra(t\_stack **a)}} et \textbf{\texttt{rb(t\_stack **b)}} : Appliquent la rotation à la pile A ou B.
  \item \textbf{\texttt{rr(t\_stack **a, t\_stack **b)}} : Effectue une rotation simultanée sur les deux piles.
\end{itemize}

\subsection{Push (srcs/instructions/push.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{push(t\_stack **dst, t\_stack **src)}} : Déplace le premier élément de la pile \texttt{src} vers \texttt{dst} et met à jour les positions dans les deux piles via \texttt{current\_position}.
  \item \textbf{\texttt{rev\_push\_stack(t\_stack **dst, t\_stack **src, char *operation)}} : Enveloppe l'appel à \texttt{push} et affiche l'opération réalisée.
  \item \textbf{\texttt{pa(t\_stack **a, t\_stack **b)}} : Pousse le nœud du haut de la pile B vers la pile A.
  \item \textbf{\texttt{pb(t\_stack **b, t\_stack **a)}} : Pousse le nœud du haut de la pile A vers la pile B.
\end{itemize}

\subsection{Reverse Rotate (srcs/instructions/rev\_rotate.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{rev\_rotate(t\_stack **stack)}} : Vérifie la présence d'au moins deux éléments, retire le dernier nœud de la pile et le place en tête.
  \item \textbf{\texttt{rev\_rotate\_stack(t\_stack **stack, char *operation)}} : Appelle \texttt{rev\_rotate} et affiche l'opération correspondante.
  \item \textbf{\texttt{rra(t\_stack **a)}} et \textbf{\texttt{rrb(t\_stack **b)}} : Appliquent la rotation inversée sur la pile A ou B.
  \item \textbf{\texttt{rrr(t\_stack **a, t\_stack **b)}} : Effectue une rotation inversée simultanée sur les deux piles.
\end{itemize}

\subsection{Swap (srcs/instructions/swap.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{swap(t\_stack **head)}} : Échange les deux premiers nœuds de la pile (si au moins deux éléments sont présents) et met à jour la position via \texttt{current\_position}.
  \item \textbf{\texttt{rev\_swap\_stack(t\_stack **stack, char *operation)}} : Enveloppe l'appel à \texttt{swap} et affiche l'opération (ex. ``sa\textbackslash n'' ou ``sb\textbackslash n'').
  \item \textbf{\texttt{sa(t\_stack **a)}} et \textbf{\texttt{sb(t\_stack **b)}} : Appliquent l'échange sur la pile A ou B.
  \item \textbf{\texttt{ss(t\_stack **a, t\_stack **b)}} : Effectue un échange simultané sur les deux piles.
\end{itemize}

\section{Initialisation et Gestion de la Pile}

\subsection{Initialisation de la Pile A (srcs/push\_swap/stack\_init.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{add\_node\_to\_a(t\_stack **stack, int n)}} : Alloue un nouveau nœud avec la valeur \texttt{n} et l'ajoute à la fin de la pile.
  \item \textbf{\texttt{init\_stack\_a(char **str, t\_stack **a)}} : Parcourt le tableau de chaînes de caractères, convertit chaque chaîne en entier, vérifie les erreurs de format, de doublon ou de dépassement de limites (\texttt{INT\_MIN}/\texttt{INT\_MAX}), et construit la pile A en appelant \texttt{add\_node\_to\_a}.
  \item \textbf{\texttt{get\_cheapest\_node(t\_stack *stack)}} : Parcourt la pile et renvoie le nœud marqué comme le moins coûteux (\texttt{cheapest == true}).
  \item \textbf{\texttt{prep\_for\_push(t\_stack **stack, t\_stack *top\_node, char stack\_name)}} : Effectue les rotations nécessaires pour positionner le nœud \texttt{top\_node} en tête de pile. Utilise \texttt{ra/rra} ou \texttt{rb/rrb} selon que la pile est A ou B.
\end{itemize}

\subsection{Affichage et Tri (srcs/push\_swap/stack.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{print\_stack(t\_stack *head)}} : Affiche la pile sous forme de tableau (index, valeur, push\_cost, etc.).
  \item \textbf{\texttt{sort\_three(t\_stack **a)}} : Pour une pile de 3 éléments, utilise une combinaison de \texttt{ra}, \texttt{rra} et \texttt{sa} pour trier.
  \item \textbf{\texttt{sort(t\_stack *a, t\_stack *b)}} : Choisit la méthode de tri selon la taille de la pile :
    \begin{itemize}
      \item \textbf{2 éléments} : échange simple (\texttt{sa}).
      \item \textbf{3 éléments} : utilisation de \texttt{sort\_three}.
      \item \textbf{Plus de 3 éléments} : utilisation de \texttt{sort\_biggest}.
    \end{itemize}
  \item \textbf{\texttt{check\_params(int argc, char **argv)}} : Gère l'entrée des paramètres (possibilité d'un argument unique contenant plusieurs nombres).
  \item \textbf{\texttt{main(int argc, char **argv)}} : Point d'entrée du programme. Initialise les piles A et B, vérifie et prépare les paramètres, effectue le tri si nécessaire, et libère la mémoire.
\end{itemize}

\section{Algorithme de Tri pour Grandes Piles}

\subsection{Stratégie Globale (srcs/push\_swap/stack\_sort\_biggest.c)}
Pour trier des piles de grande taille, l'algorithme suit plusieurs phases :

\subsubsection*{Phase 1 : Réduction de la Pile A}
\begin{itemize}[label=\textbullet]
  \item \textbf{Pousser des éléments de A vers B} : Pour simplifier le problème, certains éléments sont d'abord déplacés de la pile A vers B en utilisant \texttt{pb}.
\end{itemize}

\subsubsection*{Phase 2 : Analyse des Coûts et Détermination du Nœud à Déplacer}
\begin{itemize}[label=\textbullet]
  \item \textbf{Définir le \texttt{target\_node} pour chaque nœud de A} : Avec \texttt{set\_target\_a}, pour chaque nœud de A, on cherche dans B le nœud le plus proche ayant une valeur inférieure. Si aucun nœud plus petit n'est trouvé, le nœud cible devient le plus grand élément de B.
  \item \textbf{Calculer le coût (\texttt{push\_cost})} :
  \begin{itemize}[label=\textbullet]
    \item La fonction \texttt{calculate\_cost} détermine le nombre minimal de rotations pour amener un nœud en tête.
    \item Si le nœud et son \texttt{target\_node} se trouvent du même côté de la médiane, le coût est le maximum des deux distances (optimisation via \texttt{rr} ou \texttt{rrr}).
    \item Sinon, le coût est la somme des deux distances.
  \end{itemize}
  \item \textbf{Marquage du nœud le moins coûteux} : La fonction \texttt{set\_cheapest\_node} parcourt la pile A et marque le nœud ayant le coût minimal.
\end{itemize}

\subsubsection*{Phase 3 : Déplacement Contrôlé entre les Piles}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{move\_a\_to\_b}} : Effectue les rotations nécessaires sur les deux piles pour amener :
  \begin{itemize}[label=\textbullet]
    \item Le nœud le moins coûteux en tête de A.
    \item Son \texttt{target\_node} en tête de B.
  \end{itemize}
  Une fois ces positions atteintes, l'élément est poussé de A vers B via \texttt{pb}.
  \item \textbf{\texttt{move\_b\_to\_a}} : Lors de la phase de réinsertion, pour chaque élément en haut de B, la pile A est tournée afin de positionner son \texttt{target\_node} en tête, puis l'élément est poussé dans A via \texttt{pa}.
\end{itemize}

\subsubsection*{Phase 4 : Finalisation}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{min\_on\_top}} : La pile A est tournée de sorte que le plus petit élément se retrouve en tête, assurant ainsi l'ordre croissant.
\end{itemize}

\section{Fonctions Utilitaires et Gestion des Erreurs}

\subsection{Utilitaires de Pile (srcs/push\_swap/stack\_utils.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{get\_stack\_size(t\_stack *stack)}} : Retourne le nombre total de nœuds dans la pile.
  \item \textbf{\texttt{is\_stack\_sorted(t\_stack *stack)}} : Vérifie que la pile est triée en ordre croissant.
  \item \textbf{\texttt{get\_last\_node(t\_stack *stack)}} : Retourne le dernier nœud de la pile.
  \item \textbf{\texttt{get\_biggest\_node(t\_stack *stack)}}} et \textbf{\texttt{get\_smallest\_node(t\_stack *stack)}} : Renvoient respectivement le nœud ayant la plus grande ou la plus petite valeur.
\end{itemize}

\subsection{Gestion des Erreurs (srcs/push\_swap/stack\_errors.c)}
\begin{itemize}[label=\textbullet]
  \item \textbf{\texttt{check\_duplicate\_error(long num, char **args, int current\_position)}} : Vérifie s'il existe des doublons parmi les arguments passés.
  \item \textbf{\texttt{handle\_stack\_error(t\_stack **a)}} : Affiche un message d'erreur, libère la mémoire de la pile et termine le programme.
  \item \textbf{\texttt{free\_stack\_memory(t\_stack **a)}} : Libère la mémoire allouée pour chaque nœud de la pile.
  \item \textbf{\texttt{free\_split\_memory(char **split)}} : Libère la mémoire allouée par \texttt{ft\_split} lors de la séparation des arguments.
\end{itemize}

\section{Conclusion}
\begin{itemize}[label=\textbullet]
  \item \textbf{Modularité :} Le projet est organisé en modules distincts pour les opérations (rotate, push, swap, reverse rotate), l'initiation de la pile, le tri et la gestion des erreurs.
  \item \textbf{Optimisation :} L'algorithme exploite une analyse des coûts pour minimiser le nombre de mouvements. La stratégie de déterminer un \textbf{nœud cible} et de calculer le \textbf{push\_cost} permet d'effectuer des rotations combinées lorsque cela est possible, réduisant ainsi le nombre total d'opérations.
  \item \textbf{Approche Hybride :} Pour les petites piles, un tri simple suffit, tandis que pour les grandes piles, une série d'opérations optimisées assure le tri avec un minimum d'opérations, répondant ainsi aux exigences du projet \texttt{push\_swap}.
\end{itemize}

\end{document}
