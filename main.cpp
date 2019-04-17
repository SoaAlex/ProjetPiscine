#include "std/objet/graphe.h"

int main()
{
    Graphe graphe("broadway.txt", "broadway_weights_0.txt");
    graphe.affichage();
    graphe.PrimComplet(0);
    graphe.doublePonderation(2);
    return 0;
}
