#include "chemicalequations.h"
#include "ui_chemicalequations.h"
#include <QLabel>

ChemicalEquations::ChemicalEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChemicalEquations)
{
    ui->setupUi(this);
    QLabel* label = new QLabel();
    label->setText("Significant Equations");
    label->setAlignment(Qt::AlignCenter);
    ui->layout->addWidget(label);
}

void ChemicalEquations::receiveFormula(QString formulas)
{
    QLabel* label = new QLabel();
    label->setText(formulas);
    label->setWordWrap(true);
    ui->layout->addWidget(label);
}

void ChemicalEquations::addEquation(QString equation)
{
    QLabel* label = new QLabel();
    label->setText(equation);
    label->setWordWrap(true);
    ui->layout->addWidget(label);
}

ChemicalEquations::~ChemicalEquations()
{
    delete ui;
}
