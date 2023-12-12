#ifndef REACTIONS_H
#define REACTIONS_H

#include "chemical.h"
#include "reaction.h"

using std::map;
using std::vector;

class Reactions
{
public:
    /// @brief Standard Constructor
    Reactions();

    /// @brief Creates a mapping of their reactants to the reactants and products
    /// @param reactantA The first chemical
    /// @param reactantB The second chemical
    /// @return the chemicals and their products
    Reaction getReaction(Chemical reactantA, Chemical reactantB);

    /// @brief Add all of the reactions to a string
    /// @return the reactions as a string
    QString getAllReactions() const;

    /// @brief Add all necessary elements and products for level 1
    void addLevelOne();

    /// @brief Add all necessary elements and products for level 2
    void addLevelTwo();

    /// @brief Add all necessary elements and products for level 3
    void addLevelThree();

    /// @brief Add all necessary elements and products for level 4
    void addLevelFour();

private:
    map<vector<QString>, vector<Chemical>> m_reactantsAndProducts;
    vector<QString> m_equations;

    /// @brief Adds a mapping of the chemicals and their products
    /// @param reactantA The first chemical
    /// @param reactantB The second chemical
    /// @param products The products of the reaction
    void addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products);
};

#endif // REACTIONS_H
