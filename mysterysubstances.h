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
    /// @brief Standard Constructor. Sets up ui and makes connections
    explicit MysterySubstances(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor.
    ~MysterySubstances();

    /// @brief Makes a list of mystery substances and connects them
    /// @param number The number of substances to make
    void addMysterySubstance(int number);

private:
    Ui::MysterySubstances *m_ui;
    int m_numberSelected;
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

    /// @brief Advances everything to the next level
    /// @param level The level to go to
    void levelUp(int level);

    /// @brief Makes sure only 2 buttons can be pressed
    void updateMixButton();

signals:
    void mixChemicals();
    void mixingChemicals(QString chemicalA, QString chemicalB);
    void doneMixing();
};

#endif // MYSTERYSUBSTANCES_H
