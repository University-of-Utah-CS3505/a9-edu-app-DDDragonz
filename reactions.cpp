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
    QString allReactions = "";

    for(int i = 0; i < m_equations.size(); i++)
    {
        allReactions += m_equations.at(i);
        allReactions+= "<br/><br/>";
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
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("FeCl3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor(92, 64, 51)));
    products.push_back(Chemical("CO2", State::gas, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("FeCl3", State::aqueous, QColor(92, 64, 51)));
    products.push_back(Chemical("HCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("FeCl3", State::aqueous, QColor()), products);

    m_equations.push_back("HCl(aq) + FeCl<sub>3</sub>(aq) -> HCl(aq) + FeCl<sub>3</sub>(aq)");
    m_equations.push_back("FeCl<sub>3</sub>(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> FeO(s) + CO<sub>2</sub>(g) + NaCl(aq)<br/>Note: FeO is a dark brown solid.");
    m_equations.push_back("HCl(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> H<sub>2</sub>O(l) + CO<sub>2</sub>(g) + NaCl(aq)");
}

void Reactions::addLevelTwo()
{
    vector<Chemical> products;
    products.push_back(Chemical("FeOH", State::solid, QColor(92, 64, 51)));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("FeCl3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H2O", State::liquid, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na2CO3", State::aqueous, QColor()));
    products.push_back(Chemical("NaOH", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);

    m_equations.push_back("NaOH(aq) + FeCl<sub>3</sub>(aq) -> FeOH(s) + NaCl(aq)<br/>Note: FeOH is a dark brown solid.");
    m_equations.push_back("NaOH(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> NaOH(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq)");
    m_equations.push_back("NaOH(aq) + HCl(aq) -> H<sub>2</sub>O(l) + NaCl(aq)");
}

void Reactions::addLevelThree()
{
    vector<Chemical> products;
    products.push_back(Chemical("AgCl", State::solid, Qt::white));
    products.push_back(Chemical("FeNO3", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("FeCl3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Ag2CO3", State::solid, Qt::white));
    products.push_back(Chemical("NaNO3", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("AgCl", State::solid, Qt::white));
    products.push_back(Chemical("HNO3", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("AgOH", State::solid, Qt::gray));
    products.push_back(Chemical("NaNO3", State::aqueous, QColor()));
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);

    m_equations.push_back("AgNO<sub>3</sub>(aq) + FeCl<sub>3</sub>(aq) -> AgCl(s) + FeNO<sub>3</sub>(aq)<br/>Note: AgCl is a white solid.");
    m_equations.push_back("AgNO<sub>3</sub>(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> Ag<sub>2</sub>CO<sub>3</sub>(s) + NaNO<sub>3</sub>(aq)<br/>Note: Ag<sub>2</sub>CO<sub>3</sub> is a white solid.");
    m_equations.push_back("AgNO<sub>3</sub>(aq) + HCl(aq) -> AgCl(s) + HNO<sub>3</sub>(aq)<br/>Note: AgCl is a white solid.");
    m_equations.push_back("AgNO<sub>3</sub>(aq) + NaOH(aq) -> AgOH(s) + NaNO<sub>3</sub>(aq)<br/>Note: AgOH is a grey solid.");
}

void Reactions::addLevelFour()
{
    vector<Chemical> products;
    products.push_back(Chemical("FePO4", State::solid, QColor(255, 255, 191)));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("FeCl3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
    addReaction(Chemical("Na3PO4", State::aqueous, QColor()), Chemical("FeCl3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("Na2CO3", State::aqueous, QColor()));
    addReaction(Chemical("Na2CO3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
    addReaction(Chemical("Na3PO4", State::aqueous, QColor()), Chemical("Na2CO3", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("H3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("NaCl", State::aqueous, QColor()));
    addReaction(Chemical("HCl", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
    addReaction(Chemical("Na3PO4", State::aqueous, QColor()), Chemical("HCl", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Na3PO4", State::aqueous, QColor()));
    products.push_back(Chemical("NaOH", State::aqueous, QColor()));
    addReaction(Chemical("NaOH", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
    addReaction(Chemical("Na3PO4", State::aqueous, QColor()), Chemical("NaOH", State::aqueous, QColor()), products);

    products.clear();
    products.push_back(Chemical("Ag3PO4", State::solid, Qt::yellow));
    products.push_back(Chemical("NaNO3", State::aqueous, QColor()));
    addReaction(Chemical("AgNO3", State::aqueous, QColor()), Chemical("Na3PO4", State::aqueous, QColor()), products);
    addReaction(Chemical("Na3PO4", State::aqueous, QColor()), Chemical("AgNO3", State::aqueous, QColor()), products);

    m_equations.push_back("Na<sub>3</sub>PO<sub>4</sub>(aq) + FeCl<sub>3</sub>(aq) -> FePO<sub>4</sub>(s) + NaCl(aq)<br/>Note: FePO<sub>4</sub> is a light yellow solid.");
    m_equations.push_back("Na<sub>3</sub>PO<sub>4</sub>(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> Na<sub>3</sub>PO<sub>4</sub>(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq)");
    m_equations.push_back("Na<sub>3</sub>PO<sub>4</sub>(aq) + HCl(aq) -> H<sub>3</sub>PO<sub>4</sub>(aq) + NaCl(aq)");
    m_equations.push_back("Na<sub>3</sub>PO<sub>4</sub>(aq) + NaOH(aq) -> Na<sub>3</sub>PO<sub>4</sub>(aq) + NaOH(aq)");
    m_equations.push_back("Na<sub>3</sub>PO<sub>4</sub>(aq) + AgNO<sub>3</sub>(aq) -> Ag<sub>3</sub>PO<sub>4</sub>(s) + NaNO<sub>3</sub>(aq)<br/>Note: Ag<sub>3</sub>PO<sub>4</sub> is a light yellow solid.");
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
