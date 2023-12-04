#include "mainwindow.h"
#include "reactions.h"
#include "mixingmodel.h"

#include <QApplication>
#include "chemistrylogicmodel.h"

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChemistryLogicModel logicModel;
    MixingModel mixingModel;
    MainWindow w(logicModel, mixingModel);

    w.show();
    return a.exec();
}
