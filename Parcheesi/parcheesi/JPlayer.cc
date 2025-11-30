#include "jplayer.h"

#include "jplayer.h"

int JPlayer::DecideMove(const IParcheesi& parcheesi, int player_index, int dice_roll) const {

  int best_piece = 0;
  int best_score = -1000000;

 
  int before_home = parcheesi.PiecesAtHome(player_index);
  int before_end  = parcheesi.PiecesAtEnd(player_index);

  for (int piece = 0; piece < IParcheesi::pieces_per_player; ++piece) {


    IParcheesi* tmp = parcheesi.Clone();
    IParcheesi::Movement result = tmp->ApplyMovement(piece, player_index, dice_roll);

    int after_home = tmp->PiecesAtHome(player_index);
    int after_end  = tmp->PiecesAtEnd(player_index);

    int score = 0;

    if (result == IParcheesi::Movement::NoMoves) {
    
      score = -100000;
    } else {
    
      score += 10;

    
      if (result == IParcheesi::Movement::Eat) {
        score += 5000;    

     
        if (after_end > before_end) {
          score += 500;
        }

    
        if (before_home > after_home) {
          score += 200;
        }

      } else if (result == IParcheesi::Movement::ReachExit) {
    
        score += 3000;
      } else {

        if (before_home > after_home) {
          score += 300;
        }

        if (after_end > before_end) {
          score += 400;
        }
      }
    }

    if (score > best_score) {
      best_score = score;
      best_piece = piece;
    }

    delete tmp;
  }

  return best_piece;
}

