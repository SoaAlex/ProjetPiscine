#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED
#include "arete.h"

class Combinaison
{
public:
    Combinaison(std::vector<Arete*> aretes, float cout1, float cout2, bool elimine)
        :m_aretes{aretes}, m_coutTotalFinancier{cout1}, m_coutTotalEnvironnement{cout2}, m_elimine{elimine} { }
    ~Combinaison() { }

    void afficher() {std::cout<<m_coutTotalFinancier<<"  "<<m_coutTotalEnvironnement<<"  "<<m_elimine<<std::endl;}
    void calculFinancier(int coutTot) {m_coutTotalFinancier = coutTot;}
    void calculEnvironnement(int coutTot) {m_coutTotalEnvironnement = coutTot;}
    void setElimine(bool val) {m_elimine = val;}

    std::vector<Arete*> getAretes() const {return(m_aretes);}
    float getTotFinancier() const {return(m_coutTotalFinancier);}
    float getTotEnvironnement() const {return(m_coutTotalEnvironnement);}
    bool getElimine() const {return(m_elimine);}
    void afficher(Svgfile & svgout) const;

private:
    std::vector<Arete*> m_aretes;
    float m_coutTotalFinancier;
    float m_coutTotalEnvironnement;
    bool m_elimine;
};


#endif // COMBINAISON_H_INCLUDED
