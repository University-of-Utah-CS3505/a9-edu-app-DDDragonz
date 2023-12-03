
#include "mixingmodel.h"
#include "mw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MixingModel w;
    MW w;
    w.show();
    return a.exec();
}
