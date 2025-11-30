#pragma once
#ifndef PARCHEESI_GAME_H
#define PARCHEESI_GAME_H

#include "interface/iparcheesi.h"
#include "interface/iplayer.h"

class Game {
  public:
    Game(IParcheesi& parcheesi,const IPlayer* players[]);
    void PlayTurn();
    int Roll() const;
    IParcheesi::Color IsGameOver() const;
    IParcheesi::Color ActivePlayer() const;


  private:
    IParcheesi& parcheesi_;
    IParcheesi::Color current_player_;
    const IPlayer* players_[4];
};

#endif // PARCHEESI_GAME_H