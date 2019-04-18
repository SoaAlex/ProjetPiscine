#include "std/objet/graphe.h"

void menu();
void selecFic(std::string &ficTopologies, std::string &ficPonderations);

int main()
{
    menu();
    return 0;
}

void menu()
{
    std::string ficTopologies = "manhattan.txt"; ///De base on a manhattan.txt
    std::string ficPonderations = "manhattan_weights_0.txt";
    int choix = 0;
    int sommetDepart;
    std::string nomVille;
    do
    {
        std::cout << "fichiers selectionnes :  "<< ficTopologies << "   " << ficPonderations << std::endl;
        Graphe graphe(ficTopologies, ficPonderations);///Recrée à chaque passage au menu principal
        graphe.affichage();
        nomVille=ficTopologies;
        nomVille[0]-=32;
        nomVille.erase(nomVille.end()-4,nomVille.end());
        ///Acceuil
        std::cout << "****************   PROJET THEORIE DES GRAPHES: Les bicylettes de Triville     ****************" << std::endl;
        std::cout << "****************       Optimisation multi-objectif et circulation douce       ****************" << std::endl;
        std::cout << "****************  NICOT Mikael - FRIEDEL Alexis - SOARES Alexandre / ING2 S4  ****************" << std::endl;
        std::cout << std::endl;
        std::cout << "Veuillez faire un choix:" << std::endl;
        std::cout << "1. Mono objectif, arbre couvrant de poids minimal PRIM" << std::endl;
        std::cout << "2. Bi-ojbectif, frontiere de Pareto optimisee BRUTE FORCE" << std::endl;
        std::cout << "3. Bi-ojbectif, cout/distances DIJKSTRA" << std::endl;
        std::cout << "4. Selections des .txt a lire" << std::endl;
        std::cout << "5. Quitter" << std::endl;
        std::cout << "Choix: ";
        do
        {
            std::cin >> choix;
            if(choix<1 || choix>6)
            {
                std::cout << "Le blindage c'est vu en ING1... Reessayez: " << std::endl;
            }
        }
        while (choix<1 || choix>6);//Blindage
        std::cout << std::endl;
        switch(choix)
        {
            case 1: ///Mono objectif prim
                std::cout<< "Choisissez le sommet de depart:";
                std::cin >> sommetDepart;
                graphe.PrimComplet(sommetDepart);
                std::cout << "Execution de l'algorithme de PRIM sur le sommet "<<sommetDepart<<" avec " << nomVille << std::endl
                          << std::endl;
                break;
            case 2:///Double Pareto
                std::cout<<"Merci de patienter (moins de 20 secondes)..."<<std::endl
                         <<std::endl;
                graphe.doublePonderation();
                std::cout << "Frontiere de Pareto etablie avec "<<nomVille<< std::endl
                          <<std::endl;
                break;
            case 3:///Cout/Distances Dijkstra
                ///....
                break;
            case 4: ///Selection fichier
                selecFic(ficTopologies, ficPonderations);
                std::cout << std::endl;
                break;
            case 5: ///Quitter
                break;
            case 6: ///Clear secret
                system("cls");
                break;
        }
    }
    while(choix != 5);//Tant qu'on quitte pas

    std::cout << "A bientot !" << std::endl;

    //return 0;
}

///Selectionne un fichier selon le choix utilisateur
void selecFic(std::string &ficTopologies, std::string &ficPonderations) //Reference aux fichiers
{
    std::cout << "Veuillez choisir une ville:" << std::endl;
    std::cout << "1. broadway" << std::endl;
    std::cout << "2. cubetown" << std::endl;
    std::cout << "3. triville" << std::endl;
    std::cout << "4. manhattan" << std::endl;
    std::cout << "Choix: ";

    ///L'utilisateur choisi le fichier topo
    int choix2 = 0;
    do
    {
        std::cin >> choix2;
        if(choix2<1 || choix2>4)
        {
            std::cout << "Le blindage c'est vu en ING1... Reessayez: " << std::endl;
        }
    }
    while (choix2<1 || choix2>4); //Blindage

    int choix3 = 0;
    ///Affectation du topo + choix ponderations

    if(choix2 == 1) ///Broadway
    {
        ficTopologies = "broadway.txt";
        std::cout << "Veuillez choisir une ponderation:" << std::endl;
        std::cout << "1. weights 0" << std::endl;
        std::cout << "2. weights 1" << std::endl;
        std::cout << "3. weights 2" << std::endl;
        std::cout << "Choix: ";

        do
        {
            std::cin >> choix3;
            if(choix3<1 || choix3>3)
            {
                std::cout << "Le blindage c'est vu en ING1... Reessayez: " << std::endl;
            }
        }
        while (choix3<1 || choix3>3); //Blindage

        if(choix3 == 1)
        {
            ficPonderations = "broadway_weights_0.txt";
        }
        if(choix3 == 2)
        {
            ficPonderations = "broadway_weights_1.txt";
        }
        if(choix3 == 3)
        {
            ficPonderations = "broadway_weights_2.txt";
        }
    }

    if(choix2 == 2)///Cubetown, 1 seul choix
    {
        ficTopologies = "cubetown.txt";
        std::cout << "weight 0 selectionne car unique disponible" << std::endl;
        ficPonderations = "cubetown_weights_0.txt";
    }

    if(choix2 == 3) ///Triville
    {
        ficTopologies = "triville.txt";
        std::cout << "Veuillez choisir une ponderation:" << std::endl;
        std::cout << "1. weights 0" << std::endl;
        std::cout << "2. weights 1" << std::endl;
        std::cout << "Choix: ";

        do
        {
            std::cin >> choix3;
            if(choix3<1 || choix3>2)
            {
                std::cout << "Le blindage c'est vu en ING1... Reessayez: " << std::endl;
            }
        }
        while (choix3<1 || choix3>2); //Blindage

        if(choix3 == 1)
        {
            ficPonderations = "triville_weights_0.txt";
        }
        if(choix3 == 2)
        {
            ficPonderations = "triville_weights_1.txt";
        }
    }

    if(choix2 == 4) ///manhattan
    {
        ficTopologies = "manhattan.txt";
        std::cout << "Veuillez choisir une ponderation:" << std::endl;
        std::cout << "1. weights 0" << std::endl;
        std::cout << "2. weights 1" << std::endl;
        std::cout << "3. weights 2" << std::endl;
        std::cout << "Choix: ";

        do
        {
            std::cin >> choix3;
            if(choix3<1 || choix3>3)
            {
                std::cout << "Le blindage c'est vu en ING1... Reessayez: " << std::endl;
            }
        }
        while (choix3<1 || choix3>3); //Blindage

        if(choix3 == 1)
        {
            ficPonderations = "manhattan_weights_0.txt";
        }
        if(choix3 == 2)
        {
            ficPonderations = "manhattan_weights_1.txt";
        }
        if(choix3 == 3)
        {
            ficPonderations = "manhattan_weights_2.txt";
        }
    }
}
