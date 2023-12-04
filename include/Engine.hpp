#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Board.hpp"
#include "DigitalTree.hpp"

class Engine{
    bool game_running;
    bool turn_swapped;
    unsigned short game_result;// 1-draw   2-white won   3-black won
    unsigned short pawn_needs_promotion;
    unsigned short black_castling_rights;
    unsigned short white_castling_rights;
    unsigned int turn;
    unsigned int fifty_move_rule;
    DigitalTree game_past_possitions;
    Board *board;

    bool IsLegal(unsigned short (&board_to_check)[8][8], const Vector2f &start_pos, const Vector2f &end_pos, const int options);
    bool CheckMoveRook(unsigned short (&board_to_check)[8][8], const Vector2f &start_pos, const Vector2f &end_pos);
    bool CheckMoveBishop(unsigned short (&board_to_check)[8][8], const Vector2f &start_pos, const Vector2f &end_pos);
    bool MoveResultsInCheck(const Vector2f &start_pos, const Vector2f &end_pos);
    bool IsAttackedBy(const unsigned short side, const Vector2f &pos);
    bool IsChecked(const unsigned short side);
    bool HasLegalMoves(const unsigned short side);
    string CheckSidePieces(const unsigned short side);
    string BoardToFEN();
public:
    Engine(Board &board);
    void SelectSquare(const Vector2f &pos);
    void DeSelectSquare();
    void HighlightLegalMoves(const Vector2f &pos);
    void DeHighlightLegalMoves();
    void CheckEndConditions();
    void MakeMove(const Vector2f &start_pos, const Vector2f &end_pos);
    bool GameRunning();
    bool PawnNeedsPromotion();
    void PromotePawn(const unsigned short &id);
    unsigned short GetGameResult();
    unsigned short TurnSwapped();
};

//options for legal move
// 0 - none
// 1 - ignore turn
// 2 - ignore checks
// 3 - ignore turn and checks