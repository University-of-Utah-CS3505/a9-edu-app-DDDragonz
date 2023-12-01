#ifndef CHEMISTRYLOGICMODEL_H
#define CHEMISTRYLOGICMODEL_H

#include "chemical.h"
#include <QMap>
#include <QVector>
#include <QPair>
#include <QObject>

class ChemistryLogicModel : public QObject
{
    Q_OBJECT
public:
    explicit ChemistryLogicModel(QObject *parent = nullptr);

    void addReactionRule(QList<QString> reactants, QList<QString> products);
    int getLevel();
    QString getCommonName(QString formula);
    QString getSystematicName(QString formula);
    int getPH(QString formula);
    QString getNote(QString formula);
    void gameModel();
    QVector<QString> simulateReaction(QString reactant1, QString reactant2);

private:
    QMap<QString, Chemical> m_chemicals;
    int m_level;

    void levelOneSetUp();
    void addAllReactionRule(QVector<QPair<QVector<QString>,QVector<QString>>> reactions);

signals:
    void sendChemical(Chemical& chemical);
    void sendProducts(QVector<Chemical> products);
    void sendLevel(int level);

public slots:
    void chemicalSelected(QString formula);
    void chemicalsMixed(QString formula1, QString formula2);
    void levelUp();
};

#endif // CHEMISTRYLOGICMODEL_H
