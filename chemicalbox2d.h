#ifndef CHEMICALBOX2D_H
#define CHEMICALBOX2D_H
#include <QColor>

class chemicalBox2D
{
public:
    chemicalBox2D(int id = 0, QColor color = Qt::green, bool touching = false);
    int s_id;
    QColor s_color;
    bool s_touch;
};

#endif // CHEMICALBOX2D_H
