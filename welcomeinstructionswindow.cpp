#include "welcomeinstructionswindow.h"
#include "ui_welcomeinstructionswindow.h"

WelcomeInstructionsWindow::WelcomeInstructionsWindow(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::WelcomeInstructionsWindow)
{
    m_ui->setupUi(this);
}

WelcomeInstructionsWindow::~WelcomeInstructionsWindow()
{
    delete m_ui;
}

void WelcomeInstructionsWindow::on_pushButton_clicked()
{
    this->done(1);
}

