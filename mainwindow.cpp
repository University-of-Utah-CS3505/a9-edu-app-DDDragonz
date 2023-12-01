#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "identifychemicals.h"
#include <QString>

using std::vector;

MainWindow::MainWindow(vector<QString> chemicals, vector<QString> equations, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->possibleElementsWidget->addElements(chemicals);
    ui->significantReactionsWidget->addEquations(equations);
}

MainWindow::~MainWindow()
{
    delete ui;
}
