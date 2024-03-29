#include "observationtable.h"
#include "ui_observationtable.h"

ObservationTable::ObservationTable(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ObservationTable)
{
    m_ui->setupUi(this);
    m_tables.append(m_ui->levelOneTable);
    m_tables.append(m_ui->levelTwoTable);
    m_tables.append(m_ui->levelThreeTable);
    m_tables.append(m_ui->levelFourTable);
    
    m_ui->levelTwoTable->hide();
    m_ui->levelThreeTable->hide();
    m_ui->levelFourTable->hide();

    m_level = 1;

    setWindowFlags(Qt::WindowStaysOnTopHint);
}

ObservationTable::~ObservationTable()
{
    delete m_ui;
}

void ObservationTable::levelUp(int nextLevel)
{
    QTableWidget* currentTable = m_tables.at(m_level);
    currentTable->hide();
    m_level = nextLevel-1;
    if (m_level < 4)
    {
        currentTable = m_tables.at(m_level);
        currentTable->show();
    }
}

void ObservationTable::receiveIdentifiers(QString substance1, QString substance2, QString identifiers)
{
    QTableWidget* currentTable = m_tables.at(m_level);
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
