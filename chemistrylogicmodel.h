#ifndef CHEMISTRYLOGICMODEL_H
#define CHEMISTRYLOGICMODEL_H

#include "chemical.h"
#include "reactions.h"
#include "mysteries.h"
#include <QMap>
#include <QVector>
#include <QPair>
#include <QObject>
#include <QColor>

class ChemistryLogicModel : public QObject
{
    Q_OBJECT
public:
    explicit ChemistryLogicModel(QObject *parent = nullptr);
    int getLevel();
    void gameModel();
    Reactions getAllReaction();
    QVector<QString> getAllChemicals();
    std::vector<QString> getAllReactants();

private:
    QMap<QString, Chemical> m_chemicals;
    int m_level;
    Reactions m_reactions;
    std::vector<QString> m_reactants;
    Mysteries m_mysteries;
    QString m_currentSubstance1;
    QString m_currentSubstance2;

    void levelOneSetUp();
    void levelTwoSetUp();
    void levelThreeSetUp();
    void levelFourSetUp();

signals:
    void sendChemical(Chemical& chemical);
    void sendProducts(QVector<Chemical> products);
    void sendAllReactionsFormula(QString reactions);
    void sendLevel(int level);
    void sendAllReactants(std::vector<QString> reactants);
    void sendReactant(QString reactant);
    void addReactants(int number);
    void levelKeep();
    void gameComplete();
    void sendChemicalMixResult(Reaction reactionResult);
    void sendReaction(Reaction reaction);
    void sendReactionIdentifiers(QString substance1, QString substance2, QString identifiers);

public slots:
    void chemicalSelected(QString formula);
    void chemicalsMixed(QString formula1, QString formula2);
    void levelUp(vector<QString> choices);
    void receiveIdentifiers(QString identifiers);
};

#endif // CHEMISTRYLOGICMODEL_H
