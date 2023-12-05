#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chemistrylogicmodel.h"
#include "observationtable.h"
#include "mixingmodel.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ChemistryLogicModel& logicModel, QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent* event) override;

    //send updated window size

private:
    Ui::MainWindow *ui;
    ObservationTable* observationTable;

private slots:
    void updateLevelLabel(int level);
    void showHelp();
    void showObservationTable();
    void wrongAnswerReminder();

};
#endif // MAINWINDOW_H
