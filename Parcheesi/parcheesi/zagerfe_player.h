#pragma once
#ifndef __CZ_PLAYER_H__
#define __CZ_PLAYER__H

#include "game.h"

class zagerfe_Player : public IPlayer {  
public:  
  virtual int DecideMove(const IParcheesi& parcheesi,
                          int player_index, int dice_roll) const override;
};

#endif