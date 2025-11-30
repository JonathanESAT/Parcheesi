#include "game.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>

const char* const colors[] = {"🟡 Yellow", "🔵 Blue", "🔴 Red", "🟢 Green"};

Game::Game( IParcheesi& parcheesi, const IPlayer* players[])
    : parcheesi_{parcheesi}
    , current_player_{IParcheesi::Color::Yellow}
 {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║        🎲  WELCOME TO PARCHEESI GAME!  🎲         ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    if(!(players[0] || players[1] || players[2] || players[3])) {
      printf("❌ No players defined! Aborting...\n");
      std::abort();
    }

    std::copy(players,players+4,players_);
    
    printf("Players initialized:\n");

    for (int i = 0; i < 4; i++) {
      if (players_[i]) {
        printf("  ✓ %s\n", colors[i]);
      }
    }
    printf("\n");
 }

void Game::PlayTurn() {
  int player_index = static_cast<int>(current_player_);
  const char* player_colors[] = {"🟡 YELLOW", "🔵 BLUE", "🔴 RED", "🟢 GREEN"};

  printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
  printf("  %s PLAYER'S TURN\n", player_colors[player_index]);
  printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
  
  int pieces_at_home = parcheesi_.PiecesAtHome(player_index);
  int pieces_at_end = parcheesi_.PiecesAtEnd(player_index);
  printf("  📊 Status: %d pieces at home | %d pieces at end\n\n", pieces_at_home, pieces_at_end);
  
  int consecutive_sixes = 0;
  int last_moved_piece;
  int dice;
  do {
    dice = Roll();
    printf("  🎲 Rolled: %d\n", dice);

    // Send last moved piece home if three consecutive sixes
    if (dice == 6) {
      consecutive_sixes++;
      printf("  ⭐ Six rolled! (Consecutive sixes: %d)\n", consecutive_sixes);
    }
    if (consecutive_sixes == 3) {
      printf("  ⚠️  THREE SIXES IN A ROW! Piece #%d sent back home!\n", last_moved_piece);
      parcheesi_.SendPieceHome(last_moved_piece, player_index);
      break;
    }

    // Check if all pieces are out of home - if so, a 6 becomes a 7
    int movement = dice;
    if (dice == 6 && parcheesi_.PiecesAtHome(player_index) == 0) {
      movement = 7;
      printf("  ✨ Bonus! All pieces out - 6 becomes 7!\n");
    }

    // Let the player decide which piece to move
    const IPlayer& current_player = *(players_[player_index]);
    int piece_to_move = current_player.DecideMove(parcheesi_, player_index, movement);

    if (piece_to_move == -1) {
      printf("  ⏭️  Player decides to PASS (no valid moves)\n");
    } else {
      printf("  ➡️  Moving piece #%d by %d spaces...\n", piece_to_move, movement);
    }
    
    IParcheesi::Movement result = parcheesi_.ApplyMovement(piece_to_move, player_index, movement);
    
    // Report the result
    const char* result_msgs[] = {
      "💥 Ate opponent's piece!",
      "🏁 Piece reached the end!",
      "🚪 Piece reached the exit!",
      "✅ Normal move",
      "⛔ No moves available",
      "❌ ILLEGAL: Cannot pass",
      "❌ ILLEGAL: Bridge blocking",
      "❌ ILLEGAL: Box is full",
      "❌ ILLEGAL: Past the end",
      "❌ ILLEGAL: Entry blocked",
      "❌ ILLEGAL: Piece at home",
      "❌ ILLEGAL: Must enter piece",
      "❌ ILLEGAL: Must break bridge"
    };
    printf("  %s\n", result_msgs[static_cast<int>(result)]);
    
    if (result >= IParcheesi::Movement::IllegalPass) {
      // Invalid move - eliminate player immediately
      printf("\n  ⛔⛔⛔ PLAYER %s ELIMINATED FOR ILLEGAL MOVE! ⛔⛔⛔\n", player_colors[player_index]);
      players_[player_index] = nullptr;
      break;
    }
    last_moved_piece = piece_to_move;
    
    if (dice == 6 && consecutive_sixes < 3) {
      printf("  🔄 Rolling again...\n\n");
    }
    
  } while(dice == 6);
  
  printf("\n  Turn complete!\n");

  // Check for victory conditions
  // Check if current player won by getting all 4 pieces to the end
  if (parcheesi_.PiecesAtEnd(player_index) == 4) {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║             🎉🏆  VICTORY!  🏆🎉                   ║\n");
    printf("║                                                       ║\n");
    printf("║        %s PLAYER WINS!                 ║\n", player_colors[player_index]);
    printf("║                                                       ║\n");
    printf("║           All 4 pieces reached the end!              ║\n");
    printf("║                                                       ║\n");
    printf("║               ⭐ CONGRATULATIONS! ⭐                  ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("              🎊🎊🎊🎊🎊🎊🎊🎊\n");
    printf("              🎆  SPECTACULAR WIN!  🎆\n");
    printf("              🎊🎊🎊🎊🎊🎊🎊🎊\n");
    printf("\n");
    return;
  }

  // Check if only one player remains after elimination
  int active_players = 0;
  int last_active_player = -1;
  for (int i = 0; i < 4; ++i) {
    if (players_[i]) {
      active_players++;
      last_active_player = i;
    }
  }

  if (active_players == 1) {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║             🏆  GAME OVER!  🏆                    ║\n");
    printf("║                                                       ║\n");
    printf("║        %s PLAYER WINS!                 ║\n", player_colors[last_active_player]);
    printf("║                                                       ║\n");
    printf("║        Last player standing by elimination!          ║\n");
    printf("║                                                       ║\n");
    printf("║             ⭐ SURVIVOR VICTORY! ⭐                   ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("              💪  UNDEFEATED CHAMPION!  💪\n");
    printf("\n");
    return;
  }

  // Advance to next player
  do {
    player_index = (player_index + 1) % 4;
    current_player_ = static_cast<IParcheesi::Color>(player_index);
  } while (players_[player_index] == nullptr);
}

int Game::Roll() const {
  static bool seeded = false;
  if (!seeded) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    seeded = true;
  }
  return (std::rand() % 6) + 1;  // Returns 1-6
}

IParcheesi::Color Game::IsGameOver() const {
  // Check if any player has won by getting all pieces to the end
  for (int player = 0; player < 4; ++player) {
    if (parcheesi_.PiecesAtEnd(player) == 4) {
      return static_cast<IParcheesi::Color>(player);
    }
  }

  // Check if only one player remains not eliminated
  int active_players = 0;
  int last_active_player = -1;
  for (int player = 0; player < 4; ++player) {
    if (players_[player]) {
      active_players++;
      last_active_player = player;
    }
  }

  if (active_players == 1) {
    return static_cast<IParcheesi::Color>(last_active_player);
  }

  return IParcheesi::Color::None;
}

IParcheesi::Color Game::ActivePlayer() const {
  return current_player_;
}