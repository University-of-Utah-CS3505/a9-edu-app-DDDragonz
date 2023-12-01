#include "reactions.h"
#include "chemical.h"

using std::vector;

Reactions::Reactions()
{ }

Reaction Reactions::getReaction(Chemical reactantA, Chemical reactantB)
{
    vector<QString> reactants;
    reactants.push_back(reactantA.getFormula());
    reactants.push_back(reactantB.getFormula());
    return m_reactions[reactants];
}

void Reactions::addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products)
{
    vector<QString> reactants;
    reactants.push_back(reactantA.getFormula());
    reactants.push_back(reactantB.getFormula());
    m_reactions[reactants] = products;
}
