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
        QString reactionStr = reactant[0] + " + " + reactant[1] + " -> ";
        vector<Chemical> product = pair.second;
        for(int i = 0; i < product.size() - 1; i++)
        {
            reactionStr.push_back(product[i].getFormula() + " + ");
        }

        reactionStr.push_back(product[product.size() - 1].getFormula() + '\n');
        allReactions.push_back(reactionStr);
    }
    return allReactions;
}

void Reactions::addLevelOne()
{
    vector<Chemical> products;
    products.push_back(Chemical("FeO", State::solid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::liquid, QColor()));
    addReaction(Chemical("FeCl3", State::liquid, QColor()), Chemical("NaCO3", State::liquid, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::liquid, QColor()));
    addReaction(Chemical("HCl", State::liquid, QColor()), Chemical("NaCO3", State::liquid, QColor()), products);

    products.clear();
    products.push_back(Chemical("FeCl3", State::liquid, QColor(92, 64, 51)));
    products.push_back(Chemical("HCl", State::liquid, QColor()));
    addReaction(Chemical("FeCl3", State::liquid, QColor()), Chemical("HCl", State::liquid, QColor()), products);
}

void Reactions::addLevels()
{
    addLevelOne();
    addLevelTwo();
    addLevelThree();
    addLevelFour();
}

void Reactions::addLevelTwo()
{

}

void Reactions::addLevelThree()
{

}

void Reactions::addLevelFour()
{

}
