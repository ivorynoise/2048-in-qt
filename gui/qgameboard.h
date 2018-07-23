#ifndef QGAMEBOARD_H
#define QGAMEBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QKeyEvent>


#include "core/game.h"
#include "core/observer.h"
#include "gui/qtile.h"
#include "gui/qgameoverwindow.h"

class QGameBoard : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit QGameBoard(QWidget *parent = nullptr);
    ~QGameBoard();
    void notify();

private:
    void resizeGuiBoard();
    void drawBoard();

    Game *game;
    QVBoxLayout *mainLayout;    //TODO read about these
    QGridLayout *boardLayout;
    QHBoxLayout *messageLayout;
    QVector<QVector<QTile*> > gui_board;
    QLabel *score;
    QLabel *youWin;
    QLabel *message;
    QGameOverWindow gameOverWindow;

protected:
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void resetGame();

};

#endif // QGAMEBOARD_H
