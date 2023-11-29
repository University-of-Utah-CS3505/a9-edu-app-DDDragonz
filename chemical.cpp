#include "chemical.h"

Chemical::Chemical(QString cName, QString formula, QString sName, double pH, QString note, QString state)
{
    m_commonName = cName;
    m_formula = formula;
    m_systematicName = sName;
    m_pH = pH;
    m_note = note;
    m_state = state;
}

Chemical::Chemical(const Chemical& other)
{
    m_commonName = other.m_commonName;
    m_formula = other.m_formula;
    m_systematicName = other.m_systematicName;
    m_pH = other.m_pH;
    m_note = other.m_note;
    m_state = other.m_state;
}

Chemical& Chemical::operator=(const Chemical& other)
{
    m_commonName = other.m_commonName;
    m_formula = other.m_formula;
    m_systematicName = other.m_systematicName;
    m_pH = other.m_pH;
    m_note = other.m_note;
    m_state = other.m_state;
    return *this;
}

QString Chemical::getCommonName()
{
    return m_commonName;
}

QString Chemical::getFormula()
{
    return m_formula;
}

QString Chemical::getSystematicName()
{
    return m_systematicName;
}

double Chemical::getPH()
{
    return m_pH;
}

QString Chemical::getNote()
{
    return m_note;
}

QString Chemical::getState()
{
    return m_state;
}

void Chemical::addReaction(QString chemical, QList<Chemical> products)
{
    m_reactions[chemical] = products;
}

QList<Chemical> Chemical::getReactions(QString chemical)
{
    QList<Chemical> products;
    if (m_reactions.contains(chemical))
    {
        products = m_reactions[chemical];
    }
    return products;
}
