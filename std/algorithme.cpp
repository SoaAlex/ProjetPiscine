#include <queue>
#include "objet/graphe.h"
#include "math.h" //Fonction de calcul de maths

///PRIM
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

///BFS
size_t Graphe::connexiteBFS(std::vector<Arete*> aretes)
{
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

    return(marquage.size());
}

///DIJKSTRA
int Graphe::Dijkstra(std::vector<Arete*> aretes, int s0, int typePonderation, std::unordered_map<Sommet*,int> heurist)
{
    std::unordered_set<Sommet*> marquage;
    Sommet* sommetActuel = m_sommets[s0]; ///Depart au sommet passé  en param
    float distTotale = 0;
    float distActu = 0;
    std::unordered_map<Sommet*, int> distSommet; ///Sommet + Distance au sommet initial
    if(heurist.size() == 0){ ///Si on ne donne pas de vecteur d'heuristique (donc vide)
        for(auto s: m_sommets){
            heurist.insert({s,0}); ///On insère une heuristique nulle pour chaque sommets
        }
    }


    marquage.insert(sommetActuel);
    do
    {
        ///Determination des distances depuis le sommet Actuel
        for(const auto ar: aretes)  ///Pour chaque aretes
        {
            if(ar->getS1() == sommetActuel->getID())    ///Si on trouve un voisin
            {
                if(marquage.find(m_sommets[ar->getS2()]) == marquage.end())///non marqué
                {
                    if(distSommet.find(m_sommets[ar->getS2()]) == distSommet.end())  ///Si c'est la 1ère fois qu'on le voit
                    {
                        distSommet.insert({m_sommets[ar->getS2()], distActu + ar->getPonderations(typePonderation)}); ///On ajoute à la map. Sommet voisin + Valeur de sa distance (val = dist sommet actu/prec + poids arete)
                    }
                    else if(distActu + ar->getPonderations(typePonderation) + heurist.find(m_sommets[ar->getS2()])->second <= distSommet.find(m_sommets[ar->getS2()])->second + heurist.find(m_sommets[ar->getS2()])->second)  ///Si on la déjà vu, alors on verifie que la nouvelle distance est inférieure à l'ancienne
                    {
                        distSommet.find(m_sommets[ar->getS2()])->second = distActu + ar->getPonderations(typePonderation);
                    }
                }
            }
            if(ar->getS2() == sommetActuel->getID())    ///Si on trouve un voisin (cas où c'est S2)
            {
                if(marquage.find(m_sommets[ar->getS1()]) == marquage.end())
                {
                    if(distSommet.find(m_sommets[ar->getS1()]) == distSommet.end())  ///Si c'est la 1ère fois qu'on le voit
                    {
                        distSommet.insert({m_sommets[ar->getS1()], distActu + ar->getPonderations(typePonderation)});

                    }
                    else if(distActu + ar->getPonderations(typePonderation) + heurist.find(m_sommets[ar->getS1()])->second <= distSommet.find(m_sommets[ar->getS1()])->second + heurist.find(m_sommets[ar->getS1()])->second)
                    {
                        distSommet.find(m_sommets[ar->getS1()])->second = distActu + ar->getPonderations(typePonderation);
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

///AStar
int Graphe::AStar(std::vector<Arete*> aretes, int s0, int sFin, int typePonderation)
{
    std::unordered_map<Sommet*, int> valHeurist; ///Sommet + Valeur de l'heuristique correspondante à ce sommet vers le sommet final
    int H = 0;

    for(auto s: m_sommets){
        H = sqrt( pow(s->get_x() - m_sommets[sFin]->get_x(),2) + pow(s->get_y() - m_sommets[sFin]->get_y(),2) );///Calcul distance euclidienne
        valHeurist.insert({s, H});
    }

    H = Dijkstra(aretes, s0, typePonderation, valHeurist);
    return H; ///Dijkstra de s0 à sFin
}
