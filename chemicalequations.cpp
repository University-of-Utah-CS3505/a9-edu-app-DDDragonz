#include "chemicalequations.h"
#include "ui_chemicalequations.h"
#include <QLabel>

ChemicalEquations::ChemicalEquations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChemicalEquations)
{
    ui->setupUi(this);
}

void ChemicalEquations::addEquations(vector<QString> equations)
{
    QLabel* label = new QLabel();
    label->setText("Significant Equations");
    label->setAlignment(Qt::AlignCenter);
    ui->layout->addWidget(label);

    for(int i = 0; i < (int)equations.size(); i++)
    {
        addEquation(equations.at(i));
    }
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
