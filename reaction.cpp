#include "reaction.h"
#include "chemical.h"


Reaction::Reaction(vector<Chemical> products)
{
    for(int i = 0; i < (int)products.size(); i++)
    {
        switch(products.at(i).getState())
        {
        case State::gas:
            m_hasGas = true;
            break;
        case State::solid:
            m_hasSolid = true;
            m_colorOfSolid = products.at(i).getColorOfSolid();
            break;
        default:
            break;
        }
    }
}

bool Reaction::hasGas()
{
    return m_hasGas;
}

bool Reaction::hasSolid()
{
    return m_hasSolid;
}

QColor Reaction::colorOfSolid()
{
    return m_colorOfSolid;
}
