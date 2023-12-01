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
};

#endif // MYSTERYSUBSTANCEBUTTONCOMBO_H
