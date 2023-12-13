#include "chemistrylogicmodel.h"
#include "reaction.h"
using std::vector;

ChemistryLogicModel::ChemistryLogicModel(QObject *parent)
    : QObject{parent},
    m_level(0),
    m_mysteries(m_reactants)
{
}

int ChemistryLogicModel::getLevel()
{
    return m_level;
}

void ChemistryLogicModel::levelUp(vector<QString> choices)
{
    if(m_mysteries.checkChemicals(choices))
    {
        if(m_level < 4)
        {
            m_level++;
            gameModel();
            emit sendLevel(m_level);
        }
        else
        {
            emit gameComplete();
        }

        if(m_level == 3)
        {
            m_level++;
            gameModel();
            emit sendLevel(m_level);
        }
    }
    else
    {
        emit levelKeep();
    }
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

    m_mysteries.addChemical("FeCl3");
    m_mysteries.addChemical("Na2CO3");
    m_mysteries.addChemical("HCl");
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

    m_mysteries.addChemical("NaOH");
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

    m_mysteries.addChemical("AgNO3");
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

    m_mysteries.addChemical("Na3PO4");
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
    m_currentSubstance1 = formula1;
    m_currentSubstance2 = formula2;
    Chemical chemical1 = m_chemicals.find(m_mysteries.getChemical(formula1)).value();
    Chemical chemical2 = m_chemicals.find(m_mysteries.getChemical(formula2)).value();

    Reaction reaction = m_reactions.getReaction(chemical1, chemical2);
    emit sendChemicalMixResult(reaction);
    emit sendReaction(reaction);
}

void ChemistryLogicModel::receiveIdentifiers(QString identifiers)
{
    emit sendReactionIdentifiers(m_currentSubstance1, m_currentSubstance2, identifiers);
}
