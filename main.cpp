#include "mixingmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MixingModel w;
    //MainWindow w;
    w.show();
    return a.exec();
}
