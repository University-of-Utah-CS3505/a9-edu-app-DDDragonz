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
//    QLabel* label = new QLabel();
//    label->setText("Identify the Substances");
//    label->setAlignment(Qt::AlignHCenter);
//    ui->layout->addWidget(label);
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        char number = 'A' + i;
        string name = "Substance ";
        name += number;
        MysteryComboPair* toAdd = new MysteryComboPair(QString::fromStdString(name), chemicals);
        ui->layout->addWidget(toAdd);
    }
}

void IdentifyChemicals::submitClick()
{
    emit submitToNextLevel();
}

IdentifyChemicals::~IdentifyChemicals()
{
    delete ui;
}
