#ifndef MYSTERYCOMBOPAIR_H
#define MYSTERYCOMBOPAIR_H

#include <QWidget>
#include <QString>

using std::vector;

namespace Ui {
class MysteryComboPair;
}

class MysteryComboPair : public QWidget
{
    Q_OBJECT

public:
    explicit MysteryComboPair(QWidget *parent = nullptr);
    MysteryComboPair(QString mystery, vector<QString> chemicals, QWidget *parent = nullptr);
    ~MysteryComboPair();

private:
    Ui::MysteryComboPair *ui;
};

#endif // MYSTERYCOMBOPAIR_H
