#ifndef OUTILS_H_INCLUDED
#define OUTILS_H_INCLUDED

///Converti un nombre d�cimal en binaire + compte le nombre de 1 dans le nombre binaire obtenu (=nbr d'ar�tes)
int convertisseur_binaire(int nbr_binaire[], int nbr, int taille);
///R�alise un calcul de puissance de 2
int puissance(int nbr);
///Comparaison de 2 Ar�tes par rapport � 1 pond�ration
int ComparaisonAretes(Combinaison* comb1, Combinaison* comb2, int clef);


#endif // OUTILS_H_INCLUDED
