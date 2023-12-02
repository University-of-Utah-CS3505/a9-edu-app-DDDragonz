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
    void addReaction(Chemical reactantA, Chemical reactantB, vector<Chemical> products);
    QString getAllReactions() const;

private:
    map<vector<QString>, vector<Chemical>> m_reactions;
};

#endif // REACTIONS_H
