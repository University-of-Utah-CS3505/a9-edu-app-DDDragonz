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
    /// @brief Standard Constructor. Default sets the level to 1 and sets the sets the myster substances to reactants
    explicit ChemistryLogicModel(QObject *parent = nullptr);

    /// @brief Get the level
    int getLevel();

    /// @brief Switches level based on the current one
    void gameModel();

    /// @brief Returns all of the reactions
    /// @return the reactions
    Reactions getAllReaction();

    /// @brief Returns all of the chemicals
    /// @return the chemicals
    QVector<QString> getAllChemicals();

    /// @brief Returns all of the reactangs
    /// @return the chemicals
    std::vector<QString> getAllReactants();

private:
    QMap<QString, Chemical> m_chemicals;
    int m_level;
    Reactions m_reactions;
    std::vector<QString> m_reactants;
    Mysteries m_mysteries;
    QString m_currentSubstance1;
    QString m_currentSubstance2;

    /// @brief Sets up level one
    void levelOneSetUp();

    /// @brief Sets up level two
    void levelTwoSetUp();

    /// @brief Sets up level three
    void levelThreeSetUp();

    /// @brief Sets up level four
    void levelFourSetUp();

signals:
    /// @brief Sends the chemical
    /// @param chemical The chemical selected
    void sendChemical(Chemical& chemical);

    /// @brief A list of all the products
    /// @param products A list of products
    void sendProducts(QVector<Chemical> products);

    /// @brief A list of all the reaction names
    /// @param reactions A list of reactions
    void sendAllReactionsFormula(QString reactions);

    /// @brief Sends the level to advance to
    /// @param level The current level
    void sendLevel(int level);

    /// @brief A list of all the reactants
    /// @param reactants  A list of reactants
    void sendAllReactants(std::vector<QString> reactants);

    /// @brief Sends the name of the chemical
    /// @param reactant The selected chemical name
    void sendReactant(QString reactant);

    /// @brief Adds the chemicals to mix
    /// @param number The number of reactants to add
    void addReactants(int number);

    /// @brief Emits the signal to stay on the current level
    void levelKeep();

    /// @brief Emits the signal for the game to end
    void gameComplete();

    /// @brief Sends the reaction results to the mixing model
    /// @param reactionResult The reaction of the two chemicals
    void sendChemicalMixResult(Reaction reactionResult);

    /// @brief Sends the reaction results to the mixing model
    /// @param reaction The reaction of the two chemicals
    void sendReaction(Reaction reaction);

    /// @brief Sends the reaction results to the mixing model
    /// @param substance1 The first chemical selected
    /// @param substance2 The second chemical selected
    /// @param identifiers The list of attributes selected
    void sendReactionIdentifiers(QString substance1, QString substance2, QString identifiers);

public slots:
    /// @brief Sends the formula value of the chemical
    /// @param formula The string name of the chemical
    void chemicalSelected(QString formula);

    /// @brief Gets the actual chemical and sends the reaction to the mixing model
    /// @param formula1 The first chemical selected
    /// @param formula2 The second chemical selected
    void chemicalsMixed(QString formula1, QString formula2);

    /// @brief Deals with the correctness of the submitted responses
    /// @param choices The options to choose
    void levelUp(vector<QString> choices);

    /// @brief Gets the attributes selected to update the table
    /// @param identifiers The list of attributes selected
    void receiveIdentifiers(QString identifiers);
};

#endif // CHEMISTRYLOGICMODEL_H
