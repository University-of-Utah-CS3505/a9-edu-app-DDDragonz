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

void ObservationTable::receiveIdentifiers(QString substance1, QString substance2, QString identifiers)
{
    QTableWidget* currentTable = tables.at(level);
    QTableWidgetItem* text = new QTableWidgetItem{identifiers};
    int sub1 = substance1.at(10).toLatin1() - 'A';
    int sub2 = substance2.at(10).toLatin1() - 'A';
    int index1;
    int index2;
    int numOfColumns = currentTable->columnCount();
    if (sub1 > sub2)
    {
        index1 = sub2;
        index2 = numOfColumns - sub1;
    } else
    {
        index1 = sub1;
        index2 = numOfColumns - sub2;
    }
    currentTable->setItem(index1,index2, text);
    currentTable->resizeColumnsToContents();
}
