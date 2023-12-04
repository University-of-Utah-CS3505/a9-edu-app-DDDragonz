#ifndef CHEMICAL_H
#define CHEMICAL_H
#include <QColor>


class Chemical
{
public:
    Chemical(int id = 0, QColor color = Qt::green, bool touching = false);
    int s_id;
    QColor s_color;
    bool s_touch;

};

#endif // CHEMICAL_H
