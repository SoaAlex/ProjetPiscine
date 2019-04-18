#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "../svg/svgfile.h"
#define CoutFinancier 0
#define CoutEnvironnement 1

class Arete
{
    public:
        ///destructeur
        ~Arete(){}
        ///constructeur sans les pondérations
        Arete(int id, int s1, int s2)
            :m_id{id}, m_idSommet1{s1}, m_idSommet2{s2}{}
        ///ajoute une pondération
        void setPonderations(float ponderation)
        {m_ponderations.push_back(ponderation);}
        ///retourne l'id
        int getID() const{return m_id;}
        ///retourne les extrémités
        int getS1() const{return m_idSommet1;}
        int getS2() const{return m_idSommet2;}
        ///retourne une pondération
        float getPonderations(int clef) const{return m_ponderations[clef];}
        ///retournr l'ensemble des pondérations pour l'affichage
        std::string get_label()const;
    private:
        int m_id;/// Identifiant
        int m_idSommet1, m_idSommet2;/// Extrémités
        std::vector<float> m_ponderations;/// Ensemble des pondérations
};

#endif // ARETE_H_INCLUDED
