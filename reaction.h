#ifndef REACTION_H
#define REACTION_H

#include "chemical.h"
#include <QColor>

using std::vector;

class Reaction
{
public:
    /// @brief Disable button
    Reaction(vector<Chemical> products);

    /// @brief The gas state of the reaction
    /// @return true if it has a gas, false otherwise
    bool hasGas();

    /// @brief The solid state of the reaction
    /// @return true if it has a solid, false otherwise
    bool hasSolid();

    /// @brief The color of the solid
    /// @return the color of the solid,
    QColor colorOfSolid();

private:
    bool m_hasGas;
    bool m_hasSolid;
    QColor m_colorOfSolid;
};

#endif // REACTION_H
