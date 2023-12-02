#ifndef MYSTERIES_H
#define MYSTERIES_H

#include <QString>
#include <vector>

using std::vector;

class Mysteries
{
public:
    Mysteries(vector<QString> chemicals);
    bool checkSubstances(QString substances[]);
    void addChemical(QString chemical);
    bool checkChemicals(vector<QString> toCheck);
    QString getChemical(QString mysteryName);
    QString getChemical(int number);

private:
    QString m_substances[6];
    int m_size;
    void shuffle();
};

#endif // MYSTERIES_H
