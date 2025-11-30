#pragma once
#ifndef JPLAYER_H
#define JPLAYER_H

#include "game.h"

class JPlayer : public IPlayer {
public:
 
  int DecideMove(const IParcheesi& parcheesi, int player_index, int dice_roll) const;
};

#endif // JPLAYER_H
