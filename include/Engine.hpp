#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Engine {
    Board *board;

public:
    Engine(Board *board);

    bool MakeMove(unsigned short col_start, unsigned short row_start, unsigned short col_end, unsigned short row_end);
};