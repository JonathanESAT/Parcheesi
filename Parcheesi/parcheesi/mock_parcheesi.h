#pragma once
#ifndef MOCK_PARCHEESI_H
#define MOCK_PARCHEESI_H

#include "iparcheesi.h"

class MockParcheesi : public IParcheesi {
  public:
    int EntryBox(int player_index) const override { return 0; }
    int ExitBox(int player_index) const override { return 0; }
    int PiecesAtHome(int player_index) const override { return 0; }
    int PiecesAtEnd(int player_index) const override { return 0; }
    bool IsBoxSafe(int box_index) const override { return false; }
    Color ColorofPiece(int box_index, int piece_index) const override { return Color::None; }

    Movement ApplyMovement(int piece_index, int player_index, int count) override { return Movement::NoMoves; }
    void SendPieceHome(int piece_index, int player_index) override {};
};

#endif // MOCK_PARCHEESI_H