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
    for(size_t i=0; i<taille; ++i)
    {
        ifs2 >> id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete ID Fichier 2");
        for (size_t j=0;j<nbPonderations;j++)
        {
            ifs2 >> pond; if(ifs2.fail()) throw std::runtime_error("Probleme lecture ponderation arete Fichier 2");
            m_aretes[id]->setPonderations(pond);
            if (i==0)
            {
                m_coutTotal.push_back(pond);
            }
            else
            {
                m_coutTotal[j]+=pond;
            }
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
    std::string sortie;
    sortie.append("(");
    std::string ponderation;
    int taille=4;
    for (auto& coutTotal: m_coutTotal)
    {
        ponderation=std::to_string(coutTotal);
        if (coutTotal>=100)
        {
            taille=5;
        }
        ponderation.erase(ponderation.begin()+taille,ponderation.end());
        sortie.append(ponderation);
        sortie.append(" ; ");
    }
    sortie.erase(sortie.end()-3,sortie.end());
    sortie.append(")");
    svgout.addText(_width/2-(16*taille),_height-70,sortie,1,32);
}

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

Graphe* Graphe::Prim(int typeCout,int s0)
{
    std::unordered_map<int, Sommet*> marquage;
    std::vector<Arete*> listeAretes;
    Sommet* sommetActuel = m_sommets[s0];
    Arete* AreteActuel;
    std::vector<float> coutTotal;
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
    for (size_t i=0;i<listeAretes.size();i++)
    {
        for (size_t j=0; j<m_coutTotal.size();j++)
        {
            if (i==0)
            {
                coutTotal.push_back(listeAretes[i]->getPonderations(j));
            }
            else
            {
                coutTotal[j]+=listeAretes[i]->getPonderations(j);
            }
        }
    }
    Graphe *graphePrim=new Graphe{m_sommets, listeAretes,coutTotal};
    return graphePrim;
}

///Double Pondération
std::vector<Combinaison*> Graphe::doublePonderation(int ponderation)
{
    ///Création tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    int binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'arête) = nbr de combinaisons
    int verif;///Compte du nombre d'arêtes dans la combinaison
    int supprimer;

    std::vector<Arete*> aretes;///Tableau des arêtes (routes cyclables) des combinaisons
    std::vector<float> coutTotaux;///Pour calculer les totaux des pondérations
    for(size_t i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
    }
    bool elimine = false;///Dominée ou non dominée (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i) //MANHATTAN : 16.8 millions de combinaisons / 24 arêtes / 16 sommets // 2 600 000 combinaisons créées
    {
        ///Compteur binaire
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue à toutes les cases du tableau entre "début" et "n" la valeur "val" : fill_n(début, n, val)
        verif = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion décimal=>binaire + compte du nombre de 1 dans le nombre binaire (=nbr d'arêtes)

        if(verif == (m_sommets.size()-1))///Si nombre d'arête == nbr sommets - 1
        {
            for(size_t j=0; j<m_aretes.size(); ++j)
            {
                if(binaire[j] == 1)
                {
                    aretes.push_back(m_aretes[j]);///Ajout des arêtes

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
                sousGraphes.push_back(new Combinaison{aretes, coutTotaux, elimine});
            }
        }

        ///Réinitialisation des variables
        aretes.clear();
    }

    ///Calcul des pondération totales
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        std::fill_n(coutTotaux.begin(), ponderation, 0);///Mise à 0

        for(const auto ar: comb->getAretes())///Parcours des arêtes
        {
            for(size_t i=0; i<ponderation; ++i)
            {
                coutTotaux[i] = coutTotaux[i] + ar->getPonderations(i);
            }
        }
        comb->calculTotPond(coutTotaux);
    }

    ///Elimination des combinaisons dominées
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas éliminée
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                supprimer = 1;
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    for(size_t i=0; i<ponderation; ++i)
                    {
                        verif = ComparaisonAretes(comb1, comb2, i);
                        if(verif == 2)
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
    Svgfile svgout{"outputPareto.svg",500,500};
    svgout.addRepere();
    //Test
    for(const auto comb: sousGraphes)
    {
        comb->afficher();
        comb->afficher(svgout);
    }
    system("pause");
    //FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}

///Optimisation bi-objectif coût / distance
std::vector<Combinaison*> Graphe::cout_ditance(int ponderation)
{
    ///Création tableau de combinaisons
    std::vector<Combinaison*> sousGraphes;///Tableau des combinaisons

    int binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = puissance(m_aretes.size());///2^(nbr d'arête) = nbr de combinaisons
    int verif;///Compte du nombre d'arêtes dans la combinaison
    int supprimer;

    std::vector<Arete*> aretes;///Tableau des arêtes (routes cyclables) des combinaisons
    std::vector<float> coutTotaux;///Pour calculer les totaux des pondérations
    for(size_t i=0; i<ponderation; ++i)
    {
        coutTotaux.push_back({0});
    }
    bool elimine = false;///Dominée ou non dominée (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i)
    {
        ///Compteur binaire
        std::fill_n(binaire, m_aretes.size(), 0);///Attribue à toutes les cases du tableau entre "début" et "n" la valeur "val" : fill_n(début, n, val)
        verif = convertisseur_binaire(binaire, i, m_aretes.size());///Conversion décimal=>binaire + compte du nombre de 1 dans le nombre binaire (=nbr d'arêtes)

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
            sousGraphes.push_back(new Combinaison{aretes, coutTotaux, elimine});
        }
        ///Réinitialisation des variables
        aretes.clear();
    }

    ///Calcul des pondérations totales
    for(const auto comb: sousGraphes)///Parcours des combinaisons
    {
        std::fill_n(coutTotaux.begin(), ponderation, 0);///Mise à 0

        for(const auto ar: comb->getAretes())///Parcours des arêtes
        {
            for(size_t i=0; i<ponderation; ++i)
            {
                coutTotaux[i] = coutTotaux[i] + ar->getPonderations(i);
            }
        }
        comb->calculTotPond(coutTotaux);
    }

    ///Elimination des combinaisons dominées
    for(const auto comb1: sousGraphes)///Parcours des combinaisons
    {
        if(comb1->getElimine() == false)///Si la combinaison n'est pas éliminée
        {
            for(const auto comb2: sousGraphes)///On compare avec les autres combinaisons
            {
                supprimer = 1;
                if((comb1 != comb2) && (comb2->getElimine()!=true))
                {
                    for(size_t i=0; i<ponderation; ++i)
                    {
                        verif = ComparaisonAretes(comb1, comb2, i);
                        if(verif == 2)
                        {
                            comb2->setElimine(true);
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
//Test
/*for(const auto comb: sousGraphes)
{
    comb->afficher();
}system("pause");*/
//FIN
    return(sousGraphes);///On retourne les solutions (combinaisons) admissibles
}

///Alexandre
int Graphe::Dijkstra(/*std::vector<Arete*> aretes, */int s0, int typeCout)
{
    std::unordered_set<Sommet*> marquage;
    Sommet* sommetActuel = m_sommets[s0]; ///Depart au sommet passé  en param
    float distTotale = 0;
    float distActu = 0;
    std::unordered_map<Sommet*, int> distSommet; ///Sommet + Distance au sommet initial

    marquage.insert(sommetActuel);
    do
    {
        ///Determination des distances depuis le sommet Actuel
        for(const auto ar: /*aretes*/ m_aretes)  ///Pour chaque aretes
        {
            if(ar->getS1() == sommetActuel->getID())    ///Si on trouve un voisin
            {
                if(marquage.find(m_sommets[ar->getS2()]) == marquage.end())///non marqué
                {
                    if(distSommet.find(m_sommets[ar->getS2()]) == distSommet.end())  ///Si c'est la 1ère fois qu'on le voit
                    {
                        distSommet.insert({m_sommets[ar->getS2()], distActu + ar->getPonderations(typeCout)}); ///On ajoute à la map. Sommet voisin + Valeur de sa distance (val = dist sommet actu/prec + poids arete)
                    }
                    else if(distActu + ar->getPonderations(typeCout) <= distSommet.find(m_sommets[ar->getS2()])->second)  ///Si on la déjà vu, alors on verifie que la nouvelle distance est inférieure à l'ancienne
                    {
                        distSommet.find(m_sommets[ar->getS2()])->second = distActu + ar->getPonderations(typeCout);
                    }
                }
            }
            if(ar->getS2() == sommetActuel->getID())    ///Si on trouve un voisin (cas où c'est S2)
            {
                if(marquage.find(m_sommets[ar->getS1()]) == marquage.end())
                {
                    if(distSommet.find(m_sommets[ar->getS1()]) == distSommet.end())  ///Si c'est la 1ère fois qu'on le voit
                    {
                        distSommet.find(m_sommets[ar->getS1()])->second = distActu + ar->getPonderations(typeCout);

                    }
                    else if(distActu + ar->getPonderations(typeCout) <= distSommet.find(m_sommets[ar->getS1()])->second)
                    {std::cout<<"d";
                        distSommet.find(m_sommets[ar->getS1()])->second = distActu + ar->getPonderations(typeCout);
                    }
                }
            }
        }

        ///Determination du sommet le plus proche
        distActu = 100000; ///Arbitrairement, rien ne sera + loin que 100000
        for(const auto dist: distSommet)
        {

            if((dist.second <= distActu) && (marquage.find(m_sommets[dist.first->getID()]) == marquage.end()) )   ///On cherche la + petite distance parmi les sommets
            {
                distActu = dist.second; ///DistActu correspond a la distance au sommet le + proche. Au prochain tour il servira pour les calculs
                sommetActuel = dist.first; ///On retient quel sommet est le + proche
            }
        }
        marquage.insert(sommetActuel); ///Au prochain tour, on partira donc du sommet le + proche
    }
    while(marquage.size() != m_sommets.size());

    ///Calcul coutTotal
    for(const auto dist: distSommet)
    {
        distTotale += dist.second;
    }

    return distTotale;
}
