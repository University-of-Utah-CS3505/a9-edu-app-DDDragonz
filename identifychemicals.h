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

private:
    Ui::IdentifyChemicals *ui;

signals:
    void submitToNextLevel();

public slots:
    void submitClick();
    void addElements(vector<QString> chemicals);

};

#endif // IDENTIFYCHEMICALS_H
