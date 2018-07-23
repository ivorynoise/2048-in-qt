#include <QVBoxLayout>
#include <QDebug>

#include "qgameboard.h"
#include "qgameoverwindow.h"

QGameBoard::QGameBoard(QWidget *parent):QWidget(parent)
{
    game = new Game(4);
    game->registerObserver(this);

    resize(650, 650);
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    boardLayout = nullptr;
    resizeGuiBoard();
    drawBoard();

    messageLayout = new QHBoxLayout();
    score = new QLabel(QString("SCORE: %1").arg(game->getScore()));
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    score->setFixedHeight(40);
    messageLayout->insertWidget(1, score, 0, Qt::AlignRight);
    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }");

    message= new QLabel(QString(""));
    message->setStyleSheet("QLabel { color: rgb(235,224,214); font: 10pt; }");
    message->setFixedHeight(40);
    messageLayout->insertWidget(0, message);//, 0, Qt::AlignLeft);
    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }");

    mainLayout->insertLayout(1, messageLayout);
    connect(gameOverWindow.getResetButton(), SIGNAL(clicked()),
            this, SLOT(resetGame()));

}

void QGameBoard::resizeGuiBoard(){
    const int dimension = game->getGameBoard()->getDimension();
    gui_board.resize(dimension);

    for(int i = 0; i < dimension; ++i){
        gui_board[i].resize(dimension);
    }

    for(int r = 0; r < dimension; ++r){
        for(int c = 0; c < dimension; ++c){
            gui_board[r][c] = nullptr;
        }
    }
}

void QGameBoard::drawBoard(){
    delete boardLayout;

    int dimension = game->getGameBoard()->getDimension();
    boardLayout = new QGridLayout();
    for(int i = 0; i < dimension; ++i){
        for(int j = 0; j < dimension; ++j){
            delete gui_board[i][j];
            gui_board[i][j] = new QTile(game->getGameBoard()->getTile(i, j));
            boardLayout->addWidget(gui_board[i][j], i, j);
            gui_board[i][j]->draw();
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}

void QGameBoard::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up :
        game->move(UP);
        break;
    case Qt::Key_Down :
        game->move(DOWN);
        break;
    case Qt::Key_Left :
        game->move(LEFT);
        break;
    case Qt::Key_Right :
        game->move(RIGHT);
        break;
    }
}

void QGameBoard::resetGame()
{
    game->restart();
    drawBoard();
    gameOverWindow.close();
}

void QGameBoard::notify()
{
    if (game->isGameOver()){
        qDebug() << "Line 96 calling gameOverWindow";
        gameOverWindow.show();
    }

    if (game->won()){
        message->setText(QString("You hit 2048, congratulations!"));
    }
    else {
        score->setText(QString("SCORE: %1").arg(game->getScore()));
    }
    drawBoard();
}

QGameBoard::~QGameBoard()
{
    delete game;
}
