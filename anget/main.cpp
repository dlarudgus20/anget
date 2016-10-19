#include <stdio.h>
#include "conlib.h"

#include "Map.h"
#include "Player.h"

int main()
{
    Map map
    {
        "########################################################################################################################",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                     $                                                             $                                  #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                     $                                                             $                                  #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                                                                                                                      #",
        "#                     $                                                             $                                  #",
        "#                                                                                                                      #",
        "########################################################################################################################",
    };

    const int fps = 20;
    unsigned prevtime;

    auto player = std::make_shared<Player>();
    map.place(player, 8, 8);

    consize(120, 50);
    setCursorType(CursorType::No);
    clrscr();

    while (1)
    {
        prevtime = gettick();

        if (_kbhit())
        {
            int ch = getkey();

#ifdef _DEBUG
            gotoxy(0, 0);
            printf("      ");
            gotoxy(0, 0);
            printf("0x%04x", ch);
#endif

            if (ch == Right)
                player->move(1, 0);
            else if (ch == Left)
                player->move(-1, 0);
            else if (ch == Top)
                player->move(0, -1);
            else if (ch == Down)
                player->move(0, 1);
        }

        map.draw(player->getX() - map.getWidth() / 2, player->getY() - map.getHeight() / 2,
            2, 2, 100, 35);

        player->printinfo(2, 38);

        gotoxy(0, 0);

        int dt = int(gettick() - prevtime);
        int ms = 1000 / fps - dt;
        if (ms > 0)
            delay(ms);
    }
}
