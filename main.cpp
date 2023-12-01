#include "mainwindow.h"

#include <QApplication>
#include "chemistrylogicmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChemistryLogicModel logicModel;
    MainWindow w(logicModel);
    w.show();
    return a.exec();
}
