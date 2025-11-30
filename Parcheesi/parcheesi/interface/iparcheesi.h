#pragma once
#ifndef PARCHEESI_IPARCHEESI_H
#define PARCHEESI_IPARCHEESI_H

class IParcheesi {
  public:
    enum class Color {
      Yellow,
      Blue,
      Red,
      Green,
      None,
    };

    enum class Movement {
      Eat,
      End,
      ReachExit,
      Normal,
      NoMoves,
      IllegalPass,
      IllegalBridge,
      IllegalBoxFull,
      IllegalPastEnd,
      IllegalEntryBlocked,
      IllegalPieceAtHome,
      IllegalMustEnterPiece,
      IllegalMustBreakBridge,
    };
    

    const static int all_boxes_bard_size = 77;
    const static int board_size = 68;
    const static int exit_size = 8;
    const static int null_piece = -1;
    const static int pieces_per_player = 4;

    virtual int EntryBox(int player_index) const = 0;
    virtual int ExitBox(int player_index) const = 0;
    virtual int PiecesAtHome(int player_index) const = 0;
    virtual int PiecesAtEnd(int player_index) const = 0;
    virtual bool IsBoxSafe(int box_index) const = 0;
    // higher box_piece_index means the piece moved later
    virtual Color ColorofPiece(int box_index, int box_piece_index) const = 0;

    virtual Movement ApplyMovement(int piece_index, int player_index, int count) = 0;
    virtual void SendPieceHome(int piece_index, int player_index) = 0;

    virtual ~IParcheesi() = default;
    virtual IParcheesi* Clone() const = 0;
};

#endif // PARCHEESI_IPARCHEESI_H