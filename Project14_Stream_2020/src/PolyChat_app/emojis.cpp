#include "emojis.h"

Emojis::Emojis()
{

}
std::list<QString> Emojis::getEmoji(){
    std::list<QString> emoji = {"😀","😄", "😁", "😆",
                       "😅", "🤣" ,"😂", "🙂",
                       "🙃", "😉", "😊", "😇",
                       "🥰","😍", "🤩", "😘",
                       "😗", "😚" ,"😙", "😋",
                       "😛", "😜", "🤪", "😝",
                       "🤑", "🤗" ,"🤭", "🤫",
                       "🤔", "🤐", "🤨", "😐",
                       "😑","😶", "😏", "😒",
                       "🙄", "😬" ,"🤥", "😌",
                       "😔", "😪", "🤤", "😴",
                       "😷", "🤒" ,"🥴", "🤕",
                       "🤢", "🤮", "🤧", "🥵",
                       "🥶","😵","🤯","🤠","🥳",
                       "😎","🤓","🧐","😕","😟",
                       "🙁","😮","😯","😲","😳",
                       "🥺","😦","😧","😨","😰",
                       "😥","😢","😭","😱","😖",
                       "😞","😓","😩","😫","🥱",
                       "😤","😡","😠","🤬","😈",
                       "👿","💀","💩","🤡","💯",
                       "💢","💥","💦","💨","💣",
                       "💬","💤","👋","🤚","🖐️",
                       "✋","🖖","👌","🤞","🤟",
                       "🤏","🤙","🤘","👉","👆",
                       "👇","👍","👎","✊","👊",
                       "🤜","🤛","👏"
                     };
    return emoji;
}