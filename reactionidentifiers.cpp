#include "reactionidentifiers.h"
#include "ui_reactionidentifiers.h"

ReactionIdentifiers::ReactionIdentifiers(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ReactionIdentifiers)
{
    m_ui->setupUi(this);
    m_ui->colorBox->addItem("Dark Brown");
    m_ui->colorBox->addItem("White");
    m_ui->colorBox->addItem("Grey");
    m_ui->colorBox->addItem("Light Yellow");
    m_ui->colorBox->addItem("Yellow");
    m_ui->submitButton->setEnabled(false);

    connect(m_ui->solidBox,
            &QCheckBox::toggled,
            m_ui->colorBox,
            &QComboBox::setEnabled);

    connect(m_ui->submitButton,
            &QPushButton::clicked,
            this,
            &ReactionIdentifiers::submitSelected);
}

ReactionIdentifiers::~ReactionIdentifiers()
{
    delete m_ui;
}

void ReactionIdentifiers::mixSelected()
{
    m_ui->submitButton->setEnabled(true);
}

void ReactionIdentifiers::doneMixingSelected()
{
    m_ui->submitButton->setEnabled(false);
}

void ReactionIdentifiers::submitSelected()
{
    QString identifiers;
    if (m_ui->bubblesBox->isChecked())
    {
        m_ui->bubblesBox->setChecked(false);
        identifiers.append("bubbles");
    }
    if (m_ui->noReactionBox->isChecked())
    {
        m_ui->noReactionBox->setChecked(false);
        if (identifiers.length() != 0)
        {
            identifiers.append(", ");
        }
        identifiers.append("no reaction");
    }
    if (m_ui->solidBox->isChecked())
    {
        m_ui->solidBox->setChecked(false);
        QString color = m_ui->colorBox->currentText();
        if (identifiers.length() != 0)
        {
            identifiers.append(", ");
        }
        identifiers.append(color);
        identifiers.append(" solid");
    }
    emit sendIdentifiers(identifiers);
}
