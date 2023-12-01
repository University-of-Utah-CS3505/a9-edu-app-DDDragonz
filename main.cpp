#include "mainwindow.h"

#include <QApplication>

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    vector<QString> chemicals;
    chemicals.push_back("Na3PO4");
    chemicals.push_back("Na2CO3");
    chemicals.push_back("NaOH");

    MainWindow w(chemicals);
    w.show();
    return a.exec();
}
