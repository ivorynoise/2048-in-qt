#ifndef GAME_H
#define GAME_H

#include "subject.h"
#include "board.h"

class Game : public Subject
{
public:
    Game(int dimension);
    ~Game();

    void restart();
    bool isGameOver();
    Board* getGameBoard();
    void move(Direction dir);
    bool won();
    int getScore();

private:
    Board* board;
    int score;
};

#endif // GAME_H
