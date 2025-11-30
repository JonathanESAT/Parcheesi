#include "game.h"
#include "jplayer.h"    
#include "jparcheesi.h" 
#include <windows.h>
#include "PlayerArnau.h"


int main() {

  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  JParcheesi board;

  
  PlayerArnau p0; 
  JPlayer p1; 
  JPlayer p2; 
  JPlayer p3; 

  
  const IPlayer* players[4] = { &p0, &p1, &p2, &p3 };

  
  Game game(board, players);

  
  while (game.IsGameOver() == IParcheesi::Color::None) {
    game.PlayTurn();
  }

  return 0;
}
