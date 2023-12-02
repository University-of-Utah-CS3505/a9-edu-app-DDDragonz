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
    void addLevels();

private:
    map<vector<QString>, vector<Chemical>> m_reactions;
    void addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products);
    void addLevelOne();
    void addLevelTwo();
    void addLevelThree();
    void addLevelFour();
};

#endif // REACTIONS_H
