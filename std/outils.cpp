#include <iostream>

///Convertisseur binaire
int convertisseur_binaire(int nbr_binaire[], int nbr, int taille)
{
    int reste;
    int verif = 0;

    for(int i=0; i<taille; ++i)
    {
        reste = nbr % 2;
        nbr = ((nbr-reste)/2);
        nbr_binaire[i] = reste;
        if(reste == 1)
        {
            verif = verif + 1;
        }
    }

    return(verif);
}

int puissance(int nbr)
{
    int resultat = 2;
    for(size_t i=0; i<(nbr-1); ++i)
    {
        resultat = resultat*2;
    }
    return(resultat);
}

