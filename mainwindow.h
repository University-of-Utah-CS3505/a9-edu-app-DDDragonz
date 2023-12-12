#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chemistrylogicmodel.h"
#include "observationtable.h"
#include <QResizeEvent>

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Standard Constructor. Makes the connections
    /// @param logicModel The chemistry logic model
    MainWindow(ChemistryLogicModel& logicModel, QWidget *parent = nullptr);

    /// @brief Standard Deconstructor.
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
    ObservationTable* m_observationTable;

private slots:
    /// @brief Changes level to display to the current lone
    /// @param level The current level
    void updateLevelLabel(int level);

    /// @brief Display help window
    void showHelp();

    /// @brief Display observation table window
    void showObservationTable();

    /// @brief Display box saying the submitted response was incorrect
    void wrongAnswerReminder();

    /// @brief Display box saying game complete
    void gameComplete();
};
#endif // MAINWINDOW_H
