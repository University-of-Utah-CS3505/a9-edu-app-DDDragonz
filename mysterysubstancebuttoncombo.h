#ifndef MYSTERYSUBSTANCEBUTTONCOMBO_H
#define MYSTERYSUBSTANCEBUTTONCOMBO_H

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QGraphicsColorizeEffect>

namespace Ui {
class MysterySubstanceButtonCombo;
}

class MysterySubstanceButtonCombo : public QWidget
{
    Q_OBJECT

public:
    /// @brief Creates a MysterySubstanceButtonCombo. This should sit at the bottom of the view.
    /// @param number The number of chemicals already in the MysterySubstances. This informs what the name of the
    /// mystery substance is expected to be (ie: 0 = Substance A, 1 = Substance B, etc.)
    explicit MysterySubstanceButtonCombo(int number, QWidget *parent = nullptr);

    /// @brief Standard Deconstructor.
    ~MysterySubstanceButtonCombo();

private:
    Ui::MysterySubstanceButtonCombo *m_ui;
    QPixmap m_pixmap;   // The image to show
    QGraphicsColorizeEffect* m_effect;


public slots:
    /// @brief Receives information that the button was selected
    void buttonSelected();

    /// @brief Receives information that the mixing button was selected
    void mixingChemicals();


    /// @brief Receives information that the done mixing button was selected
    void doneMixingChemicals();

signals:
    /// @brief Informs the program that this substance was selected
    /// @param name The name of the substance
    void substanceSelected(QString name);

    /// @brief Informs the program that this substance was deselected
    /// @param name The name of the substance
    void substanceDeselected(QString name);

    /// @brief Informs the program that a substance was selected
    void mysterySubstanceSelected();

    /// @brief Informs the program that a substance was deselected
    void mysterySubstanceDeselected();
};

#endif // MYSTERYSUBSTANCEBUTTONCOMBO_H
