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
    MysteryComboPair(int index, QString mystery, vector<QString> chemicals, QWidget *parent = nullptr);
    void addComboItem(QString name, int index);
    ~MysteryComboPair();

private:
    Ui::MysteryComboPair *ui;
    int m_index;

signals:
    void choiceChange(QString chemical, int index);

public slots:
    void comboChange(QString chemical);
};

#endif // MYSTERYCOMBOPAIR_H
