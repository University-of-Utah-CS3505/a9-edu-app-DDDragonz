#include "identifychemicals.h"
#include "ui_identifychemicals.h"
#include "mysterycombopair.h"
#include <QLabel>
#include <QDebug>

using std::string;

IdentifyChemicals::IdentifyChemicals(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdentifyChemicals),
    m_choicesSize(0)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &IdentifyChemicals::submitClick);
    m_numberOfSubstances = 0;
}

void IdentifyChemicals::addElements(vector<QString> chemicals)
{
    m_firstChoice = chemicals.at(0);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
       addElement(chemicals.at(i));
    }
}


void IdentifyChemicals::submitClick()
{
    vector<QString> choices;
    for(int i = 0; i < m_choicesSize; i++)
    {
       choices.push_back(m_choices[i]);
    }
    emit submitToNextLevel(choices);
    emit clearWorld();
}

void IdentifyChemicals::addElement(QString chemical)
{
    m_choicesSize++;
    if(m_numberOfSubstances >= 6)
    {
       return;
    }

    char numberCharacter = 'A' + m_numberOfSubstances;
    string name = "Substance ";
    m_choices[m_choicesSize - 1] = m_firstChoice;
    name += numberCharacter;
    m_prevChemicals.push_back(chemical);
    MysteryComboPair* toAdd = new MysteryComboPair(m_numberOfSubstances, QString::fromStdString(name), m_prevChemicals);
    connect(toAdd, &MysteryComboPair::choiceChange, this, &IdentifyChemicals::choiceChange);
    ui->layout->addWidget(toAdd);

    for(int i = 0; i < (int)m_comboPairs.size(); i++)
    {
       m_comboPairs.at(i)->addComboItem(chemical, i);
    }
    m_comboPairs.push_back(toAdd);
    m_numberOfSubstances++;
}

void IdentifyChemicals::choiceChange(QString chemical, int index)
{
   // qDebug() << "Index:" << index ;
    m_choices[index] = chemical;

}

IdentifyChemicals::~IdentifyChemicals()
{
    delete ui;
}
