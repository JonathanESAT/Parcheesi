#pragma once
#ifndef PARCHEESI_IPLAYER_H
#define PARCHEESI_IPLAYER_H

#include "iparcheesi.h"

class IPlayer {
  public:
    virtual int DecideMove(const IParcheesi& parcheesi, int current_player_index, int dice_roll) const = 0;
    virtual ~IPlayer() = default;
};

#endif // PARCHEESI_IPLAYER_H