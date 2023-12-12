#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chemistrylogicmodel.h"
#include "identifychemicals.h"
#include "helpwindow.h"
#include "observationtable.h"
#include <QString>
#include <QMessageBox>

using std::vector;

MainWindow::MainWindow(ChemistryLogicModel& logicModel, QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->vialButtonsWidget->addMysterySubstances(logicModel.getAllReactants().size());

    m_observationTable = new ObservationTable();
    connect(m_ui->possibleElementsWidget, &IdentifyChemicals::submitToNextLevel, &logicModel, &ChemistryLogicModel::levelUp);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, this, &MainWindow::updateLevelLabel);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactionsFormula, m_ui->significantReactionsWidget, &ChemicalEquations::receiveFormula);
    connect(&logicModel, &ChemistryLogicModel::sendAllReactants, m_ui->possibleElementsWidget, &IdentifyChemicals::addElements);
    connect(&logicModel, &ChemistryLogicModel::sendReactant, m_ui->possibleElementsWidget, &IdentifyChemicals::addElement);
    connect(&logicModel, &ChemistryLogicModel::addReactants, m_ui->vialButtonsWidget, &MysterySubstances::addMysterySubstances);
    connect(m_ui->pushButton, &QPushButton::clicked, this, &MainWindow::showHelp);
    connect(m_ui->viewTableButton, &QPushButton::clicked, this, &MainWindow::showObservationTable);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, m_observationTable, &ObservationTable::levelUp);
    connect(&logicModel, &ChemistryLogicModel::levelKeep, this, &MainWindow::wrongAnswerReminder);
    connect(m_ui->vialButtonsWidget, &MysterySubstances::mixingChemicals, &logicModel, &ChemistryLogicModel::chemicalsMixed);
    connect(m_ui->vialButtonsWidget, &MysterySubstances::mixChemicals, m_ui->reactionIdentifiersWidget, &ReactionIdentifiers::mixSelected);
    connect(m_ui->vialButtonsWidget, &MysterySubstances::doneMixing, m_ui->reactionIdentifiersWidget, &ReactionIdentifiers::doneMixingSelected);
    connect(m_ui->reactionIdentifiersWidget, &ReactionIdentifiers::sendIdentifiers, &logicModel, &ChemistryLogicModel::receiveIdentifiers);
    connect(&logicModel, &ChemistryLogicModel::sendReactionIdentifiers, m_observationTable, &ObservationTable::receiveIdentifiers);
    connect(&logicModel, &ChemistryLogicModel::sendLevel, m_ui->vialButtonsWidget, &MysterySubstances::levelUp);
    connect(&logicModel, &ChemistryLogicModel::gameComplete, this, &MainWindow::gameComplete);
    connect(m_ui->possibleElementsWidget, &IdentifyChemicals::submitToNextLevel, m_ui->vialButtonsWidget, &MysterySubstances::doneButtonClicked);
    connect(m_ui->vialButtonsWidget, &MysterySubstances::doneMixing, m_ui->mixingWidget, &MixingModel::eraseScene);
    connect(&logicModel, &ChemistryLogicModel::sendChemicalMixResult, m_ui->mixingWidget, &MixingModel::createScene);
    connect(m_ui->possibleElementsWidget, &IdentifyChemicals::clearWorld, m_ui->mixingWidget, &MixingModel::eraseScene);
    connect(m_ui->mixingWidget, &MixingModel::resetScene, m_ui->vialButtonsWidget, &MysterySubstances::doneButtonClicked);
    connect(m_ui->mixingWidget, &MixingModel::resetScene, m_ui->vialButtonsWidget, &MysterySubstances::updateMixButton);

    m_ui->mixingWidget->setFocusPolicy(Qt::StrongFocus);
    logicModel.levelUp(vector<QString>());
}

void MainWindow::updateLevelLabel(int level)
{
    QString levelText = "Level " + QString::number(level);
    m_ui->levelLabel->setText(levelText);
}

MainWindow::~MainWindow()
{
    delete m_ui;
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
    m_observationTable->show();
}

void MainWindow::gameComplete()
{
    QMessageBox::information(this, "Game Complete", "Congratulation! You have completed all the tasks!", "OK");
    this->close();
}

