#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstancebuttoncombo.h"
#include <QPixmap>
#include <QImage>
#include <QGraphicsColorizeEffect>


MysterySubstanceButtonCombo::MysterySubstanceButtonCombo(int number, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysterySubstanceButtonCombo),
    m_pixmap(":/images/vial.png")
{
    ui->setupUi(this);
    char character = 'A' + number;
    QString textString = "Substance ";
    textString += character;
    ui->label->setText(textString);
    ui->selectButton->setText(textString);

    //Create image
    int scaleFactor = 6;
    m_effect = new QGraphicsColorizeEffect();
    m_pixmap = m_pixmap.scaled(ui->label->size() * scaleFactor, Qt::KeepAspectRatio);
    ui->label->setPixmap(m_pixmap);

    connect(ui->selectButton,
            &QPushButton::clicked,
            this,
            &MysterySubstanceButtonCombo::buttonSelected);
}

MysterySubstanceButtonCombo::~MysterySubstanceButtonCombo()
{
    delete ui;
}

void MysterySubstanceButtonCombo::buttonSelected()
{
    if(ui->selectButton->isChecked())
    {
        m_effect->setColor(QColor(0, 0, 255));
        ui->label->setGraphicsEffect(m_effect);
        ui->label->setPixmap(m_pixmap);
        emit substanceSelected(ui->selectButton->text());
        emit mysterySubstanceSelected();
    }
    else
    {
        m_effect->setColor(QColor(169, 169, 169));
        ui->label->setGraphicsEffect(m_effect);
        ui->label->setPixmap(m_pixmap);
        emit substanceDeselected(ui->selectButton->text());
        emit mysterySubstanceDeselected();
    }
}

void MysterySubstanceButtonCombo::mixingChemicals()
{
    ui->selectButton->setChecked(false);
    ui->selectButton->setEnabled(false);
}

void MysterySubstanceButtonCombo::doneMixingChemicals()
{
    m_effect->setColor(QColor(169, 169, 169));
    ui->label->setGraphicsEffect(m_effect);
    ui->label->setPixmap(m_pixmap);
    ui->selectButton->setChecked(false);
    ui->selectButton->setEnabled(true);
}
