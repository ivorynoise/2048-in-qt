#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <utility>

#include "subject.h"
#include "tile.h"

enum Direction {UP, DOWN, LEFT, RIGHT};

class Board : public Subject
{
public:
    Board(int dimension = 4);
    Board(const Board&);
    ~Board();
    Tile* getTile(int xCoord, int yCoord);
    int getDimension();
    void move(Direction directionToMove);
    bool movePossible();
    int getPointsScoredInLastMove();
    bool isWinner();
    bool isFull();

private:
    void  check2048Tile(int tileValue);
    QVector<QVector<Tile*> > board;
    int dimension;
    int pointsScoredInLastMove;
    bool tile2048Found;
    void initializeBoard();
    std::pair<int,int> freePosition();    // generates a random position on Board
    void moveVerticallyUP(int col);
    void moveVerticallyDOWN(int col);
    void moveHorizontallyLEFT(int row);
    void moveHorizontallyRIGHT(int row);
    void placeNewTile();
    bool movePossibleHorizontally();
    bool movePossibleVertically();
};

#endif // BOARD_H
