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

QString Reactions::getAllReactions() const
{
    QString allReactions;
    for (const auto& pair : m_reactions)
    {
        vector<QString> reactant = pair.first;
        QString reactionStr = reactant[0] + getStateString(State::aqueous) + " + " + reactant[1] + getStateString(State::aqueous) + " -> ";
        vector<Chemical> product = pair.second;
        for(int i = 0; i < product.size() - 1; i++)
        {
            reactionStr.push_back(product[i].getFormula() + getStateString(product[i].getState()) + " + ");
        }

        reactionStr.push_back(product[product.size() - 1].getFormula() + getStateString(product[product.size() - 1].getState()) + '\n');
        allReactions.push_back(reactionStr);
    }
    return allReactions;
}

void Reactions::addLevelOne()
{
    vector<Chemical> products;
    products.push_back(Chemical("FeO", State::solid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("NaCO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("NaCO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("FeCl3", State::aqueous, QColor(92, 64, 51)));
    products.push_back(Chemical("HCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);
}

void Reactions::addLevelTwo()
{
    vector<Chemical> products;
    products.push_back(Chemical("FeOH", State::solid, QColor(92, 64, 51)));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na2CO3", State::aqueous, QColor()));
    products.push_back(Chemical("NaOH", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);
}

void Reactions::addLevelThree()
{

}

void Reactions::addLevelFour()
{

}

QString Reactions::getStateString(State state) const
{
    switch(state)
    {
    case State::solid:
        return "(s)";
    case State::liquid:
        return "(l)";
    case State::gas:
        return "(g)";
    case State::aqueous:
        return "(aq)";
    }
}
