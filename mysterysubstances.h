#ifndef MYSTERYSUBSTANCES_H
#define MYSTERYSUBSTANCES_H

#include <QWidget>

namespace Ui {
class MysterySubstances;
}

class MysterySubstances : public QWidget
{
    Q_OBJECT

public:
    explicit MysterySubstances(QWidget *parent = nullptr);
    ~MysterySubstances();
    void addMysterySubstance(int number);
    void addMysterySubstances(int number);

private:
    Ui::MysterySubstances *ui;
};

#endif // MYSTERYSUBSTANCES_H
