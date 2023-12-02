#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstancebuttoncombo.h"

MysterySubstanceButtonCombo::MysterySubstanceButtonCombo(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstanceButtonCombo)
{
    ui->setupUi(this);
    ui->label->setText(ui->label->text() + QString::fromStdString(std::to_string('A' + number)));

    connect(ui->selectButton,
            &QPushButton::clicked,
            this,
            &MysterySubstanceButtonCombo::buttonSelected);
}

MysterySubstanceButtonCombo::~MysterySubstanceButtonCombo()
{
    delete ui;
}

void MysterySubstanceButtonCombo::buttonSelected()
{
    if(ui->selectButton->isChecked())
    {
        emit substanceSelected(ui->selectButton->text());
        emit mysterySubstanceSelected();
    }
    else
    {
        emit substanceDeselected(ui->selectButton->text());
        emit mysterySubstanceDeselected();
    }
}

void MysterySubstanceButtonCombo::mixingChemicals()
{
    ui->selectButton->setChecked(false);
    ui->selectButton->setEnabled(false);
}

void MysterySubstanceButtonCombo::doneMixingChemicals()
{
    ui->selectButton->setChecked(false);
    ui->selectButton->setEnabled(true);
}
