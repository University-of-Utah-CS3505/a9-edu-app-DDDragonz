#include "mysterycombopair.h"
#include "ui_mysterycombopair.h"

MysteryComboPair::MysteryComboPair(QString mystery, vector<QString> chemicals, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysteryComboPair),
    index(0)
{
    ui->setupUi(this);
    ui->label->setText(mystery);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        ui->comboBox->addItem(chemicals.at(i));
    }

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MysteryComboPair::comboChange);
}

MysteryComboPair::MysteryComboPair(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysteryComboPair)
{
    ui->setupUi(this);
}

void MysteryComboPair::addComboItem(QString name, int index)
{
    ui->comboBox->addItem(name);
    this->index = index;
}

void MysteryComboPair::comboChange(QString chemical)
{
    emit choiceChange(chemical, index);
}

MysteryComboPair::~MysteryComboPair()
{
    delete ui;
}
