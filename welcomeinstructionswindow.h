#ifndef WELCOMEINSTRUCTIONSWINDOW_H
#define WELCOMEINSTRUCTIONSWINDOW_H

#include <QDialog>

namespace Ui {
class WelcomeInstructionsWindow;
}

class WelcomeInstructionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeInstructionsWindow(QWidget *parent = nullptr);
    ~WelcomeInstructionsWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WelcomeInstructionsWindow *ui;
};

#endif // WELCOMEINSTRUCTIONSWINDOW_H
