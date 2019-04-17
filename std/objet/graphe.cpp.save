#include "graphe.h"
#include <queue>

Graphe::Graphe(std::string ficTopologie, std::string ficPoids){ ///CODE TP2/3 (adapté)
    ///Ouverture FICHIER TOPOLOGIE/////////////////////////////////
    std::ifstream ifs{ficTopologie};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficTopologie );

    int ordre; //nb sommets
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    double x,y;

    ///Lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    int taille; //nb aretes
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    int ID_s1, ID_s2;

    Arete* arete;
    ///Lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete ID");
        ifs>>ID_s1; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        ifs>>ID_s2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        arete = new Arete{id,ID_s1, ID_s2};
        m_sommets[ID_s1]->setArete(arete);
        m_sommets[ID_s2]->setArete(arete);
        m_aretes.push_back(arete);
    }
    ifs.close();

    ///Ouverture FICHIER POIDS///////////////////////:
    std::ifstream ifs2{ficPoids};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficPoids );

    unsigned int nbPonderations = 0;
    ifs2 >> taille;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe fichier ponderation");
    ifs2 >> nbPonderations;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre ponderations du graphe");

    float pond;
    for(int i=0; i<taille; ++i)
    {
        ifs2 >> id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete ID Fichier 2");
        for (size_t i=0;i<nbPonderations;i++)
        {
            ifs2 >> pond; if(ifs2.fail()) throw std::runtime_error("Probleme lecture ponderation arete Fichier 2");
            m_aretes[id]->setPonderations(pond);
        }
    }
    ifs2.close();
}

void Graphe::affichage(std::string _filename, int _width, int _height) const
{
    Svgfile svgout{_filename,_width,_height};
    svgout.addGrid(2);
    int x1,x2,y1,y2;
    for (auto& arete: m_aretes)
    {
        x1=m_sommets[arete->getS1()]->get_x();
        y1=m_sommets[arete->getS1()]->get_y();
        x2=m_sommets[arete->getS2()]->get_x();
        y2=m_sommets[arete->getS2()]->get_y();
        svgout.addLine(x1,y1,x2,y2,2);
        svgout.addText((abs(x1+x2)/2)+1,(abs(y1+y2)/2)-2,arete->get_label(),2);
    }
    for (auto& sommet: m_sommets)
    {
        sommet->affichage(svgout);
    }
}

Graphe* Graphe::Prim(int typeCout,int s0)
{
    std::unordered_map<int, Sommet*> marquage;
    std::vector<Arete*> listeAretes;
    Sommet* sommetActuel = m_sommets[s0];
    Arete* AreteActuel;
    float coutActuel; ///Suppose que le max de ponderation est 10000 pour pouvoir comparer ensuite
    while(listeAretes.size() != (m_sommets.size()-1))
    {
        coutActuel = 1000.0;
        marquage.insert({sommetActuel->getID(), sommetActuel}); ///On marque le sommet sur lequel on est
        for(const auto s: marquage) ///Pour chaque sommets marqué
        {
            for(const auto ar: s.second->getAretes())///On regarde ses aretes adjacentes et leur poids
            {
                if(((marquage.find(ar->getS2())==marquage.end())||(marquage.find(ar->getS1())==marquage.end()))&&(ar->getPonderations(typeCout)<coutActuel))///Prim
                {
                    coutActuel = ar->getPonderations(typeCout);
                    AreteActuel = ar;
                    if( (marquage.find(ar->getS2()) != marquage.end()) && (marquage.find(ar->getS1()) == marquage.end()) ){ ///Si c le sommet S2 qui n'est pas marqué, c'est lui l'extrmité de l'arete visitée
                        sommetActuel = m_sommets[ar->getS1()];
                    }
                    else if( (marquage.find(ar->getS2()) == marquage.end()) && (marquage.find(ar->getS1()) != marquage.end()) ){ ///Sinon c l'autre
                        sommetActuel = m_sommets[ar->getS2()];
                    }
                }
            }
        }
        listeAretes.push_back(AreteActuel); ///L'arrete trouvée peut être ajoutée
    }
    Graphe *graphePrim=new Graphe{m_sommets, listeAretes};
    return graphePrim;
}
/*
///Double Pondération
std::vector<Combinaison*> Graphe::doublePonderation()
{
    ///Création tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    int binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'arête) = nbr de combinaisons
    int verif;///Compte du nombre d'arêtes dans la combinaison

    std::vector<Arete*> aretes;///Tableau des arêtes (routes cyclables) des combinaisons
    float coutTotalFinancier = 0;
    float coutTotalEnvironnement = 0;
    bool elimine = false;///Dominée ou non dominée (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i) //MANHATTAN : 16.8 millions de combinaisons / 24 arêtes / 16 sommets // 2 600 000 combinaisons créées
    {
        ///Compteur binaire
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue à toutes les cases du tableau entre "début" et "n" la valeur "val" : fill_n(début, n, val)
        verif = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion décimal=>binaire + compte du nombre de 1 dans le nombre binaire (=nbr d'arêtes)

        if(verif == (m_sommets.size()-1))///Si nombre d'arête == nbr sommets - 1
        {
            for(size_t j=0; j<aretes.size(); ++j)
            {
                if(binaire[j] == 1)
                {
                    aretes.push_back(aretes[j]);///Ajout des arêtes
                }
            }
            ///Variables BFS
            std::queue<Sommet*> file;
            std::unordered_set<Sommet*> marquage;
            Sommet* sommetActuel;

            ///Vérifier connexité (BFS)
            std::string s0 = "0"; ///Commence au sommet 0 arbitrairement
            sommetActuel = m_sommets[0];
            marquage.insert(sommetActuel);
            file.push(sommetActuel);

            do
            {
                sommetActuel = file.front();
                file.pop();

                for(auto ar: aretes) ///Pour chaque aretes du sous graphe
                {
                    if(ar->getS1() == sommetActuel->getID()) ///Si une extremité correspond au sommet. Cas S1 On recherche ses adjacents et on traite.
                    {
                        if(marquage.find(m_sommets[ar->getS2()]) == marquage.end())///Si sommet adjacent non marqué
                        {
                            file.push(m_sommets[ar->getS2()]);
                            marquage.insert(m_sommets[ar->getS2()]);
                        }
                    }
                    if(ar->getS2() == sommetActuel->getID()) ///Cas S2, c'est donc S1 l'autre extremité adjaçente
                    {
                        if(marquage.find(m_sommets[ar->getS1()]) == marquage.end())
                        {
                            file.push(m_sommets[ar->getS1()]);
                            marquage.insert(m_sommets[ar->getS1()]);
                        }
                    }
                }
            }
            while(!file.empty());
            if(marquage.size() == m_sommets.size()) ///Si connexe
            {
                ///Création de la combinaison
                sousGraphes.push_back(new Combinaison{aretes, coutTotalFinancier, coutTotalEnvironnement, elimine});
            }
        }

        ///Réinitialisation des variables
        aretes.clear();
    }

    ///Calcul des coûts totaux
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        coutTotalFinancier = 0;
        coutTotalEnvironnement = 0;
        for(const auto ar: comb->getAretes())///Parcours des arêtes
        {
            coutTotalFinancier = coutTotalFinancier + ar->getCoutFinancier();
            coutTotalEnvironnement = coutTotalEnvironnement + ar->getCoutEnvironnement();
        }
        comb->calculFinancier(coutTotalFinancier);
        comb->calculEnvironnement(coutTotalEnvironnement);
    }

    ///Elimination des combinaisons dominées
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas éliminée
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    if((comb1->getTotFinancier() <= comb2->getTotFinancier()) && (comb1->getTotEnvironnement() <= comb2->getTotEnvironnement()))
                    {
                        comb2->setElimine(true);
                    }
                }
            }
        }
    }
//Test
for(const auto comb: sousGraphes)
{
    comb->afficher();
}system("pause");
//FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}

///Optimisation bi-objectif coût / distance
std::vector<Combinaison*> Graphe::cout_ditance()
{
    ///Création tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    int binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'arête) = nbr de combinaisons
    int compteur = 0;///Pour parcourir les arêtes
    int verif;

    std::vector<Arete*> aretes;///Tableau des arêtes (routes cyclables) des combinaisons
    float coutTotal = 0;
    float distanceTotale = 0;
    bool elimine = false;///Dominée ou non dominée (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i)
    {
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue à toutes les cases du tableau entre "début" et "n" la valeur "val" : fill_n(début, n, val)
        verif = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion décimal=>binaire

        for(size_t j=0; j<aretes.size(); ++j)
        {
            if(binaire[j] == 1)
            {
                aretes.push_back(aretes[j]);///Ajout des arêtes
            }
        }

        //AJOUT BFS !!!

        ///Création de la combinaison
        sousGraphes.push_back(new Combinaison{aretes, coutTotal, distanceTotale, elimine});

        ///Réinitialisation des variables
        compteur = 0;
        aretes.clear();
    }

    ///Calcul de la distance totale de sommet à sommet (Dijkstra)

    ///Calcul des objectifs
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        coutTotal = 0;
        for(const auto ar: comb->getAretes())///Parcours des arêtes
        {
            coutTotal = coutTotal + ar->getCoutFinancier();
        }
        comb->calculFinancier(coutTotal);
    }

    ///Elimination des combinaisons dominées
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas éliminée
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    if((comb1->getTotFinancier() <= comb2->getTotFinancier()) && (comb1->getTotEnvironnement() <= comb2->getTotEnvironnement()))
                    {
                        comb2->setElimine(true);
                    }
                }
            }
        }
    }
//Test
//for(const auto comb: sousGraphes)
//{
//    comb->afficher();
//}system("pause");
//FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}

*/

Graphe::Dijkstra(std::vector<Arete*> aretes, int s0, int typeCout)
{
    std::unordered_set<Sommet*> marquage;
    //std::vector<Sommet*> visite;
    Sommet* sommetActuel = m_sommets[s0]; ///Depart au sommet passé  en param
    int distTotale = 0;
    int distActu = 0;
    std::unordered_map<Sommet*, int> distSommet; ///Sommet + Distance au sommet initial

    marquage.insert(sommetActuel);
    for(auto ar: aretes){ ///Pour chaque aretes
        if(ar->getS1() == sommetActuel->getID()) {  ///Si on trouve un voisin
            distSommet.insert({m_sommets[ar->getS2()], distActu + ar->getPonderations(typeCout}));
        }
        if(ar->getS2() == sommetActuel->getID()) {  ///Si on trouve un voisin (cas ou c'est S2)
            distSommet.insert({m_sommets[ar->getS1()], distActu + ar->getPonderations(typeCout}));
        }
    }


}
