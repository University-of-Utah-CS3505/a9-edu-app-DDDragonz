#include "mainwindow.h"

#include <QApplication>
#include "chemistrylogicmodel.h"
#include "welcomeinstructionswindow.h"

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChemistryLogicModel logicModel;
    MainWindow w(logicModel);
    w.show();

    WelcomeInstructionsWindow startWindow;
    startWindow.show();

    return a.exec();
}
