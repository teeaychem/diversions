

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

class Game {
public:

  int player_hp;
  int player_armour = 0;
  int player_mana;
  int mana_spend = 0;

  int boss_hp;
  int boss_dmg;

  int cooldown_shield = 0;
  int cooldown_poison = 0;
  int cooldown_recharge = 0;

  void apply_effects() {
    if (cooldown_shield > 0) {
      cooldown_shield -= 1;
      if (cooldown_shield == 0) {
        player_armour = 0;
      }
    }

    if (cooldown_poison > 0) {
      boss_hp -= 3;
      cooldown_poison -= 1;
    }

    if (cooldown_recharge > 0) {
      player_mana += 101;
      cooldown_recharge -= 1;
    }
  }

  bool cast_mm() {
    if (player_mana < 53) {
      return false;
    }
    player_mana -= 53;
    mana_spend += 53;
    boss_hp -= 4;
    return true;
  }

   bool cast_drain() {
    if (player_mana < 73) {
      return false;
    }
    player_mana -= 73;
    mana_spend += 73;
    player_hp += 2;
    boss_hp -= 2;
    return true;
  }

  bool cast_shield() {
    if (player_mana < 113 || cooldown_shield > 0) {
      return false;
    }
    player_mana -= 113;
    mana_spend += 113;
    player_armour = 7;
    cooldown_shield = 6;
    return true;
  }

  bool cast_poison() {
    if (player_mana < 173 || cooldown_poison > 0) {
      return false;
    }
    player_mana -= 173;
    mana_spend += 173;
    cooldown_poison = 6;
    return true;
  }

  bool cast_recharge() {
    if (player_mana < 229 || cooldown_recharge > 0) {
      return false;
    }
    player_mana -= 229;
    mana_spend += 229;
    cooldown_recharge = 5;
    return true;
  }

  void boss_turn() {
    apply_effects();
    player_hp -= max(1, (boss_dmg - player_armour));
  }

  bool player_wins() { return boss_hp <= 0; }

  bool boss_wins() { return player_hp <= 0; }

  void stats() {
    cout << "player hp " << player_hp << endl;
    cout << "player mana " << player_mana << endl;
    cout << "boss hp " << boss_hp << endl;
    cout << endl;
  }

  Game(int php, int pm, int bh, int bd) {
    player_hp = php;
    player_armour = 0;
    player_mana = pm;
    mana_spend = 0;
    boss_hp = bh;
    boss_dmg = bd;
    cooldown_shield = 0;
    cooldown_poison = 0;
    cooldown_recharge = 0;
  }

  Game(const Game &g) {
    player_hp = g.player_hp;
    player_armour = g.player_armour;
    player_mana = g.player_mana;
    mana_spend = g.mana_spend;
    boss_hp = g.boss_hp;
    boss_dmg = g.boss_dmg;
    cooldown_shield = g.cooldown_shield;
    cooldown_poison = g.cooldown_poison;
    cooldown_recharge = g.cooldown_recharge;
  };
};

int known_lowest = numeric_limits<int>::max();

void continue_play(vector<int> &mana_use, Game the_game) {
  if (the_game.mana_spend > known_lowest) {
    return;
  }

  the_game.player_hp -= 1;
  if (the_game.boss_wins()) {
    return;
  }

  the_game.apply_effects();
  if (the_game.player_wins()) {
    if (the_game.mana_spend < known_lowest) {
      known_lowest = the_game.mana_spend;
      mana_use.push_back(known_lowest);
      return;
    }
  }

  Game do_mm(the_game);
  if (do_mm.cast_mm()) {
    do_mm.boss_turn();
    if (do_mm.player_wins()) {
      if (do_mm.mana_spend < known_lowest) {
        known_lowest = do_mm.mana_spend;
        mana_use.push_back(do_mm.mana_spend);
      }
    } else if (!do_mm.boss_wins()) {
      continue_play(mana_use, do_mm);
    }
  }

  Game do_drain(the_game);
  if (do_drain.cast_drain()) {
    do_drain.boss_turn();
    if (do_drain.player_wins()) {
      if (do_drain.mana_spend < known_lowest) {
        known_lowest = do_drain.mana_spend;
        mana_use.push_back(do_drain.mana_spend);
      }
    } else if (!do_drain.boss_wins()) {
      continue_play(mana_use, do_drain);
    }
  }


  Game do_shield(the_game);
  if (do_shield.cast_shield()) {
    do_shield.boss_turn();
    if (do_shield.player_wins()) {
      if (do_shield.mana_spend < known_lowest) {
        known_lowest = do_shield.mana_spend;
        mana_use.push_back(do_shield.mana_spend);
      }
    } else if (!do_shield.boss_wins()) {
      continue_play(mana_use, do_shield);
    }
  }

  Game do_poison(the_game);
  if (do_poison.cast_poison()) {
    do_poison.boss_turn();
    if (do_poison.player_wins()) {
      if (do_poison.mana_spend < known_lowest) {
        known_lowest = do_poison.mana_spend;
        mana_use.push_back(do_poison.mana_spend);
      }
    } else if (!do_poison.boss_wins()) {
      continue_play(mana_use, do_poison);
    }
  }

  Game do_recharge(the_game);
  if (do_recharge.cast_recharge()) {
    do_recharge.boss_turn();
    if (do_recharge.player_wins()) {
      if (do_recharge.mana_spend < known_lowest) {
        known_lowest = do_recharge.mana_spend;
        mana_use.push_back(do_recharge.mana_spend);
      }

    } else if (!do_recharge.boss_wins()) {
      continue_play(mana_use, do_recharge);
    }
  }

  return;
}

int main() {
  // Game the_game(10, 250, 13, 8);
  // the_game.update_counters();
  // the_game.cast_poison();
  // the_game.stats();
  // the_game.boss_turn();
  // the_game.stats();
  // the_game.update_counters();
  // the_game.cast_mm();
  // the_game.stats();
  // the_game.boss_turn();
  // cout << the_game.player_wins() << endl;
  // cout << the_game.boss_wins() << endl;

  Game the_game(50, 500, 999, 999);

  vector<int> mana_use{};
  continue_play(mana_use, the_game);
  cout << "game over" << endl;
  if (mana_use.empty()) {
    cout << "oh" << endl;
    exit(1);
  }
  sort(mana_use.begin(), mana_use.end(), less<int>());
  cout << mana_use.front() << endl;

  return 0;
}
