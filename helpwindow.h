#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QWidget
{
    Q_OBJECT

public:
    /// @brief Standard Constructor
    explicit HelpWindow(QWidget *parent = nullptr);

    /// @brief Standard Deconstructor
    ~HelpWindow();

private:
    Ui::HelpWindow *m_ui;
};

#endif // HELPWINDOW_H
