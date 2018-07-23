#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile();
    Tile(int value);
    Tile(const Tile&);
    int getValue();
    void updateValue();
private:
    int value;
    const int multiplier;
};

#endif // TILE_H
