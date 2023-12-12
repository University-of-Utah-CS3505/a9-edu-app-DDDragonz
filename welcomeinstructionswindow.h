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
    /// @brief Standard Constructor
    explicit WelcomeInstructionsWindow(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor
    ~WelcomeInstructionsWindow();

private slots:
    /// @brief Close the window
    void on_pushButton_clicked();

private:
    Ui::WelcomeInstructionsWindow *m_ui;
};

#endif // WELCOMEINSTRUCTIONSWINDOW_H
