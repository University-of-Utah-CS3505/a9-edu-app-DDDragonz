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
    explicit MysterySubstanceButtonCombo(int number, QWidget *parent = nullptr);
    ~MysterySubstanceButtonCombo();

private:
    Ui::MysterySubstanceButtonCombo *ui;
    QPixmap m_pixmap;
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
