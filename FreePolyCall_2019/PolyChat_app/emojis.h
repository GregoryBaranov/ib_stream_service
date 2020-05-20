#ifndef EMOJIS_H
#define EMOJIS_H

#include <QString>
#include "list"

class Emojis
{
public:
    Emojis();
    std::list<QString> getEmoji();
};

#endif // EMOJIS_H
