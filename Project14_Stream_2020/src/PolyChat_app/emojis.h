#ifndef EMOJIS_H
#define EMOJIS_H

#include <QString>

class Emojis
{
public:

    enum TYPE_EMOJI
    {
        ALL,
        SMILEY,
        GESTURES,
        PEOPLE,
        CLOTHING
    };

    QStringList getEmoji(TYPE_EMOJI TYPE);
    static Emojis *instance();
private:
    Emojis();
};

#endif // EMOJIS_H
