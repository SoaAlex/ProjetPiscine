#include "std/objet/graphe.h"

int main()
{
    Graphe graphe("manhattan.txt", "manhattan_weights_0.txt");
    graphe.affichage();
    Graphe* graphePoidMin=graphe.Prim(CoutFinancier);
    graphePoidMin->affichage("ouputPrim.svg");
    Graphe* graphePoidMin2=graphe.Prim(CoutEnvironnement);
    graphePoidMin2->affichage("ouputPrim2.svg");
    return 0;
}
