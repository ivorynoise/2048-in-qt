#include <string>
#include <cstdio>
#include <cmath>
#include <QDebug>

#include "gui/qtile.h"
#include "core/tile.h"

// Function Declarations
std::string getTileBgColor(int tileValue);
std::string getTileTextColor(int tileValue);
int getFontSize(int tileValue);


QTile::QTile(Tile *tile)
{
    setAlignment(Qt::AlignCenter);
    this->tile = tile;
}

QTile::QTile(const QString &text){

}

void QTile::draw(){
    if (this->tile == nullptr){
//        setText("XXX");
        setStyleSheet("QTile { background:rgb(204, 192, 179); border-radius:10px;}");
        return;
    }

    int tileValue = this->tile->getValue();
    setText(QString::number(tileValue));

    std::string tileBgColor = getTileBgColor(tileValue);
    std::string tileTextColor = getTileTextColor(tileValue);
    int fontSize = getFontSize(tileValue);
    int borderRadius = 10;

    char styleSheet[1000] = "";
    sprintf(styleSheet, "QTile { background: %s; color: %s; font: bold; border-radius: %dpx; font: %dpt; }",
            tileBgColor.c_str(), tileTextColor.c_str(), borderRadius, fontSize);
    setStyleSheet(styleSheet);
}

std::string getTileBgColor(int tileValue){
    static const char tileBgColorMat[12][100] = {
        "",
        "rgb(238,228,218)",
        "rgb(237,224,200)",
        "rgb(242,177,121)",
        "rgb(245,150,100)",
        "rgb(245,125,95)",
        "rgb(245,95,60)",
        "rgb(237,207,114)",
        "rgb(237,204,97)",
        "rgb(237,204,97)",
        "rgb(237,204,97)",
        "rgb(237,204,97)"
    };
    int idx = std::log2(tileValue);
    return tileBgColorMat[idx];
}

std::string getTileTextColor(int tileValue){
    static const char tileTextColorMat[12][100] = {
        "",
        "rgb(119,110,101)",
        "rgb(119,110,101)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)",
        "rgb(255,255,255)"
    };
    int idx = std::log2(tileValue);
    return tileTextColorMat[idx];
}

int getFontSize(int tileValue){
    static const int fontSize[] = {
        35, //  1
        35, //  2
        35, //  4
        35, //  8
        30, //  16
        30, //  32
        30, //  64
        25, //  128
        25, //  256
        25, //  512
        20, //  1024
        20, //  2048
    };
    int idx = std::log2(tileValue);
    return fontSize[idx];
}
