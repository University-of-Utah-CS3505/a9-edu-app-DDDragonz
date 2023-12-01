#ifndef REACTION_H
#define REACTION_H

#include "chemical.h"
#include <QColor>

using std::vector;

class Reaction
{
public:
    Reaction(vector<Chemical> chemicals);
    bool hasGas();
    bool hasSolid();
    QColor colorOfSolid();

private:
    bool m_hasGas;
    bool m_hasSolid;
    QColor m_colorOfSolid;
};

#endif // REACTION_H
