#include "game.h"

int main (int argc, char* argv[])
{
    Game game;
    game.init();
    game.gameLoop();
    return 0;
}
