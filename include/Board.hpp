#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include "Properties.hpp"
#include "Piece.hpp"

using namespace sf;
using namespace std;
class Board {
    unsigned short board[8][8];
    Texture board_background_texture;
    SoundBuffer buffer[2];
    Sound sound[2];
    map<unsigned short, Texture> pieces_texture;
    RectangleShape board_background;
    RectangleShape pieces[8][8];
    RectangleShape selected_square;
    RectangleShape highlighted_square[8][8];
protected:
    friend class Engine;
    void MovePiece(const Vector2f &start_pos, const Vector2f &end_pos);
    void SelectSquare(const Vector2f &pos);
    void DeSelectSquare();
    void HighlightSquare(const unsigned short x, const unsigned short y);
    void DeHighlightSquare();
    void SetEnPassantTrace(const Vector2f &pos, const unsigned short side);
    void RemoveEnPassantTrace(const unsigned short side);
    void UpdateBoard();
public:
    Board(const String FEN_board);
    void Draw(RenderWindow& window);
};