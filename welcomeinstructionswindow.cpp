#include "welcomeinstructionswindow.h"
#include "ui_welcomeinstructionswindow.h"

WelcomeInstructionsWindow::WelcomeInstructionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeInstructionsWindow)
{
    ui->setupUi(this);
}

WelcomeInstructionsWindow::~WelcomeInstructionsWindow()
{
    delete ui;
}

void WelcomeInstructionsWindow::on_pushButton_clicked()
{
    this->done(1);
}

