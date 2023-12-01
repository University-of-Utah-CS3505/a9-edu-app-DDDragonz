#include "mysterysubstances.h"
#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstances.h"

MysterySubstances::MysterySubstances(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstances)
{
    ui->setupUi(this);
}

MysterySubstances::~MysterySubstances()
{
    delete ui;
}

void MysterySubstances::addMysterySubstances(int number)
{
    for(int i = 0; i < number; i++)
    {
        addMysterySubstance(i);
    }
}

void MysterySubstances::addMysterySubstance(int number)
{
    MysterySubstanceButtonCombo* toAdd = new MysterySubstanceButtonCombo(number);
    ui->layout->addWidget(toAdd);
}
