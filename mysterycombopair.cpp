#include "mysterycombopair.h"
#include "ui_mysterycombopair.h"

MysteryComboPair::MysteryComboPair(int index, QString mystery, vector<QString> chemicals, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysteryComboPair),
    m_index(index)
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
    this->m_index = index;
}

void MysteryComboPair::comboChange(QString chemical)
{
    emit choiceChange(chemical, m_index);
}

MysteryComboPair::~MysteryComboPair()
{
    delete ui;
}
