#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>

namespace Ui {
class Level;
}

class Level : public QWidget
{
    Q_OBJECT

public:
    explicit Level(QWidget *parent = nullptr);
    ~Level();

private:
    Ui::Level *ui;

signals:
    void nextLevel();
    void sendLevel(int level);

public slots:
    void getLevel(int level);
    void getToNextLevel();
    void getLevelUp();
};

#endif // LEVEL_H
