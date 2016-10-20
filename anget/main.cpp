#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conlib.h"

#include "Map.h"
#include "Player.h"
#include "Timer.h"

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
        "#                                             %                                                                        #",
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

    srand(unsigned(time(nullptr)));

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

            switch (ch)
            {
                case Right:
                    player->move(1, 0);
                    break;
                case Left:
                    player->move(-1, 0);
                    break;
                case Top:
                    player->move(0, -1);
                    break;
                case Down:
                    player->move(0, 1);
                    break;
                case 'Q':
                    player->attack();
                    break;
            }
        }

        Timer::get().runTick();

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
