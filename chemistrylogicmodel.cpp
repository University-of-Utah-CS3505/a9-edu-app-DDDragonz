#include "chemistrylogicmodel.h"

ChemistryLogicModel::ChemistryLogicModel(QObject *parent)
    : QObject{parent},
    m_level(1)
{

}

void ChemistryLogicModel::addReactionRule(QList<QString> reactants, QList<QString> products)
{
    if(reactants.size() != 2)
    {
        return;
    }

    QList<Chemical> productsConvert;
    for(const QString& product : products)
    {
        auto it = m_chemicals.find(product);
        productsConvert.append(it.value());
    }

    auto reactant1 = m_chemicals.find(reactants[0]);
    auto reactant2 = m_chemicals.find(reactants[1]);

    reactant1.value().addReaction(reactants[1], productsConvert);
    reactant2.value().addReaction(reactants[0], productsConvert);
}

int ChemistryLogicModel::getLevel()
{
    return m_level;
}

QString ChemistryLogicModel::getCommonName(QString formula)
{
    auto chemical = m_chemicals.find(formula);
    if(chemical != m_chemicals.end())
    {
        return chemical.value().getCommonName();
    }
    return QString();
}

QString ChemistryLogicModel::getSystematicName(QString formula)
{
    auto chemical = m_chemicals.find(formula);
    if(chemical != m_chemicals.end())
    {
        return chemical.value().getSystematicName();
    }
    return QString();
}

int ChemistryLogicModel::getPH(QString formula)
{
    auto chemical = m_chemicals.find(formula);
    if(chemical != m_chemicals.end())
    {
        return chemical.value().getPH();
    }
    return NULL;
}

QString ChemistryLogicModel::getNote(QString formula)
{
    auto chemical = m_chemicals.find(formula);
    if(chemical != m_chemicals.end())
    {
        return chemical.value().getNote();
    }
    return QString();
}

void ChemistryLogicModel::levelUp()
{
    m_level++;
}

void ChemistryLogicModel::gameModel()
{
    if (m_level == 1)
    {
        levelOneSetUp();
    }
}

void ChemistryLogicModel::levelOneSetUp()
{
    Chemical HCl("Hydrochloric acid", "HCl", "Hydrogen Chloride", 0.0, "Hydrogen Chloride is a gas at room temperature. However, for the purposes of this lab, we will refer to hydrochloric acid as the aqueous solution of HCl dissolved in water.", "Liquid");
    Chemical NaOH("Sodium Hydroxide", "NaOH", "Sodium Hydroxide", 14.0, "Sodium Hydroxide is a solid at room temperature. However, for the purposes of this lab, we will refer to sodium hydroxide as the aqueous solution of NaOH dissolved in water.", "Liquid");
    Chemical H2O2("Hydrogen peroxide", "H2O2", "Hydrogen peroxide",3.0, "None", "Liquid");
    Chemical NaCl("Salt", "NaCl", "Sodium chloride", 7.0, "NaCl is commonly known as table salt and is used widely to season and preserve food.", "Solid");
    Chemical H2O("Water", "H2O", "Dihydrogen monoxide", 7.0, "None", "");
    Chemical Cl2("Chlorine gas", "Cl2", "Dichlorine", NULL, "Chlorine gas is dangerous to humans and exposure should be avoided.", "Gas");
    Chemical O2("Oxygen", "O2", "Dioxygen", NULL, "None", "Gas");
    Chemical NaIon("Sodium", "Na+", "Sodium ion", NULL, "None", "None");

    m_chemicals.insert("HCl", HCl);
    m_chemicals.insert("NaOH", NaOH);
    m_chemicals.insert("H2O2", H2O2);
    m_chemicals.insert("NaCl", NaCl);
    m_chemicals.insert("H2O", H2O);
    m_chemicals.insert("Cl2", Cl2);
    m_chemicals.insert("O2", O2);
    m_chemicals.insert("Na+", NaIon);

    QVector<QPair<QVector<QString>,QVector<QString>>> reactions;
    reactions.append(qMakePair(QVector<QString>{"HCl", "NaOH"}, QVector<QString>{"NaCl", "H2O"}));
    reactions.append(qMakePair(QVector<QString>{"HCl", "H2O2"}, QVector<QString>{"Cl2", "H2O"}));
    reactions.append(qMakePair(QVector<QString>{"NaOH", "H2O2"}, QVector<QString>{"H2O", "O2", "NaIon"}));
    addAllReactionRule(reactions);
}

QVector<QString> ChemistryLogicModel::simulateReaction(QString reactant1, QString reactant2)
{
    QList<QString> productionsConvert;
    if(m_chemicals.contains(reactant1) && m_chemicals.contains(reactant2))
    {
        auto reactant1Convert = m_chemicals.find(reactant1);
        auto reactant2Convert = m_chemicals.find(reactant2);
        if(!reactant1Convert.value().getReactions(reactant2).isEmpty() && !reactant2Convert.value().getReactions(reactant1).isEmpty())
        {
            QList<Chemical> productions = reactant1Convert.value().getReactions(reactant2);

            for(Chemical& production : productions)
            {
                productionsConvert.append(production.getFormula());
            }
        }
    }
    return productionsConvert;
}

void ChemistryLogicModel::addAllReactionRule(QVector<QPair<QVector<QString>,QVector<QString>>> reactions)
{
    for(auto reaction : reactions)
    {
        QVector<QString> reactants = reaction.first;
        QVector<QString> products = reaction.second;
        addReactionRule(reactants, products);
    }
}

void ChemistryLogicModel::chemicalSelected(QString formula)
{
    emit sendChemical(m_chemicals.find(formula).value());
}

void ChemistryLogicModel::chemicalsMixed(QString formula1, QString formula2)
{
    QVector<QString> products = simulateReaction(formula1, formula2);
    QVector<Chemical> productChemicals;
    for (QString product : products)
    {
        productChemicals.append(m_chemicals.find(product).value());
    }
    emit sendProducts(productChemicals);
}
