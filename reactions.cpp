#include "reactions.h"
#include "reaction.h"
#include "chemical.h"

using std::vector;

Reactions::Reactions()
{ }

Reaction Reactions::getReaction(Chemical reactantA, Chemical reactantB)
{
    vector<QString> reactants;
    reactants.push_back(reactantA.getFormula());
    reactants.push_back(reactantB.getFormula());
    return Reaction(m_reactantsAndProducts[reactants]);
}

void Reactions::addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products)
{
    vector<QString> reactants;
    reactants.push_back(reactantA.getFormula());
    reactants.push_back(reactantB.getFormula());
    m_reactantsAndProducts[reactants] = products;
}

QString Reactions::getAllReactions() const
{
    QString allReactions;
    for (const auto& pair : m_reactantsAndProducts)
    {
        vector<QString> reactant = pair.first;
        QString reactionStr = reactant[0] + getStateString(State::aqueous) + " + " + reactant[1] + getStateString(State::aqueous) + " -> ";
        vector<Chemical> product = pair.second;
        for(unsigned int i = 0; i < product.size() - 1; i++)
        {
            reactionStr.push_back(product[i].getFormula() + getStateString(product[i].getState()) + " + ");
        }
        reactionStr.push_back(product[product.size() - 1].getFormula() + getStateString(product[product.size() - 1].getState()) + '\n' + '\n');
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
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);

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
    vector<Chemical> products;
    products.push_back(Chemical("AgCl", State::solid, Qt::white));
    products.push_back(Chemical("FeNO3", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Ag2CO3", State::solid, Qt::white));
    products.push_back(Chemical("NaNO3", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("AgCl", State::solid, Qt::white));
    products.push_back(Chemical("HNO3", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("AgOH", State::solid, Qt::gray));
    products.push_back(Chemical("NaOH", State::aqueous, QColor()));
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);
}

void Reactions::addLevelFour()
{
    vector<Chemical> products;
    products.push_back(Chemical("FePO4", State::solid, QColor(255, 255, 191)));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("Na2CO3", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("NaOH", State::aqueous, QColor()));
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Ag3PO4", State::solid, Qt::yellow));
    products.push_back(Chemical("NaNO3", State::aqueous, QColor()));
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
}

QString Reactions::getStateString(State state) const
{
    QString solid;
    switch(state)
    {
    case State::solid:
        solid = "(s, ";
        solid += getColorString(QColor());
        solid += ")";
        return solid;
    case State::liquid:
        return "(l)";
    case State::gas:
        return "(g)";
    case State::aqueous:
        return "(aq)";
    }
}

QString Reactions::getColorString(QColor color) const
{
    return "color";
}
