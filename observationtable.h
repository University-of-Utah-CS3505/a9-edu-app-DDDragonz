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
    /// @brief Standard Constructor. Creates level tables
    explicit ObservationTable(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor.
    ~ObservationTable();

private:
    Ui::ObservationTable *m_ui;
    QList<QTableWidget*> m_tables;
    int m_level;

public slots:

    /// @brief Advances everything to the next level
    /// @param level The level to go to
    void levelUp(int level);

    /// @brief Updates the table to have the recorded observations
    /// @param substance1 One of the mystery chemicals selected
    /// @param substance2 The other mystery chemical selected
    /// @param identifiers The recorded observations
    void receiveIdentifiers(QString substance1, QString substance2, QString identifiers);
};

#endif // OBSERVATIONTABLE_H
