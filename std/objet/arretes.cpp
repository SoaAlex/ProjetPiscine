#include "arretes.h"

Arete::Arete(std::string id, std::string s1, std::string s2, float coutFinancier, float coutEnvironnement)
    :m_id{id}, m_idSommet1{s1}, m_idSommet2{s2}, m_coutFinancier{coutFinancier}, m_coutEnvironnement{coutEnvironnement}
{ }

void Arete::setCoutFinancier(float coutFinancier)
{
    m_coutFinancier = coutFinancier;
}

void Arete::setCoutEnvironnement(float coutEnvironnement)
{
    m_coutEnvironnement = coutEnvironnement;
}

Arete::~Arete()
{
    //dtor
}
