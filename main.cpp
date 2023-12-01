#include "mainwindow.h"

#include <QApplication>

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString chemicalsOrdered[] {"Na3PO4", "Na2CO3", "NaOH"};

    // randomize chemicals ordered

    vector<QString> chemicals;
    for(int i = 0; i < 3; i++)
    {
        chemicals.push_back(chemicalsOrdered[i]);
    }

    vector<QString> equations;
    equations.push_back("This is an equation");
    equations.push_back("This is another equation");
    equations.push_back("Oh yeah. It's all coming together.");

    MainWindow w(chemicals, equations);
    w.show();
    return a.exec();
}
