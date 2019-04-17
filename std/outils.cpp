#include <iostream>
#include "objet/combinaison.h"

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

///R�alise un calcul de puissance de 2
int puissance(int nbr)
{
    int resultat = 2;
    for(size_t i=0; i<(nbr-1); ++i)
    {
        resultat = resultat*2;
    }
    return(resultat);
}

///Comparaison de 2 combinaisons par rapport � 1 pond�ration totale, 0 : inf�rieure, 1 : �gale, 2 : sup�rieure
int ComparaisonAretes(Combinaison* comb1, Combinaison* comb2, int clef)
{
    if(comb1->getTotPond()[clef] <= comb2->getTotPond()[clef])
    {
        return(0);
    }
    if(comb1->getTotPond()[clef] == comb2->getTotPond()[clef])
    {
        return(1);
    }
    if(comb1->getTotPond()[clef] >= comb2->getTotPond()[clef])
    {
        return(2);
    }
}
