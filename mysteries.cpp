#include "mysteries.h"
#include <vector>
#include <QString>

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
    for(int i = 0; i < m_size; i++)
    {
        int random = rand()*m_size;
        QString temp = m_substances[i];
        m_substances[i] = m_substances[random];
        m_substances[random] = temp;
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
