#ifndef MYSTERYSUBSTANCEBUTTONCOMBO_H
#define MYSTERYSUBSTANCEBUTTONCOMBO_H

#include <QWidget>

namespace Ui {
class MysterySubstanceButtonCombo;
}

class MysterySubstanceButtonCombo : public QWidget
{
    Q_OBJECT

public:
    explicit MysterySubstanceButtonCombo(int number, QWidget *parent = nullptr);
    ~MysterySubstanceButtonCombo();

private:
    Ui::MysterySubstanceButtonCombo *ui;

public slots:
    void buttonSelected();
    void mixingChemicals();
    void doneMixingChemicals();

signals:
    void substanceSelected(QString name);
    void substanceDeselected(QString name);
    void mysterySubstanceSelected();
    void mysterySubstanceDeselected();
};

#endif // MYSTERYSUBSTANCEBUTTONCOMBO_H
