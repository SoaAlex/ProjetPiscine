#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y)
    :m_id{id}, m_x{x}, m_y{y}
{ }

void Sommet::setArete(Arete* arete)
{
    m_aretes.push_back(arete);
}

Sommet::~Sommet()
{
    //dtor
}

void Sommet::ajouterVoisin(std::string voisin)
{
    m_voisins.push_back(voisin);
}
