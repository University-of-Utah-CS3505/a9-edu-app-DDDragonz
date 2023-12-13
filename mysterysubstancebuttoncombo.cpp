#include "mysterysubstancebuttoncombo.h"
#include "ui_mysterysubstancebuttoncombo.h"
#include <QPixmap>
#include <QImage>
#include <QGraphicsColorizeEffect>


MysterySubstanceButtonCombo::MysterySubstanceButtonCombo(int number, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MysterySubstanceButtonCombo),
    m_pixmap(":/images/vial.png")
{
    m_ui->setupUi(this);
    char character = 'A' + number;
    QString textString = "Substance ";
    textString += character;
    m_ui->label->setText(textString);
    m_ui->selectButton->setText(textString);

    //Create image
    int scaleFactor = 6;
    m_effect = new QGraphicsColorizeEffect();
    m_pixmap = m_pixmap.scaled(m_ui->label->size() * scaleFactor, Qt::KeepAspectRatio);
    m_ui->label->setPixmap(m_pixmap);

    connect(m_ui->selectButton,
            &QPushButton::clicked,
            this,
            &MysterySubstanceButtonCombo::buttonSelected);
}

MysterySubstanceButtonCombo::~MysterySubstanceButtonCombo()
{
    delete m_ui;
}

void MysterySubstanceButtonCombo::buttonSelected()
{
    if(m_ui->selectButton->isChecked())
    {
        m_effect->setColor(QColor(0, 0, 255));
        m_ui->label->setGraphicsEffect(m_effect);
        m_ui->label->setPixmap(m_pixmap);
        emit substanceSelected(m_ui->selectButton->text());
        emit mysterySubstanceSelected();
    }
    else
    {
        m_effect->setColor(QColor(169, 169, 169));
        m_ui->label->setGraphicsEffect(m_effect);
        m_ui->label->setPixmap(m_pixmap);
        emit substanceDeselected(m_ui->selectButton->text());
        emit mysterySubstanceDeselected();
    }
}

void MysterySubstanceButtonCombo::mixingChemicals()
{
    m_ui->selectButton->setChecked(false);
    m_ui->selectButton->setEnabled(false);
}

void MysterySubstanceButtonCombo::doneMixingChemicals()
{
    m_effect->setColor(QColor(169, 169, 169));
    m_ui->label->setGraphicsEffect(m_effect);
    m_ui->label->setPixmap(m_pixmap);
    m_ui->selectButton->setChecked(false);
    m_ui->selectButton->setEnabled(true);
}
