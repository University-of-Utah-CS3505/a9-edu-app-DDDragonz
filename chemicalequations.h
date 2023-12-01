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
    explicit ChemicalEquations(QWidget *parent = nullptr);
    ~ChemicalEquations();
    void addEquations(vector<QString> equations);

private:
    Ui::ChemicalEquations *ui;
};

#endif // CHEMICALEQUATIONS_H
