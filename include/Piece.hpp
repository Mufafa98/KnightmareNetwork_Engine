#pragma once

struct Piece
{

    // aabbbb
    // aa - represents the type of the piece
    //  01 - white
    //  10 - black
    // bbbb - represents the type of the piece
    //  ex. 110 = 6 = pawn
    static const unsigned short King = 1; 
    static const unsigned short Queen = 2; 
    static const unsigned short Bishop = 3; 
    static const unsigned short Knight = 4; 
    static const unsigned short Rook = 5; 
    static const unsigned short Pawn = 6;
    static const unsigned short EnPassantTrace = 7;

    static const unsigned short White = 8;
    static const unsigned short Black = 16;
};