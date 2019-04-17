#ifndef OUTILS_H_INCLUDED
#define OUTILS_H_INCLUDED

///Converti un nombre décimal en binaire + compte le nombre de 1 dans le nombre binaire obtenu (=nbr d'arêtes)
int convertisseur_binaire(int nbr_binaire[], int nbr, int taille);
///Réalise un calcul de puissance de 2
int puissance(int nbr);
///Comparaison de 2 Arêtes par rapport à 1 pondération
int ComparaisonAretes(Combinaison* comb1, Combinaison* comb2, int clef);


#endif // OUTILS_H_INCLUDED
