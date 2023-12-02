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

private:
    Ui::MysterySubstances *ui;
    int m_numberSelected;
    void updateMixButton();

public slots:
    void buttonSelected();
    void buttonDeselected();
    void mixButtonClicked();
    void doneButtonClicked();
    void addMysterySubstances(int number);

signals:
    void mixChemicals();
    void doneMixing();
};

#endif // MYSTERYSUBSTANCES_H
