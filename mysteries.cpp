#include "mysteries.h"
#include <vector>
#include <QString>
#include <QDebug>

using std::vector;

Mysteries::Mysteries(vector<QString> chemicals)
{
    m_size = (int)chemicals.size();
    for(int i = 0; i < (int)chemicals.size(); i++)
    {
        m_substances[i] = chemicals.at(i);
    }
    shuffle();
}

void Mysteries::shuffle()
{
    srand(time(0));
    for(int i = 0; i < m_size; i++)
    {
        int random = rand()%m_size;
        QString temp = m_substances[i];
        m_substances[i] = m_substances[random];
        m_substances[random] = temp;
    }

    for(int i = 0; i < m_size; i++)
    {
        qDebug() << "Correct Answer " << i << ": " << m_substances[i];
    }
}

bool Mysteries::checkSubstances(QString substances[])
{
    if(substances->size() != m_size)
    {
        return false;
    }
    for(int i = 0; i < m_size; i++)
    {
        if(substances[i] != m_substances[i])
            return false;
    }

    return true;
}

void Mysteries::addChemical(QString chemical)
{
    m_substances[m_size++] = chemical;
    shuffle();
}

bool Mysteries::checkChemicals(vector<QString> toCheck)
{
    if((int)toCheck.size() != m_size)
    {
        return false;
    }

    for(int i = 0; i < m_size; i++)
    {
        if(toCheck.at(i) != m_substances[i])
        {
            return false;
        }
    }
    return true;
}

QString Mysteries::getChemical(QString mysteryName)
{
    QChar letter = mysteryName.at(mysteryName.size()-1);
    int number = (int)letter.unicode();
    number -= 'A';
    return getChemical(number);
}

QString Mysteries::getChemical(int number)
{
    return m_substances[number];
}
