#ifndef COMBINAISON_H_INCLUDED
#define COMBINAISON_H_INCLUDED

class Combinaison
{
public:
    Combinaison(std::unordered_map<std::string, Arete*> aretes, float cout1, float cout2, bool elimine)
        :m_aretes{aretes}, m_coutTotalFinancier{cout1}, m_coutTotalEnvironnement{cout2}, m_elimine{elimine} { }
    ~Combinaison() { }

    void calculFinancier(int cout1) {m_coutTotalFinancier = m_coutTotalFinancier + cout1;}
    void calculEnvironnement(int cout1) {m_coutTotalFinancier = m_coutTotalEnvironnement + cout1;}
    void setElimine(bool val) {m_elimine = val;}

    std::unordered_map<std::string, Arete*> getAretes() const {return(m_aretes);}
    float getTotFinancier() const {return(m_coutTotalFinancier);}
    float getTotEnvironnement() const {return(m_coutTotalEnvironnement);}
    bool getElimine() const {return(m_elimine);}

private:
    std::unordered_map<std::string, Arete*> m_aretes;
    float m_coutTotalFinancier;
    float m_coutTotalEnvironnement;
    bool m_elimine;
};


#endif // COMBINAISON_H_INCLUDED
