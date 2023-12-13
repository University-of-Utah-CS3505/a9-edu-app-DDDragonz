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
    ~MysterySubstanceButtonCombo();

private:
    Ui::MysterySubstanceButtonCombo *ui;
    QPixmap m_pixmap;   // The image to show
    QGraphicsColorizeEffect* m_effect;


public slots:
    void buttonSelected();
    void mixingChemicals();
    void doneMixingChemicals();

signals:
    void substanceSelected(QString name);
    void substanceDeselected(QString name);
    void mysterySubstanceSelected();
    void mysterySubstanceDeselected();
};

#endif // MYSTERYSUBSTANCEBUTTONCOMBO_H
