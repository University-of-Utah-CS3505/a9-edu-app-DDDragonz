#include "mysterysubstances.h"
#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstances.h"

MysterySubstances::MysterySubstances(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstances)
{
    ui->setupUi(this);
    m_numberSelected = 0;
    updateMixButton();
    ui->doneButton->setEnabled(false);

    connect(ui->mixButton,
            &QPushButton::clicked,
            this,
            &MysterySubstances::mixButtonClicked);

    connect(ui->doneButton,
            &QPushButton::clicked,
            this,
            &MysterySubstances::doneButtonClicked);
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

    connect(toAdd,
            &MysterySubstanceButtonCombo::mysterySubstanceSelected,
            this,
            &MysterySubstances::buttonSelected);

    connect(toAdd,
            &MysterySubstanceButtonCombo::mysterySubstanceDeselected,
            this,
            &MysterySubstances::buttonDeselected);

    connect(this,
            &MysterySubstances::mixChemicals,
            toAdd,
            &MysterySubstanceButtonCombo::mixingChemicals);

    connect(this,
            &MysterySubstances::doneMixing,
            toAdd,
            &MysterySubstanceButtonCombo::doneMixingChemicals);
}

void MysterySubstances::buttonDeselected()
{
    m_numberSelected--;
    updateMixButton();
}

void MysterySubstances::buttonSelected()
{
    m_numberSelected++;
    updateMixButton();
}

void MysterySubstances::updateMixButton()
{
    if(m_numberSelected == 2)
    {
        ui->mixButton->setEnabled(true);
    }
    else
    {
        ui->mixButton->setEnabled(false);
    }
}

void MysterySubstances::mixButtonClicked()
{
    m_numberSelected = 0;
    ui->mixButton->setEnabled(false);
    emit mixChemicals();
    ui->doneButton->setEnabled(true);
}

void MysterySubstances::doneButtonClicked()
{
    emit doneMixing();
    ui->doneButton->setEnabled(false);
}
