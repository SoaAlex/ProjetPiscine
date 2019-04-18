#include <queue>
#include <algorithm>
#include "objet/graphe.h"
#include "outils.h"

///Prim : 1�re partie
void Graphe::PrimComplet(int s0)
{
    Graphe* graphePoidMin;
    std::string nom_output;
    for (size_t i=0;i<m_coutTotal.size();i++)
    {
        nom_output.clear();
        graphePoidMin=this->Prim(i,s0);
        nom_output.append("outputPrim");
        nom_output.append(std::to_string(i));
        nom_output.append(".svg");
        graphePoidMin->affichage(nom_output);
    }
}

///Double Pond�ration : 2�me partie
std::vector<Combinaison*> Graphe::doublePonderation()
{
    ///Cr�ation tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    int ponderation=m_coutTotal.size();
    bool binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'ar�te) = nbr de combinaisons
    int verif1;
    size_t verif2;
    int supprimer;

    std::vector<Arete*> aretes;///Tableau des ar�tes (routes cyclables) des combinaisons
    std::vector<float> coutTotaux;///Pour calculer les totaux des pond�rations
    std::vector<float> maxcoutTotaux;
    std::vector<float> mincoutTotaux;
    for(int i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
        maxcoutTotaux.push_back({0});
        mincoutTotaux.push_back({10000});
    }
    for(int i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
    }
    bool elimine = false;///Domin�e ou non domin�e (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i) //MANHATTAN : 16.8 millions de combinaisons / 24 ar�tes / 16 sommets // 2 600 000 combinaisons cr��es
    {
        ///Compteur binaire
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue � toutes les cases du tableau entre "d�but" et "n" la valeur "val" : fill_n(d�but, n, val)
        verif1 = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion d�cimal=>binaire + compte du nombre de 1 dans le nombre binaire (=nbr d'ar�tes)

        if(verif1 == (m_sommets.size()-1))///Si nombre d'ar�te == nbr sommets - 1
        {
            for(size_t j=0; j<m_aretes.size(); ++j)
            {
                if(binaire[j] == 1)
                {
                    aretes.push_back(m_aretes[j]);///Ajout des ar�tes

                }
            }

            ///V�rification connexit� (BFS)
            verif2 = Graphe::connexiteBFS(aretes);

            if(verif2 == m_sommets.size()) ///Si connexe
            {
                ///Cr�ation de la combinaison
                sousGraphes.push_back(new Combinaison{aretes, coutTotaux, elimine});
            }
        }

        ///R�initialisation des variables
        aretes.clear();
    }

    ///Calcul des pond�ration totales
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        std::fill_n(coutTotaux.begin(), ponderation, 0);///Mise � 0

        for(const auto ar: comb->getAretes())///Parcours des ar�tes
        {
            for(int i=0; i<ponderation; ++i)
            {
                coutTotaux[i] = coutTotaux[i] + ar->getPonderations(i);
            }
        }
        comb->calculTotPond(coutTotaux);
        for(int i=0; i<ponderation; ++i)
        {
            if (coutTotaux[i]>maxcoutTotaux[i])
            {
                maxcoutTotaux[i]=coutTotaux[i];
            }
            if (coutTotaux[i]<mincoutTotaux[i])
            {
                mincoutTotaux[i]=coutTotaux[i];
            }
        }
    }

    ///Elimination des combinaisons domin�es
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas �limin�e
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                supprimer = 1;
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    for(int i=0; i<ponderation; ++i)
                    {
                        verif1 = ComparaisonAretes(comb1, comb2, i);
                        if(verif1 == 2)
                        {
                            supprimer = 0;
                        }
                    }
                    if(supprimer == 1)
                    {
                        comb2->setElimine(true);
                    }
                }
            }
        }
    }

    Svgfile svgout{"outputPareto.svg",1000,1000};
    std::vector<Combinaison*> combichoisies;
    for (const auto comb: sousGraphes)
    {
        if (!comb->getElimine())
        {
            combichoisies.push_back(comb);
        }
    }
    std::sort(combichoisies.begin(),combichoisies.end(),comparaison);
    float echellex=520/(maxcoutTotaux[0]-mincoutTotaux[0]);
    float echelley=520/(maxcoutTotaux[1]-mincoutTotaux[1]);
    float milieux=((maxcoutTotaux[0]-mincoutTotaux[0])/2)+mincoutTotaux[1];
    float milieuy=((maxcoutTotaux[1]-mincoutTotaux[1])/2)+mincoutTotaux[1];
    svgout.addRepere(maxcoutTotaux[0],maxcoutTotaux[1],mincoutTotaux[0],mincoutTotaux[1]);
    int nombre_afficher=0;
    //Test
    for(const auto comb: sousGraphes)
    {
        //comb->afficher();
        comb->afficher(svgout,echellex,echelley,mincoutTotaux[0],mincoutTotaux[1],milieux,milieuy);
    }
    for(const auto comb: combichoisies)
    {
        //comb->afficher();
        comb->afficherSelec(svgout,echellex,echelley,nombre_afficher,m_sommets,mincoutTotaux[0],mincoutTotaux[1]);
    }
    //system("pause");
    //FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}

///Optimisation bi-objectif co�t / distance : 3�me partie
std::vector<Combinaison*> Graphe::cout_distance(int ponderation)
{
    ///Cr�ation tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    bool binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'ar�te) = nbr de combinaisons
    int verif1;
    size_t verif2;
    bool supprimer;
    int distanceTotale;

    std::vector<Arete*> aretes;///Tableau des ar�tes (routes cyclables) des combinaisons
    std::vector<float> coutTotaux;///Pour calculer les totaux des pond�rations
    std::vector<float> maxcoutTotaux;
    std::vector<float> mincoutTotaux;
    for(int i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
        maxcoutTotaux.push_back({0});
        mincoutTotaux.push_back({10000});
    }
    for(int i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
    }
    bool elimine = false;///Domin�e ou non domin�e (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i)
    {
        ///Compteur binaire
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue � toutes les cases du tableau entre "d�but" et "n" la valeur "val" : fill_n(d�but, n, val)
        verif1 = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion d�cimal=>binaire + compte du nombre de 1 dans le nombre binaire (=nbr d'ar�tes)

        for(size_t j=0; j<m_aretes.size(); ++j)
        {
            if(binaire[j] == 1)
            {
                aretes.push_back(m_aretes[j]);///Ajout des ar�tes

            }
        }

        ///V�rification connexit� (BFS)
        verif2 = Graphe::connexiteBFS(aretes);

        if(verif2 == m_sommets.size()) ///Si connexe
        {
            ///Cr�ation de la combinaison
            sousGraphes.push_back(new Combinaison{aretes, coutTotaux, elimine});
        }
        ///R�initialisation des variables
        aretes.clear();
    }

    ///Calcul des pond�rations totales
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        std::fill_n(coutTotaux.begin(), ponderation, 0);///Mise � 0

        for(const auto ar: comb->getAretes())///Parcours des ar�tes
        {
            for(int i=0; i<ponderation; ++i)
            {
                if(i != 1)
                {
                    coutTotaux[i] = coutTotaux[i] + ar->getPonderations(i);
                }
            }
        }
        ///Calcul des distances totales de sommet � sommet
        for(const auto som: m_sommets)
        {
            distanceTotale = distanceTotale + Dijkstra(comb->getAretes(), som->getID(), 1);
        }
        coutTotaux[1] = distanceTotale;
        comb->calculTotPond(coutTotaux);
        distanceTotale = 0;
        for(int i=0; i<ponderation; ++i)
        {
            if (coutTotaux[i]>maxcoutTotaux[i])
            {
                maxcoutTotaux[i]=coutTotaux[i];
            }
            if (coutTotaux[i]<mincoutTotaux[i])
            {
                mincoutTotaux[i]=coutTotaux[i];
            }
        }
    }

    ///Elimination des combinaisons domin�es
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas �limin�e
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                supprimer = 1;
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    for(int i=0; i<ponderation; ++i)
                    {
                        verif1 = ComparaisonAretes(comb1, comb2, i);
                        if(verif1 == 2)
                        {
                            supprimer = 0;
                        }
                    }
                    if(supprimer == 1)
                    {
                        comb2->setElimine(true);
                    }
                }
            }
        }
    }

    Svgfile svgout{"outputPareto.svg",1000,1000};
    std::vector<Combinaison*> combichoisies;
    for (const auto comb: sousGraphes)
    {
        if (!comb->getElimine())
        {
            combichoisies.push_back(comb);
        }
    }
    std::sort(combichoisies.begin(),combichoisies.end(),comparaison);
    float echellex=520/(maxcoutTotaux[0]-mincoutTotaux[0]);
    float echelley=520/(maxcoutTotaux[1]-mincoutTotaux[1]);
    float milieux=((maxcoutTotaux[0]-mincoutTotaux[0])/2)+mincoutTotaux[1];
    float milieuy=((maxcoutTotaux[1]-mincoutTotaux[1])/2)+mincoutTotaux[1];
    svgout.addRepere(maxcoutTotaux[0],maxcoutTotaux[1],mincoutTotaux[0],mincoutTotaux[1]);
    int nombre_afficher=0;
    //Test
    for(const auto comb: sousGraphes)
    {
        //comb->afficher();
        comb->afficher(svgout,echellex,echelley,mincoutTotaux[0],mincoutTotaux[1],milieux,milieuy);
    }
    for(const auto comb: combichoisies)
    {
        //comb->afficher();
        comb->afficherSelec(svgout,echellex,echelley,nombre_afficher,m_sommets,mincoutTotaux[0],mincoutTotaux[1]);
    }
    //system("pause");
    //FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}
