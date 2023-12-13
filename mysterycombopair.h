#ifndef MYSTERYCOMBOPAIR_H
#define MYSTERYCOMBOPAIR_H

#include <QWidget>
#include <QString>

using std::vector;

namespace Ui {
class MysteryComboPair;
}

class MysteryComboPair : public QWidget
{
    Q_OBJECT

public:
    /// @brief Creates an empty MysteryComboPair
    /// @param parent The parent of the Qt object
    explicit MysteryComboPair(QWidget *parent = nullptr);

    /// @brief Creates a MysteryComboPair, with the given index, mystery name, chemical options, and parent
    /// @param index The index of the pair within the identify chemicals
    /// @param mystery The name of the mystery to display
    /// @param chemicals The chemicals to add as initial options
    /// @param parent The parent of the Qt object
    MysteryComboPair(int index, QString mystery, vector<QString> chemicals, QWidget *parent = nullptr);

    /// @brief Adds an option to select
    /// @param name The name of the new option
    /// @param index The new index of the pair
    void addComboItem(QString name, int index);
    ~MysteryComboPair();

private:
    Ui::MysteryComboPair *ui;
    int m_index;    // The index of the pair within the identify chemicals

signals:
    /// @brief Informs the program that a different choice was made of which chemical is selected
    /// @param chemical The name of the chemical that's been selected
    /// @param index The index of the pair within the identify chemicals
    void choiceChange(QString chemical, int index);

public slots:
    /// @brief Receives information that the selected item within the combo box has changed
    /// @param chemical The name of the chemical that's been selected in the combo box
    void comboChange(QString chemical);
};

#endif // MYSTERYCOMBOPAIR_H
