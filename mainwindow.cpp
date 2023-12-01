#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chemistrylogicmodel.h"
#include "level.h"
#include "identifychemicals.h"
#include <QString>

using std::vector;

MainWindow::MainWindow(ChemistryLogicModel& logicModel, vector<QString> chemicals, vector<QString> equations, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->levelWidget, &Level::nextLevel, &logicModel, &ChemistryLogicModel::levelUp);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, ui->levelWidget, &Level::getLevel);
    ui->possibleElementsWidget->addElements(chemicals);
    ui->significantReactionsWidget->addEquations(equations);
    ui->vialButtonsWidget->addMysterySubstances(chemicals.size());
}

MainWindow::~MainWindow()
{
    delete ui;
}
