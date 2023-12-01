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

    connect(ui->solidBox,
            &QCheckBox::toggled,
            ui->colorBox,
            &QComboBox::setEnabled);
}

ReactionIdentifiers::~ReactionIdentifiers()
{
    delete ui;
}
