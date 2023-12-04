#include "mysterysubstances.h"
#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstances.h"

using std::string;

MysterySubstances::MysterySubstances(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstances)
{
    ui->setupUi(this);
    m_numberSelected = 0;
    updateMixButton();
    ui->doneButton->setEnabled(false);
    m_chemicalSize = 3;

    connect(ui->mixButton,
            &QPushButton::clicked,
            this,
            &MysterySubstances::mixButtonClicked);

    connect(ui->doneButton,
            &QPushButton::clicked,
            this,
            &MysterySubstances::doneButtonClicked);
}

MysterySubstances::~MysterySubstances()
{
    delete ui;
}

void MysterySubstances::addMysterySubstances(int number)
{
    for(int i = 0; i < number; i++)
    {
        addMysterySubstance(m_numberOfSubstances++);
    }
}

void MysterySubstances::addMysterySubstance(int number)
{
    if(m_numberOfSubstances > 6)
    {
        return;
    }

    MysterySubstanceButtonCombo* toAdd = new MysterySubstanceButtonCombo(number);
    ui->layout->addWidget(toAdd);

    connect(toAdd,
            &MysterySubstanceButtonCombo::mysterySubstanceSelected,
            this,
            &MysterySubstances::buttonSelected);

    connect(toAdd,
            &MysterySubstanceButtonCombo::mysterySubstanceDeselected,
            this,
            &MysterySubstances::buttonDeselected);

    connect(toAdd,
            &MysterySubstanceButtonCombo::substanceSelected,
            this,
            &MysterySubstances::chemicalSelected);

    connect(toAdd,
            &MysterySubstanceButtonCombo::substanceDeselected,
            this,
            &MysterySubstances::chemicalDeselected);

    connect(this,
            &MysterySubstances::mixChemicals,
            toAdd,
            &MysterySubstanceButtonCombo::mixingChemicals);

    connect(this,
            &MysterySubstances::doneMixing,
            toAdd,
            &MysterySubstanceButtonCombo::doneMixingChemicals);
}

void MysterySubstances::buttonDeselected()
{
    m_numberSelected--;
    updateMixButton();
}

void MysterySubstances::buttonSelected()
{
    m_numberSelected++;
    updateMixButton();
}

void MysterySubstances::updateMixButton()
{
    if(m_numberSelected == 2)
    {
        ui->mixButton->setEnabled(true);
    }
    else
    {
        ui->mixButton->setEnabled(false);
    }
}

void MysterySubstances::mixButtonClicked()
{
    m_numberSelected = 0;
    ui->mixButton->setEnabled(false);
    emit mixChemicals();
    ui->doneButton->setEnabled(true);

    QString chemicalA = "Substance ";
    QString chemicalB = "Substance ";
    for(int i = 0; i < m_chemicalSize; i++)
    {
        if(m_chemicalSelected[i] && chemicalA == "Substance ")
        {
            char letter = 'A' + i;
            chemicalA += letter;
        }
        else if(m_chemicalSelected[i] && chemicalB == "Substance ")
        {
            char letter = 'A' + i;
            chemicalB += letter;
            emit mixingChemicals(chemicalA, chemicalB);
            break;
        }
        else if(m_chemicalSelected[i])
        {
            printf("Something is very, very wrong.\n");
        }
    }
}

void MysterySubstances::doneButtonClicked()
{
    emit doneMixing();
    ui->doneButton->setEnabled(false);

    for(int i = 0; i < m_chemicalSize; i++)
    {
        m_chemicalSelected[i] = false;
    }
}

void MysterySubstances::chemicalSelected(QString chemical)
{
    string name = chemical.toStdString();
    char letter = name.at(chemical.size() - 1);
    int number = letter - 'A';
    m_chemicalSelected[number] = true;
}
void MysterySubstances::chemicalDeselected(QString chemical)
{
    string name = chemical.toStdString();
    char letter = name.at(chemical.size() - 1);
    int number = letter - 'A';
    m_chemicalSelected[number] = false;
}

void MysterySubstances::levelUp(int level)
{
    m_chemicalSize = level + 2;
}
