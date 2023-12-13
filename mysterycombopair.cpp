#include "mysterycombopair.h"
#include "ui_mysterycombopair.h"

MysteryComboPair::MysteryComboPair(int index, QString mystery, vector<QString> chemicals, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MysteryComboPair),
    m_index(index)
{
    m_ui->setupUi(this);
    m_ui->label->setText(mystery);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        m_ui->comboBox->addItem(chemicals.at(i));
    }
    
    connect(m_ui->comboBox, &QComboBox::currentTextChanged, this, &MysteryComboPair::comboChange);
}

MysteryComboPair::MysteryComboPair(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MysteryComboPair)
{
    m_ui->setupUi(this);
}

void MysteryComboPair::addComboItem(QString name, int index)
{
    m_ui->comboBox->addItem(name);
    this->m_index = index;
}

void MysteryComboPair::comboChange(QString chemical)
{
    emit choiceChange(chemical, m_index);
}

MysteryComboPair::~MysteryComboPair()
{
    delete m_ui;
}
