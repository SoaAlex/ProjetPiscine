#include <fstream>
#include <iostream>
#include "graphe.h"
#include "../outils.h"
#include <queue>

Graphe::Graphe(std::string ficTopologie, std::string ficPoids){ ///CODE TP2/3 (adapt�)
    ///Ouverture FICHIER TOPOLOGIE/////////////////////////////////
    std::ifstream ifs{ficTopologie};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficTopologie );

    int ordre; //nb sommets
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;

    ///Lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture donn�es sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille; //nb aretes
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string ID_s1, ID_s2;

    Arete* arete;
    ///Lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete ID");
        ifs>>ID_s1; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        ifs>>ID_s2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        arete = new Arete{id,ID_s1, ID_s2};
        m_sommets.find(ID_s1)->second->setArete(arete);
        m_sommets.find(ID_s2)->second->setArete(arete);
        m_aretes.insert({id,arete});
        m_sommets.find(ID_s1)->second->ajouterVoisin(ID_s2);
        m_sommets.find(ID_s2)->second->ajouterVoisin(ID_s1);
    }



    ///Ouverture FICHIER POIDS///////////////////////:
    std::ifstream ifs2{ficPoids};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + ficPoids );

    int nbPonderations = 0;
    ifs2 >> taille;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe fichier ponderation");
    ifs2 >> nbPonderations;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre ponderations du graphe");

    float pond1, pond2;
    for(int i=0; i<taille; ++i){
        ifs2 >> id; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete ID Fichier 2");
        ifs2 >> pond1; if(ifs2.fail()) throw std::runtime_error("Probleme lecture ponderation 1 arete Fichier 2");
        ifs2 >> pond2; if(ifs2.fail()) throw std::runtime_error("Probleme lecture ponderation 2 arete Fichier 2");
        m_aretes.find(id)->second->setCoutFinancier(pond1);
        m_aretes.find(id)->second->setCoutEnvironnement(pond2);
    }
}

Graphe::Graphe()///Surcharge sans lecture de fichier
{ }

void Graphe::testAfficher()
{
    std::cout << "SOMMETS: " << std::endl;
    for(const auto s: m_sommets){
        std::cout<< s.second->getID() << std::endl;
    }

    std::cout << "ARETES: " << std::endl;
    for(const auto s: m_aretes){
        std::cout<< s.second->getID() << "  " << s.second->getS1() << "  " << s.second->getS2() << std::endl;
    }

    std::cout << "POIDS ARETES" << std::endl;
    for(const auto s: m_aretes){
        std::cout << "SOMMET: " << s.first << " CF: " << s.second->getCoutFinancier() << " CE: " << s.second->getCoutEnvironnement() << std::endl;
    }
}

Graphe::~Graphe()
{
    //dtor
}

///Alexandre
///Prim
Graphe* Graphe::Prim(int typeCout)
{
    std::string s0 = "0"; //D�part � 0 arbitraire
    std::unordered_map<std::string, Sommet*> marquage;
    std::unordered_map<std::string, Arete*> listeAretes;
    Sommet* sommetActuel = m_sommets.find(s0)->second;
    Arete* AreteActuel;
    float coutActuel = 10000.0; ///Suppose que le max de ponderation est 10000 pour pouvoir comparer ensuite

    do{
        marquage.insert({sommetActuel->getID(), sommetActuel}); ///On marque le sommet sur lequel on est
        for(const auto s: marquage){ ///Pour chaque sommets marqu�
            for(const auto ar: m_sommets.find(s.second->getID())->second->getAretes()) {///On regarde ses aretes adjacentes et leur poids
                if( (ar->getCoutFinancier() < coutActuel) && (typeCout == 1)
                     && !( (marquage.find(ar->getS2()) != marquage.end()) && (marquage.find(ar->getS1()) != marquage.end())) ){ ///Prim avec cout financier
                    coutActuel = ar->getCoutFinancier();
                    AreteActuel = ar;
                    sommetActuel = m_sommets.find(s.second->getID())->second;
                }
                else if((ar->getCoutEnvironnement() < coutActuel) && (typeCout == 2)
                        && !(marquage.find(ar->getS2()) != marquage.end() && marquage.find(ar->getS1()) != marquage.end()) ) { ///Avec cout environnement. On verifie le type de cout + Si 1 des sommets n'est pas marqu� (Le sommet sur lequel on est est forcement marqu� mais pas l'autre).
                    coutActuel = ar->getCoutEnvironnement();
                    AreteActuel = ar;
                    sommetActuel = m_sommets.find(s.second->getID())->second;
                }
            }
        }
        listeAretes.insert({AreteActuel->getID(),AreteActuel}); ///L'arrete trouv�e peut �tre ajout�e
    }while((listeAretes.size()-1) != m_sommets.size() );

    Graphe *graphePrim; ///On cr�e un sous graphe qui correspond � l'algo de Prim
    graphePrim->setAretes(listeAretes);
    graphePrim->setSommets(marquage);

    return graphePrim;
}

///Double Pond�ration
std::unordered_set<Combinaison*> Graphe::doublePonderation()
{
    ///Cr�ation tableau de combinaisons
    std::unordered_set<Combinaison*> sousGraphes;///Tableau des combinaisons

    ///Cr�ation des combinaisons
    int binaire[m_aretes.size()] = {0};///Tableau : nombre binaire
    int nbr_comb = 2^m_aretes.size();///2^(nbr d'ar�te) = nbr de combinaisons

    std::unordered_map<std::string,Sommet*> sommets = m_sommets;///Tableau des sommets des combinaisons
    std::unordered_map<std::string,Arete*> aretes;///Tableau des ar�tes (route cyclables) des combinaisons
    float coutTotalFinancier = 0;
    float coutTotalEnvironnement = 0;
    bool elimine = false;///Domin�e ou non domin�e (diagramme de Pareto)

    for(int i = 0; i < nbr_comb; ++i)
    {
        ///1�re �tape
            ///Compteur binaire
        convertisseur_binaire(binaire, nbr_comb, m_aretes.size());
        int compteur = 0;
        for(const auto ar: m_aretes)
        {
            if(binaire[compteur] == 1)
            {
                aretes.insert(ar);
            }
            compteur = compteur + 1;
        }
        ///Cr�ation de la combinaison
        sousGraphes.insert(new Combinaison{aretes, coutTotalFinancier, coutTotalEnvironnement, elimine});
        ///Variables BFS
        std::queue<Sommet*> file;
        std::unordered_set<Sommet*> marquage;
        Sommet* sommetActuel;

        ///2�me �tape
        for(const auto comb: sousGraphes)
        {
            ///Compter nombre d'ar�tes (doit �tre �gal � n-1, n : sommets)
            if(comb->getAretes().size() != (m_sommets.size() - 1))
            {
                sousGraphes.erase(comb);
            }
            ///V�rifier connexit� (BFS)
            else
            {
                std::string s0 = "0"; //Commence au sommet 0 arbitrairement
                sommetActuel = m_sommets.find(s0)->second;
                marquage.insert(sommetActuel);
                file.push(sommetActuel);

                do{
                    sommetActuel = file.front();
                    file.pop();
                    for(auto suc: sommetActuel->getVoisins() ){
                        if(marquage.find(m_sommets.find(suc)->second) == marquage.end()){
                            file.push(m_sommets.find(suc)->second);
                            marquage.insert(m_sommets.find(suc)->second);
                        }
                    }
                }while(!file.empty());
                if(marquage.size() != m_sommets.size()){///Si non connexe
                    sousGraphes.erase(comb);
                }
            }
        }

        ///3�me �tape
            ///Calcul des co�ts totaux
        for(const auto comb: sousGraphes)
        {
            for(const auto ar: comb->getAretes())
            {
                comb->calculFinancier(ar.second->getCoutFinancier());
                comb->calculEnvironnement(ar.second->getCoutEnvironnement());
            }
        }
            ///Elimination des combinaisons domin�es
        for(const auto comb1: sousGraphes)
        {
            if(comb1->getElimine() == false)
            {
                for(const auto comb2: sousGraphes)
                {
                    if(comb1 != comb2)
                    {
                        if((comb1->getTotFinancier() <= comb2->getTotFinancier()) && (comb1->getTotEnvironnement() <= comb2->getTotEnvironnement()))
                        {
                            comb2->setElimine(true);
                        }
                    }
                }
            }
        }
    }

    return(sousGraphes);
}
