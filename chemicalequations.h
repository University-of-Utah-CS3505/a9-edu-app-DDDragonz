#ifndef CHEMICALEQUATIONS_H
#define CHEMICALEQUATIONS_H

#include <QWidget>

using std::vector;

namespace Ui {
class ChemicalEquations;
}

class ChemicalEquations : public QWidget
{
    Q_OBJECT

public:
    /// @brief Standard Constructor
    explicit ChemicalEquations(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor
    ~ChemicalEquations();

    /// @brief Display the recieved equation
    /// @param equation The equation to display
    void addEquation(QString equation);

private:
    Ui::ChemicalEquations *m_ui;

public slots:
    /// @brief Display the recieved formulas
    /// @param formulas The formulas to display
    void receiveFormula(QString formulas);
};

#endif // CHEMICALEQUATIONS_H
