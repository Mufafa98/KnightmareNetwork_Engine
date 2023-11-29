#include "Engine.hpp"

Engine::Engine(Board *board)
{
    this->board = board;
}

bool Engine::MakeMove(unsigned short col_start, unsigned short row_start, unsigned short col_end, unsigned short row_end)
{
    board->MakeMove(col_start, row_start, col_end, row_end);
    return true;
}
