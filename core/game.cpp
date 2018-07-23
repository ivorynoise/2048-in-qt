#include "game.h"
#include "board.h"

Game::Game(int dimension)
{
    this->score = 0;
    this->board = new Board(dimension);
}

Game::~Game(){
    delete this->board;
}

void Game::restart(){
    int dimension = board->getDimension();
    score = 0;

    delete this->board;
    board = new Board(dimension);
}

bool Game::won(){
    return board->isWinner();
}

Board* Game::getGameBoard(){
    return board;
}

bool Game::isGameOver(){
    return board->movePossible() == false;
}

int Game::getScore(){
    return score;
}

void Game::move(Direction dir){
    board->move(dir);
    score += board->getPointsScoredInLastMove();
    notifyObservers();
}
