#include <fstream>
#include <iostream>
#include "graphe.h"

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

Graphe::~Graphe()
{
    //dtor
}
