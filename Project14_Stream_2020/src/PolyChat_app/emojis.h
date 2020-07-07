#ifndef EMOJIS_H
#define EMOJIS_H

#include <QString>

class Emojis
{
public:
    QStringList getEmoji();
    static Emojis *instance();
private:
    Emojis();
};

#endif // EMOJIS_H
