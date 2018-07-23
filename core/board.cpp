#include "board.h"
#include <algorithm>
#include <QDebug>

#define WINNING_VAL 2048

Board::Board(int dimension)
{
    this->dimension = dimension;
    this->pointsScoredInLastMove = 0;
    initializeBoard();
    placeNewTile();
    placeNewTile();
}

void Board::initializeBoard(){
    board.resize(dimension);
    this->tile2048Found = false;

    for(int row = 0; row < dimension; ++row){
        board[row].resize(dimension);
    }

    for(int row = 0; row < dimension; ++row){
        for(int col = 0; col < dimension; ++col){
            board[row][col] = nullptr;
        }
    }
}


Board::Board(const Board &other){
    dimension = other.dimension;
    initializeBoard();

    for(int row = 0; row < dimension; ++row){
        for(int col = 0; col < dimension; ++col){
            delete board[row][col];
            board[row][col] = new Tile(*(other.board[row][col]));
        }
    }
}

Board::~Board(){
    for(int row = 0; row < dimension; ++row){
        for(int col = 0; col < dimension; ++col){
            delete board[row][col];
        }
    }
}

std::pair<int, int> Board::freePosition(){
    std::pair<int, int> coord;
    static int tileNo = 0;

    while(true){
        // TODO generate random using engine
        int xcoord = rand() % dimension;
        int ycoord = rand() % dimension;
        if (board[xcoord][ycoord] == nullptr){
            coord.first = xcoord;
            coord.second = ycoord;
            ++tileNo;
            qDebug() << tileNo << ": " <<  xcoord << " " << ycoord;
            break;
        }
    }
    return coord;
}


Tile* Board::getTile(int xCoord, int yCoord){
    return board[xCoord][yCoord];
}

int Board::getDimension(){
    return dimension;
}

void Board::move(Direction directionToMove){
    pointsScoredInLastMove = 0;
    switch(directionToMove){
    case UP     :
        for(int col = 0; col < dimension; ++col){
            moveVerticallyUP(col);
        }
        break;
    case DOWN   :
        for(int col = 0; col < dimension; ++col){
            moveVerticallyDOWN(col);
        }
        break;
    case LEFT   :
        for(int row = 0; row < dimension; ++row){
                moveHorizontallyLEFT(row);
        }
        break;
    case RIGHT  :
        for(int row = 0; row < dimension; ++row){
                moveHorizontallyRIGHT(row);
        }
        break;
    }
    placeNewTile();
    notifyObservers();
}

void Board::placeNewTile(){
    if (isFull() == false) {
        std::pair<int, int> coord = freePosition();
        qDebug() << "Inside placeNewTile() " << coord.first << " " << coord.second;
        board[coord.first][coord.second] = new Tile();
    }
}

void Board::moveVerticallyUP(int col){
    int dim = this->getDimension();

    int dest = 0;
    for (int src = dest + 1; src < dim; ++src){
        if (board[src][col] == nullptr){
            continue;
        }

        if (board[dest][col] == nullptr){
            std::swap(board[dest][col], board[src][col]);
            continue;
        }
        if (board[dest][col]->getValue() == board[src][col]->getValue()){
            board[dest][col]->updateValue();
            board[src][col] = nullptr;
            check2048Tile(board[dest][col]->getValue());
            pointsScoredInLastMove += board[dest][col]->getValue();
            ++dest;
        }
        else {
            std::swap(board[dest+1][col], board[src][col]);
            ++dest;
        }
    }
}

void Board::moveVerticallyDOWN(int col){
    int dest = this->getDimension()- 1;
    for(int src = dest - 1; src >= 0; --src){
        if (board[src][col] == nullptr) continue;

        if (board[dest][col] == nullptr){
            std::swap(board[dest][col], board[src][col]);
            continue;
        }

        if (board[dest][col]->getValue() == board[src][col]->getValue()){
            board[dest][col]->updateValue();
            board[src][col] = nullptr;
            pointsScoredInLastMove += board[dest][col]->getValue();
            check2048Tile(board[dest][col]->getValue());
            --dest;
        }
        else {
            std::swap(board[dest-1][col], board[src][col]);
            --dest;
        }
    }
}

void Board::moveHorizontallyLEFT(int row){
    int dim = this->getDimension();

    int dest = 0;
    for (int src = dest + 1; src < dim; ++src){
        if (board[row][src] == nullptr){
            continue;
        }

        if (board[row][dest] == nullptr){
            std::swap(board[row][dest], board[row][src]);
            continue;
        }
        if (board[row][dest]->getValue() == board[row][src]->getValue()){
            board[row][dest]->updateValue();
            board[row][src] = nullptr;
            check2048Tile(board[row][dest]->getValue());
            pointsScoredInLastMove += board[row][dest]->getValue();
            ++dest;
        }
        else {
            std::swap(board[row][dest+1], board[row][src]);
            ++dest;
        }
    }
}

void Board::moveHorizontallyRIGHT(int row){
    int dest = this->getDimension() - 1;
    for(int src = dest - 1; src >= 0; --src){
        if (board[row][src] == nullptr) continue;

        if (board[row][dest] == nullptr){
            std::swap(board[row][dest], board[row][src]);
            continue;
        }

        if (board[row][dest]->getValue() == board[row][src]->getValue()){
            board[row][dest]->updateValue();
            check2048Tile(board[row][dest]->getValue());
            pointsScoredInLastMove += board[row][dest]->getValue();
            board[row][src] = nullptr;
            --dest;
        }
        else {
            std::swap(board[row][dest-1], board[row][src]);
            --dest;
        }
    }
}

bool Board::isFull(){
    for(int r = 0; r < dimension; ++r){
        for(int c = 0; c < dimension; ++c){
            if (board[r][c] == nullptr) return false;
        }
    }
    return true;
}

bool Board::movePossibleHorizontally(){
    int dim = this->getDimension();
    for(int r = 0; r < dim; ++r){
        for(int c = 1; c < dim; ++c){
            if (board[r][c]->getValue() == board[r][c-1]->getValue()){
                return true;
            }
        }
    }
    return false;
}

bool Board::movePossibleVertically(){
    int dim = getDimension();
    for(int c = 0; c < dim; ++c){
        for(int r = 1; r < dim; ++r){
            if (board[r][c]->getValue() == board[r-1][c]->getValue()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::movePossible(){
    return (not isFull())  ||
           movePossibleHorizontally() ||
           movePossibleVertically();
}

int Board::getPointsScoredInLastMove(){
    return pointsScoredInLastMove;
}

bool Board::isWinner(){
    return tile2048Found;
}

void Board::check2048Tile(int tileValue){
    if (tileValue == WINNING_VAL){
        tile2048Found = true;
    }
}
