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
    /// @brief Receives information that a chemical was selected
    void buttonSelected();

    /// @brief Receives information that a chemical was deselected
    void buttonDeselected();

    /// @brief Receives information that the mix button was clicked
    void mixButtonClicked();

    /// @brief Receives information that the done mixing button was clicked
    void doneButtonClicked();

    /// @brief Receives information that a mystery substance needs to be added
    void addMysterySubstances(int number);

    /// @brief Receives information about which chemical was selected
    /// @param chemical The name of the chemical that was selected
    void chemicalSelected(QString chemical);

    /// @brief Receives information about which chemical was deselected
    /// @param chemical The name of the chemical that was deselected
    void chemicalDeselected(QString chemical);

    /// @brief Receives information that everything needs to advance to the next level
    /// @param level The level to go to
    void levelUp(int level);

    /// @brief Receives information to make sure only 2 buttons can be pressed and mixed
    void updateMixButton();

signals:
    /// @brief Sends information to the program that chemicals need to be mixed
    void mixChemicals();

    /// @brief Sends information to the program that chemicals need to be mixed
    /// @param chemicalA One of the chemicals being mixed
    /// @param chemicalB One of the chemicals being mixed
    void mixingChemicals(QString chemicalA, QString chemicalB);

    /// @brief Sends information to the program that chemicals are done mixing
    void doneMixing();
};

#endif // MYSTERYSUBSTANCES_H
