#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newHeight(float value);

public slots:
    void updateWorld();

private:
    Ui::MainWindow *ui;
    b2World world;
    b2Body *body;
    QTimer *timer;
};
#endif // MAINWINDOW_H
