#pragma once
#ifndef JPARCHEESI_H
#define JPARCHEESI_H

#include "interface/iparcheesi.h"

class JParcheesi : public IParcheesi {
public:
  static const int kNumPlayers = 4;
  static const int kPiecesPerPlayer = 4;
  static const int kMaxPlayers = 4;
  static const int kSafePoints = 12;
  static const int kBoxNum = 68;

  JParcheesi();
  JParcheesi* Clone() const override;

  int EntryBox(int player_index) const override;
  int ExitBox(int player_index) const override;

  int PiecesAtHome(int player_index) const override;
  int PiecesAtEnd(int player_index) const override;

  bool IsBoxSafe(int box_index) const override;

  Color ColorofPiece(int box_index, int piece_index) const override;

  int GlobalIndex(int player_index, int piece_index) const;

  int CountPiecesOnBox(int box);
  int CountPiecesOnBoxPerPlayer(int box, int player_index) const;

  void SendPieceHome(int piece_index, int player_index) override;

  int PositionOfPiece(int player_index, int piece_index) const;

  Movement ApplyMovement(int piece_index, int player_index, int count) override;

private:
 
  const int safePoint[kSafePoints]   = { 5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68 };
  const int startPoint[kMaxPlayers]  = { 5, 22, 39, 56 };
  const int finishPoint[kMaxPlayers] = { 68, 17, 34, 51 };


  int pos_[kNumPlayers * kPiecesPerPlayer];


  int FirstFinalBox(int player_index) const;
  int GoalBox(int player_index) const;
  int IsMyFinalPos(int player_index, int p) const;
  int NextBoxBoard(int box) const;
  int IsBridge(int box) const;
  int CountAllOnBox(int box) const;
  int CountMineOnBox(int box, int player_index) const;
  int StepForward(int player_index, int from) const;
  int TryAdvanceWithFinalRules(int player_index, int from, int steps, int* out_valid) const;
  void ChainEatBonus20(int player_index, int global_index);
};

#endif // JPARCHEESI_H
