#include "mainwindow.h"
#include "mixingmodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    MixingModel w;
    w.show();
    return a.exec();
}
