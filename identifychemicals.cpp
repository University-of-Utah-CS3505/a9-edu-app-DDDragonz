#include "identifychemicals.h"
#include "ui_identifychemicals.h"
#include "mysterycombopair.h"
#include <QLabel>

using std::string;

IdentifyChemicals::IdentifyChemicals(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdentifyChemicals)
{
    ui->setupUi(this);

    QLabel* label = new QLabel();
    label->setText("Identify the Substances");
    label->setAlignment(Qt::AlignHCenter);
    ui->layout->addWidget(label);

    connect(ui->pushButton, &QPushButton::clicked, this, &IdentifyChemicals::submitClick);
}

void IdentifyChemicals::addElements(vector<QString> chemicals)
{
    QLayoutItem* item;
    while ((item = ui->layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        addElement(i, chemicals.at(i));
    }
}


void IdentifyChemicals::submitClick()
{
    emit submitToNextLevel();
}

void IdentifyChemicals::addElement(int number, QString chemical)
{
    char numberCharacter = 'A' + number;
    string name = "Substance ";
    name += numberCharacter;
    m_prevChemicals.push_back(chemical);
    MysteryComboPair* toAdd = new MysteryComboPair(QString::fromStdString(name), m_prevChemicals);
    ui->layout->addWidget(toAdd);

    for(int i = 0; i < (int)m_comboPairs.size(); i++)
    {
        m_comboPairs.at(i)->addComboItem(chemical);
    }
    m_comboPairs.push_back(toAdd);
}

IdentifyChemicals::~IdentifyChemicals()
{
    delete ui;
}
