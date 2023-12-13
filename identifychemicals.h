#ifndef IDENTIFYCHEMICALS_H
#define IDENTIFYCHEMICALS_H

#include <QWidget>
#include "mysterycombopair.h"
#include "mysteries.h"

using std::vector;
using std::map;

namespace Ui {
class IdentifyChemicals;
}

class IdentifyChemicals : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor for IdentifyChemicals
    /// @param parent The parent for the Qt object
    IdentifyChemicals(QWidget *parent = nullptr);
    ~IdentifyChemicals();

private:
    Ui::IdentifyChemicals *ui;
    vector<MysteryComboPair*> m_comboPairs; // Keeps track of the combo pairs, so added chemicals can be added
    vector<QString> m_prevChemicals;    // Keeps track of the names of previously added chemicals
    int m_numberOfSubstances;
    QString m_choices[6];
    QString m_firstChoice;  // Keeps track of the first choice
    int m_choicesSize;  // May not always be filled - m_numberOfSubstances is the size

signals:
    /// @brief Informs the program that choices were made, and the user would like to move to the next level
    /// @param choices The choices selected, in order
    void submitToNextLevel(vector<QString> choices);

    /// @brief Informs the program that the world needs to be cleared
    void clearWorld();

public slots:
    /// @brief Receives the information that the submit button was clicked
    void submitClick();

    /// @brief Receives the information that one or more chemicals needs to be added
    /// @param chemicals The chemicals that need to be added
    void addElements(vector<QString> chemicals);

    /// @brief Receives the information that one chemical needs to be added
    /// @param chemical The chemical that needs to be added
    void addElement(QString chemical);

    /// @brief Receives the information that one of the choices changed
    /// @param chemical The chemical that was selected
    /// @param index The index of the selected chemical
    void choiceChange(QString chemical, int index);
};

#endif // IDENTIFYCHEMICALS_H
