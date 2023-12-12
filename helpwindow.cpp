#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::HelpWindow)
{
    m_ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
    delete m_ui;
}
