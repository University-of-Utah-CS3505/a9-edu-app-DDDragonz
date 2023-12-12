#include "chemicalequations.h"
#include "ui_chemicalequations.h"
#include <QLabel>

ChemicalEquations::ChemicalEquations(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ChemicalEquations)
{
    m_ui->setupUi(this);
}

void ChemicalEquations::receiveFormula(QString formulas)
{
    m_ui->equationsLabel->setText(formulas);
}

void ChemicalEquations::addEquation(QString equation)
{
    m_ui->equationsLabel->setText(equation);
}

ChemicalEquations::~ChemicalEquations()
{
    delete m_ui;
}
