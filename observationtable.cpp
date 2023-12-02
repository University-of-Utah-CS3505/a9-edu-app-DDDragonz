#include "observationtable.h"
#include "ui_observationtable.h"

ObservationTable::ObservationTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObservationTable)
{
    ui->setupUi(this);
    tables.append(ui->levelOneTable);
    tables.append(ui->levelTwoTable);
    tables.append(ui->levelThreeTable);
    tables.append(ui->levelFourTable);

    ui->levelTwoTable->hide();
    ui->levelThreeTable->hide();
    ui->levelFourTable->hide();

    level = 1;
}

ObservationTable::~ObservationTable()
{
    delete ui;
}

void ObservationTable::levelUp(int nextLevel)
{
    QTableWidget* currentTable = tables.at(level);
    currentTable->hide();
    level = nextLevel-1;
    if (level < 4)
    {
        currentTable = tables.at(level);
        currentTable->show();
    }
}
