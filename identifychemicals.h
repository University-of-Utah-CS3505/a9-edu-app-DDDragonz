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

private:
    Ui::IdentifyChemicals *ui;
};

#endif // IDENTIFYCHEMICALS_H
