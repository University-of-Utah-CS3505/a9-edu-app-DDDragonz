#ifndef REACTION_H
#define REACTION_H

#include "chemical.h"
#include <QColor>

using std::vector;

class Reaction
{
public:
    Reaction(vector<Chemical> products);
    Reaction(const Reaction& other);
    Reaction& operator=(const Reaction& other);
    bool hasGas();
    bool hasSolid();
    QColor colorOfSolid();
    QString toString() const;

private:
    bool m_hasGas;
    bool m_hasSolid;
    QColor m_colorOfSolid;
};

#endif // REACTION_H
