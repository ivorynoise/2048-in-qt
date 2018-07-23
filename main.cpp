#include <QApplication>
#include <QDebug>

#include <ctime>
#include <cstdlib>

#include "gui/qgameboard.h"
#include "gui/qgameoverwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::srand(std::time(nullptr));

    qDebug() << "Hello World";

    QGameBoard board;
    board.show();
    return app.exec();
}

