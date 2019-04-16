#include <iostream>

///Convertisseur binaire
void convertisseur_binaire(int nbr_binaire[], int nbr, int taille)
{
    int reste;

    for(int i=0; i<taille; ++i)
    {
        reste = nbr % 2;
        nbr = ((nbr-reste)/2);
        nbr_binaire[i] = reste;
    }
}
