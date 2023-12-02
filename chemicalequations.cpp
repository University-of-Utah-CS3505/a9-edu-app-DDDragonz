#include "chemicalequations.h"
#include "ui_chemicalequations.h"
#include <QLabel>

ChemicalEquations::ChemicalEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChemicalEquations)
{
    ui->setupUi(this);
}

void ChemicalEquations::receiveFormula(QString formulas)
{
    ui->equationsLabel->setText(formulas);
}

void ChemicalEquations::addEquation(QString equation)
{
    ui->equationsLabel->setText(equation);
}

ChemicalEquations::~ChemicalEquations()
{
    delete ui;
}
