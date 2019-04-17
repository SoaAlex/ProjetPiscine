#include "combinaison.h"

void Combinaison::afficher()
{
    for(size_t i=0; i<m_totauxPonderations.size(); ++i)
    {
        std::cout<<m_totauxPonderations[i]<<"  ";
    }
    std::cout<<m_elimine<<std::endl;
}

void Combinaison::afficher(Svgfile & svgout) const
{
    if (m_elimine)
    {
        svgout.addDisk(m_totauxPonderations[0],m_totauxPonderations[1],5,3,"red");
    }
    else
    {
        svgout.addDisk(m_totauxPonderations[0],m_totauxPonderations[1],5,3,"green");
    }
}
