#pragma once
#include <iostream>
                                        #include <bitset>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Properties.hpp"
#include "Piece.hpp"

using namespace sf;
using namespace std;
class Board {

    Texture board_background_texture;
    map<unsigned short, Texture> pieces_texture;
    unsigned short board[8][8];
    RectangleShape board_background;
    RectangleShape pieces[8][8];

public:
    void MakeMove(unsigned short col_start, unsigned short row_start, unsigned short col_end, unsigned short row_end);

    Board(const String FEN_board);
    void Draw(RenderWindow& window);
};