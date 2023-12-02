#include "chemistrylogicmodel.h"
#include "reaction.h"
using std::vector;

ChemistryLogicModel::ChemistryLogicModel(QObject *parent)
    : QObject{parent},
    m_level(0),
    m_mysteries(vector<QString>())
{
}

int ChemistryLogicModel::getLevel()
{
    return m_level;
}

void ChemistryLogicModel::levelUp()
{
    if(m_level < 4)
    {
        m_level++;
    }
    gameModel();
    emit sendLevel(m_level);
}

void ChemistryLogicModel::gameModel()
{
    switch(m_level)
    {
        case 1:
        levelOneSetUp();
        break;
        case 2:
        levelTwoSetUp();
        break;
        case 3:
        levelThreeSetUp();
        break;
        case 4:
        levelFourSetUp();
        break;
    }
}

void ChemistryLogicModel::levelOneSetUp()
{
    Chemical FeCl3("FeCl3", State::aqueous, QColor());
    Chemical Na2CO3("Na2CO3", State::aqueous, QColor());
    Chemical HCl("HCl", State::aqueous, QColor());
    Chemical NaCl("NaCl", State::aqueous, QColor());
    Chemical FeO("FeO", State::solid, QColor(101, 67, 33));
    Chemical CO2("CO2", State::gas, QColor());
    Chemical H2O("H2O", State::liquid, QColor());

    m_chemicals.insert("FeCl3", FeCl3);
    m_chemicals.insert("Na2CO3", Na2CO3);
    m_chemicals.insert("HCl", HCl);
    m_chemicals.insert("NaCl", NaCl);
    m_chemicals.insert("FeO", FeO);
    m_chemicals.insert("CO2", CO2);
    m_chemicals.insert("H2O", H2O);

    m_reactants.push_back("FeCl3");
    m_reactants.push_back("Na2CO3");
    m_reactants.push_back("HCl");
    m_reactions.addLevelOne();

    emit sendAllReactants(m_reactants);
    emit sendAllReactionsFormula(m_reactions.getAllReactions());
    emit addReactants(3);

}

void ChemistryLogicModel::levelTwoSetUp()
{
    Chemical NaOH("NaOH", State::aqueous, QColor());
    Chemical FeOH("FeOH", State::solid, QColor(101, 67, 33));
    m_chemicals.insert("NaOH", NaOH);
    m_chemicals.insert("FeOH", FeOH);
    m_reactions.addLevelTwo();

    m_reactants.push_back("NaOH");
    emit sendAllReactionsFormula(m_reactions.getAllReactions());
    emit sendReactant("NaOH");
    emit addReactants(1);
}

void ChemistryLogicModel::levelThreeSetUp()
{
    Chemical AgNO3("AgNO3", State::aqueous, QColor());
    Chemical AgCl("AgCl", State::solid, QColor(255, 255, 255));
    Chemical FeNO3("FeNO3", State::aqueous, QColor());
    Chemical NaNO3("NaNO3", State::aqueous, QColor());
    Chemical AgOH("AgOH", State::solid, QColor(128, 128, 128));
    Chemical AgCO3("AgCO3", State::solid, QColor(255, 255, 255));

    m_chemicals.insert("AgNO3", AgNO3);
    m_chemicals.insert("AgCl", AgCl);
    m_chemicals.insert("FeNO3", FeNO3);
    m_chemicals.insert("NaNO3", NaNO3);
    m_chemicals.insert("AgOH", AgOH);
    m_chemicals.insert("AgCO3", AgCO3);
    m_reactions.addLevelThree();

    m_reactants.push_back("AgNO3");
    emit sendAllReactionsFormula(m_reactions.getAllReactions());
    emit sendReactant("AgNO3");
    emit addReactants(1);
}

void ChemistryLogicModel::levelFourSetUp()
{
    Chemical Na3PO4("Na3PO4", State::aqueous, QColor());
    Chemical FePO4("FePO4", State::solid, QColor(255, 255, 128));

    m_chemicals.insert("Na3PO4", Na3PO4);
    m_chemicals.insert("FePO4", FePO4);
    m_reactions.addLevelFour();

    m_reactants.push_back("Na3PO4");
    emit sendAllReactionsFormula(m_reactions.getAllReactions());
    emit sendReactant("Na3PO4");
    emit addReactants(1);
}

void ChemistryLogicModel::chemicalSelected(QString formula)
{
    emit sendChemical(m_chemicals.find(formula).value());
}

Reactions ChemistryLogicModel::getAllReaction()
{
    emit sendAllReactionsFormula(m_reactions.getAllReactions());
    return m_reactions;
}

QVector<QString> ChemistryLogicModel::getAllChemicals()
{
    return m_chemicals.keys();
}

vector<QString> ChemistryLogicModel::getAllReactants()
{
    return m_reactants;
}

void ChemistryLogicModel::chemicalsMixed(QString formula1, QString formula2)
{
//    Reaction reaction = m_reactions.getReaction(Chemical(m_chemicals.find(formula1).value()), Chemical(m_chemicals.find(formula2).value()));

//    emit sendProducts(productChemicals);
}
