#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstancebuttoncombo.h"

MysterySubstanceButtonCombo::MysterySubstanceButtonCombo(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstanceButtonCombo)
{
    ui->setupUi(this);
    ui->label->setText(ui->label->text() + QString::fromStdString(std::to_string('A' + number)));
}

MysterySubstanceButtonCombo::~MysterySubstanceButtonCombo()
{
    delete ui;
}
