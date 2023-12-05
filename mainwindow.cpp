#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chemistrylogicmodel.h"
#include "identifychemicals.h"
#include "helpwindow.h"
#include "observationtable.h"
#include "mixingmodel.h"
#include <QString>
#include <QMessageBox>

using std::vector;

MainWindow::MainWindow(ChemistryLogicModel& logicModel, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->vialButtonsWidget->addMysterySubstances(logicModel.getAllReactants().size());

    observationTable = new ObservationTable();

    connect(ui->possibleElementsWidget, &IdentifyChemicals::submitToNextLevel, &logicModel, &ChemistryLogicModel::levelUp);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, this, &MainWindow::updateLevelLabel);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactionsFormula, ui->significantReactionsWidget, &ChemicalEquations::receiveFormula);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactants, ui->possibleElementsWidget, &IdentifyChemicals::addElements);
    connect(&logicModel, &ChemistryLogicModel::sendReactant, ui->possibleElementsWidget, &IdentifyChemicals::addElement);
    connect(&logicModel, &ChemistryLogicModel::addReactants, ui->vialButtonsWidget, &MysterySubstances::addMysterySubstances);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::showHelp);
    connect(ui->viewTableButton, &QPushButton::clicked, this, &MainWindow::showObservationTable);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, observationTable, &ObservationTable::levelUp);
    connect(&logicModel, &ChemistryLogicModel::levelKeep, this, &MainWindow::wrongAnswerReminder);
    connect(ui->vialButtonsWidget, &MysterySubstances::mixingChemicals, &logicModel, &ChemistryLogicModel::chemicalsMixed);
    connect(ui->vialButtonsWidget, &MysterySubstances::mixChemicals, ui->reactionIdentifiersWidget, &ReactionIdentifiers::mixSelected);
    connect(ui->vialButtonsWidget, &MysterySubstances::doneMixing, ui->reactionIdentifiersWidget, &ReactionIdentifiers::doneMixingSelected);
    connect(ui->reactionIdentifiersWidget, &ReactionIdentifiers::sendIdentifiers, &logicModel, &ChemistryLogicModel::receiveIdentifiers);
    connect(&logicModel, &ChemistryLogicModel::sendReactionIdentifiers, observationTable, &ObservationTable::receiveIdentifiers);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, ui->vialButtonsWidget, &MysterySubstances::levelUp);

    connect(ui->vialButtonsWidget, &MysterySubstances::doneMixing, ui->mixingWidget, &MixingModel::eraseScene);
    connect(ui->vialButtonsWidget, &MysterySubstances::mixChemicals, ui->mixingWidget, &MixingModel::createScene);
    connect(&logicModel, &ChemistryLogicModel::sendChemicalMixResult, ui->mixingWidget, &MixingModel::createScene2);
    ui->mixingWidget->setFocusPolicy(Qt::StrongFocus);
    logicModel.levelUp(vector<QString>());

}


void MainWindow::resizeEvent(QResizeEvent* event)
{
    qDebug() << "resized";
}

void MainWindow::updateLevelLabel(int level)
{
    QString levelText = "Level " + QString::number(level);
    ui->levelLabel->setText(levelText);
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

void MainWindow::wrongAnswerReminder()
{
    QMessageBox::information(this, "Wrong Answer", "At least one of the answer is false, please try again.", "OK");
}

void MainWindow::showObservationTable()
{
    observationTable->show();
}
