#include "reactionidentifiers.h"
#include "ui_reactionidentifiers.h"

ReactionIdentifiers::ReactionIdentifiers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReactionIdentifiers)
{
    ui->setupUi(this);
    ui->colorBox->addItem("Dark Brown");
    ui->colorBox->addItem("White");
    ui->colorBox->addItem("Grey");
    ui->colorBox->addItem("Light Yellow");
    ui->colorBox->addItem("Yellow");
    ui->submitButton->setEnabled(false);

    connect(ui->solidBox,
            &QCheckBox::toggled,
            ui->colorBox,
            &QComboBox::setEnabled);

    connect(ui->submitButton,
            &QPushButton::clicked,
            this,
            &ReactionIdentifiers::submitSelected);
}

ReactionIdentifiers::~ReactionIdentifiers()
{
    delete ui;
}

void ReactionIdentifiers::mixSelected()
{
    ui->submitButton->setEnabled(true);
}

void ReactionIdentifiers::doneMixingSelected()
{
    ui->submitButton->setEnabled(false);
}

void ReactionIdentifiers::submitSelected()
{
    ui->submitButton->setEnabled(false);
    QString identifiers;
    if (ui->bubblesBox->isChecked())
    {
        ui->bubblesBox->setChecked(false);
        identifiers.append("bubbles");
    }
    if (ui->noReactionBox->isChecked())
    {
        ui->noReactionBox->setChecked(false);
        if (identifiers.length() != 0)
        {
            identifiers.append(", ");
        }
        identifiers.append("no reaction");
    }
    if (ui->solidBox->isChecked())
    {
        ui->solidBox->setChecked(false);
        QString color = ui->colorBox->currentText();
        if (identifiers.length() != 0)
        {
            identifiers.append(", ");
        }
        identifiers.append(color);
        identifiers.append(" solid");
    }
    emit sendIdentifiers(identifiers);
}
