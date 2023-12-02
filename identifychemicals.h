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

signals:
    void submitToNextLevel();

public slots:
    void submitClick();
    void addElements(vector<QString> chemicals);
    void addElement(QString chemical);
};

#endif // IDENTIFYCHEMICALS_H
