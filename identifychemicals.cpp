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
}

void IdentifyChemicals::addElements(vector<QString> chemicals)
{
    QLabel* label = new QLabel();
    label->setText("Identify the Substances");
    label->setAlignment(Qt::AlignHCenter);
    ui->layout->addWidget(label);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        char number = 'A' + i;
        string name = "Substance ";
        name += number;
        MysteryComboPair* toAdd = new MysteryComboPair(QString::fromStdString(name), chemicals);
        ui->layout->addWidget(toAdd);
    }
    MysteryComboPair* toAdd = new MysteryComboPair("wtf", chemicals);
    ui->layout->addWidget(toAdd);
}

IdentifyChemicals::~IdentifyChemicals()
{
    delete ui;
}
