#include <iostream>
#include "std/objet/graphe.h"

int main()
{
    Graphe graphe("manhattan.txt", "manhattan_weights_0.txt");
    graphe.testAfficher();
    return 0;
}
