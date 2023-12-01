#include "chemical.h"

Chemical::Chemical(QString formula, State state, QColor color)
{
    m_formula = formula;
    m_state = state;
    m_colorOfSolid = color;
}

Chemical::Chemical(const Chemical& other)
{
    m_formula = other.m_formula;
    m_state = other.m_state;
    m_colorOfSolid = other.m_colorOfSolid;
}

Chemical& Chemical::operator=(const Chemical& other)
{
    m_formula = other.m_formula;
    m_state = other.m_state;
    m_colorOfSolid = other.m_colorOfSolid;
    return *this;
}

QString Chemical::getFormula()
{
    return m_formula;
}

State Chemical::getState()
{
    return m_state;
}

QColor Chemical::getColorOfSolid()
{
    return m_colorOfSolid;
}
