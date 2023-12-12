#ifndef MIXINGCHEMICAL_H
#define MIXINGCHEMICAL_H
#include <QColor>

class MixingChemical
{
public:
    /// @brief Standard Constructor. If no params are entered set defaults
    MixingChemical(int id = 0, QColor color = Qt::green, bool touching = false);
    int s_id;
    QColor s_color;
    bool s_touch;
};

#endif // MIXINGCHEMICAL_H
