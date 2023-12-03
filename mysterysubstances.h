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
    int m_numberOfSubstances;
    bool m_chemicalSelected[6];
    int m_chemicalSize;

public slots:
    void buttonSelected();
    void buttonDeselected();
    void mixButtonClicked();
    void doneButtonClicked();
    void addMysterySubstances(int number);
    void chemicalSelected(QString chemical);
    void chemicalDeselected(QString chemical);
    void levelUp();

signals:
    void mixChemicals();
    void mixingChemicals(QString chemicalA, QString chemicalB);
    void doneMixing();
};

#endif // MYSTERYSUBSTANCES_H
