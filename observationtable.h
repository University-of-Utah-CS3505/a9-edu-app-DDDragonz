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
    void receiveIdentifiers(QString substance1, QString substance2, QString identifiers);
};

#endif // OBSERVATIONTABLE_H
