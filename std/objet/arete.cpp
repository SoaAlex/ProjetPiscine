#include "arete.h"

std::string Arete::get_label() const
{
    std::string sortie;///chaine de sortie
    sortie.append("(");
    std::string ponderation;
    int i=0;
    for (auto it : m_ponderations)///ajout des pondérations en le tronquant
    {
        ponderation=std::to_string(it);
        ponderation.erase(ponderation.begin()+3,ponderation.end());
        sortie.append(ponderation);
        sortie.append(";");
    }
    sortie.erase(sortie.end()-1,sortie.end());
    sortie.append(")");
    return sortie;
}
