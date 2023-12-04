#include "chemical.h"
#include <QColor>

Chemical::Chemical(int id, QColor color, bool touching)
    : s_id(id),
      s_color(color),
      s_touch(touching)
{

}
