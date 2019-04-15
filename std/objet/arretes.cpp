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

std::string Arete::getID() const
{
    return m_id;
}

std::string Arete::getS1() const
{
    return m_idSommet1;
}

std::string Arete::getS2() const
{
    return m_idSommet2;
}

float Arete::getCoutFinancier() const
{
    return m_coutFinancier;
}

float Arete::getCoutEnvironnement() const
{
    return m_coutEnvironnement;
}

Arete::~Arete()
{
    //dtor
}
