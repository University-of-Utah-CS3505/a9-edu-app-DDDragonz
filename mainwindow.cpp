#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identifychemicals.h"
#include "helpwindow.h"
#include <QString>

using std::vector;

MainWindow::MainWindow(vector<QString> chemicals, vector<QString> equations, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->possibleElementsWidget->addElements(chemicals);
    ui->significantReactionsWidget->addEquations(equations);
    ui->vialButtonsWidget->addMysterySubstances(chemicals.size());

    connect(ui->pushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::showHelp);
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
