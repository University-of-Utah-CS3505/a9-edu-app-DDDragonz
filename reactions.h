#ifndef REACTIONS_H
#define REACTIONS_H

#include "chemical.h"
#include "reaction.h"

using std::map;
using std::vector;

class Reactions
{
public:
    Reactions();
    Reaction getReaction(Chemical reactantA, Chemical reactantB);
    QString getAllReactions() const;
    void addLevelOne();
    void addLevelTwo();
    void addLevelThree();
    void addLevelFour();

private:
    map<vector<QString>, vector<Chemical>> m_reactantsAndProducts;
    vector<QString> m_equations;
    void addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products);
    QString getStateString(State state) const;
    QString getColorString(QColor color) const;
};

#endif // REACTIONS_H
