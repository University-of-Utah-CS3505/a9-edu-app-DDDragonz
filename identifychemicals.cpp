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
    connect(ui->pushButton, &QPushButton::clicked, this, &IdentifyChemicals::submitClick);
    m_numberOfSubstances = 0;
}

void IdentifyChemicals::addElements(vector<QString> chemicals)
{
    m_choices.resize(chemicals.size());
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
       addElement(chemicals.at(i));
    }
}


void IdentifyChemicals::submitClick()
{
    emit submitToNextLevel(m_choices);
}

void IdentifyChemicals::addElement(QString chemical)
{
    if(m_numberOfSubstances >= 6)
    {
       return;
    }

    char numberCharacter = 'A' + m_numberOfSubstances;
    string name = "Substance ";
    name += numberCharacter;
    m_prevChemicals.push_back(chemical);
    MysteryComboPair* toAdd = new MysteryComboPair(QString::fromStdString(name), m_prevChemicals);
    ui->layout->addWidget(toAdd);

    for(int i = 0; i < (int)m_comboPairs.size(); i++)
    {
       m_comboPairs.at(i)->addComboItem(chemical, i);
       m_choices[i] = chemical;
       connect(m_comboPairs.at(i), &MysteryComboPair::choiceChange, this, &IdentifyChemicals::choiceChange);
    }
    m_comboPairs.push_back(toAdd);
    m_numberOfSubstances++;
}

void IdentifyChemicals::choiceChange(QString chemical, int index)
{
    m_choices[index] = chemical;
}

IdentifyChemicals::~IdentifyChemicals()
{
    delete ui;
}
