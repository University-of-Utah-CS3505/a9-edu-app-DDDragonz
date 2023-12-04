#ifndef IDENTIFYCHEMICALS_H
#define IDENTIFYCHEMICALS_H

#include <QWidget>
#include "mysterycombopair.h"
#include "mysteries.h"

using std::vector;
using std::map;

namespace Ui {
class IdentifyChemicals;
}

class IdentifyChemicals : public QWidget
{
    Q_OBJECT

public:
    IdentifyChemicals(QWidget *parent = nullptr);
    ~IdentifyChemicals();

private:
    Ui::IdentifyChemicals *ui;
    vector<MysteryComboPair*> m_comboPairs;
    vector<QString> m_prevChemicals;
    int m_numberOfSubstances;
    vector<QString> m_choices;

signals:
    void submitToNextLevel(vector<QString> choices);

public slots:
    void submitClick();
    void addElements(vector<QString> chemicals);
    void addElement(QString chemical);
    void choiceChange(QString chemical, int index);
};

#endif // IDENTIFYCHEMICALS_H
