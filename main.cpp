#include "mainwindow.h"

#include <QApplication>

using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString chemicalsOrdered[] {"FeCl3", "NaCO3", "HCl"};
    vector<QString> chemicals;
    for(int i = 0; i < 3; i++)
    {
        chemicals.push_back(chemicalsOrdered[i]);
    }

    vector<QString> equations;
    equations.push_back("FeCl<sub>3</sub>(aq) + Na<sub>2</sub>CO<sub>3</sub>(aq) -> NaCl(aq) + FeO(s) + CO<sub>2</sub>(g)<br/>Note: The solid that results is dark brown.");
    equations.push_back("Na<sub>2</sub>CO<sub>3</sub>(aq) + HCl(aq) -> NaCl(aq) + H<sub>2</sub>O + CO<sub>2</sub>(g)");
    equations.push_back("FeCl<sub>3</sub>(aq) + HCl(aq) -> FeCl<sub>3</sub>(aq) + HCl(aq)");

    MainWindow w(chemicals, equations);
    w.show();
    return a.exec();
}
