#ifndef IDENTIFYCHEMICALS_H
#define IDENTIFYCHEMICALS_H

#include <QWidget>
#include "mysterycombopair.h"

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
    void addElements(vector<QString> chemicals);
    void addElement(int number, QString chemical);

private:
    Ui::IdentifyChemicals *ui;
    vector<MysteryComboPair*> m_comboPairs;
    vector<QString> m_prevChemicals;
};

#endif // IDENTIFYCHEMICALS_H
