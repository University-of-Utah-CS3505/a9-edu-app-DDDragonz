#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chemistrylogicmodel.h"

MainWindow::MainWindow(ChemistryLogicModel& logicModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->levelWidget, &Level::nextLevel, &logicModel, &ChemistryLogicModel::levelUp);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, ui->levelWidget, &Level::getLevel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

