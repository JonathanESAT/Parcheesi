#pragma once
#ifndef PLAYER_ARNAU_H
#define PLAYER_ARNAU_H

#include "interface/iplayer.h"

class PlayerArnau : public IPlayer {
  public:
    int DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const override;
};

#endif // PLAYER_ARNAU_H
