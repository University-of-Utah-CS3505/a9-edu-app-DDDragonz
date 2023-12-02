#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(vector<QString> chemicals, vector<QString> equations, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void showHelp();
};
#endif // MAINWINDOW_H
