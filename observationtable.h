#ifndef OBSERVATIONTABLE_H
#define OBSERVATIONTABLE_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class ObservationTable;
}

class ObservationTable : public QWidget
{
    Q_OBJECT

public:
    explicit ObservationTable(QWidget *parent = nullptr);
    ~ObservationTable();

private:
    Ui::ObservationTable *ui;
    QList<QTableWidget*> tables;
    int level;

public slots:
    void levelUp(int level);
};

#endif // OBSERVATIONTABLE_H
