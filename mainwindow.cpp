#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chemistrylogicmodel.h"
#include "identifychemicals.h"
#include "helpwindow.h"
#include <QString>

using std::vector;

MainWindow::MainWindow(ChemistryLogicModel& logicModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->vialButtonsWidget->addMysterySubstances(logicModel.getAllReactants().size());

    int level = logicModel.getLevel();
    QString levelText = "Level " + QString::number(level);
    ui->levelLabel->setText(levelText);


    connect(ui->possibleElementsWidget, &IdentifyChemicals::submitToNextLevel, &logicModel, &ChemistryLogicModel::levelUp);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, this, &MainWindow::updateLevelLabel);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::helpClicked);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactionsFormula, ui->significantReactionsWidget, &ChemicalEquations::receiveFormula);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactants, ui->possibleElementsWidget, &IdentifyChemicals::addElements);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::showHelp);

}

void MainWindow::updateLevelLabel(int level)
{
    QString levelText = "Level " + QString::number(level);
    ui->levelLabel->setText(levelText);
}

void MainWindow::helpClicked()
{
    HelpWindow* help = new HelpWindow();
    help->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showHelp()
{
    HelpWindow* help = new HelpWindow();
    help->show();
}
