#include "tile.h"

Tile::Tile() : multiplier(2){
    value = 2;
}

Tile::Tile(int value) : multiplier(2){
    this->value = value;
}

Tile::Tile(const Tile& other) : multiplier(2){
    this->value = other.value;
}

int Tile::getValue(){
    return this->value;
}

void Tile::updateValue(){
    this->value *= multiplier;
}
