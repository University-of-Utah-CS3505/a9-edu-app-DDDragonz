#include "mainwindow.h"
#include "reactions.h"

#include <QApplication>
#include "chemistrylogicmodel.h"

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Reactions reactions;
    reactions.addLevels();

    ChemistryLogicModel logicModel;
    MainWindow w(logicModel);

    w.show();
    return a.exec();
}
