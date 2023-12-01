#include "mysterycombopair.h"
#include "ui_mysterycombopair.h"

MysteryComboPair::MysteryComboPair(QString mystery, vector<QString> chemicals, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysteryComboPair)
{
    ui->setupUi(this);
    ui->label->setText(mystery);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        ui->comboBox->addItem(chemicals.at(i));
    }
}

MysteryComboPair::MysteryComboPair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysteryComboPair)
{
    ui->setupUi(this);
    ui->label->setText("FeCl<sub>3</sub>");
    ui->comboBox->addItem("NaOh");
    ui->comboBox->addItem("FeCl<sub>3</sub>");
}

MysteryComboPair::~MysteryComboPair()
{
    delete ui;
}
