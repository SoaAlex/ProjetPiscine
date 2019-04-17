#include "combinaison.h"

void Combinaison::afficher(Svgfile & svgout) const
{
    if (m_elimine)
    {
        svgout.addDisk(m_coutTotalFinancier,m_coutTotalEnvironnement,5,1,"red");
    }
    else
    {
        svgout.addDisk(m_coutTotalFinancier,m_coutTotalEnvironnement,5,1,"green");
    }
}
