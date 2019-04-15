#ifndef ARRETES_H_INCLUDED
#define ARRETES_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "ressource/svg/svgfile.h"

class Arete{

    public:
        Arete(std::string id, std::string idSommet1, std::string idSommet2,
              float coutFinancier=0.0, float coutEnvironnement=0.0);
        ~Arete();
        void setCoutFinancier(float coutFinancier);
        void setCoutEnvironnement(float coutEnvironnement);

    private:
        std::string m_id;
        std::string m_idSommet1, m_idSommet2;
        int m_coutFinancier, m_coutEnvironnement;
        bool cyclable;
}

#endif // ARRETES_H_INCLUDED
