
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Character {
public:
  int hp;
  int dmg;
  int arm;
};

class Item {
public:
  string name;
  int cost;
  int dmg;
  int arm;

  Item(string n, int c, int d, int a) : name{n}, cost{c}, dmg{d}, arm{a} {}

  void display() {
    cout << name << endl;
    cout << "- cost: " << this->cost << endl;
    cout << "- damage: " << this->dmg << endl;
    cout << "- armour: " << this->arm << endl;
  }
};

pair<bool, int> simulate(Character &player, Character &boss) {
  int player_hp = player.hp;
  int boss_hp = boss.hp;
  int round = 1;
  for (;; round++) {
    boss_hp -= max(1, player.dmg - boss.arm);
    if (boss_hp <= 0) {
      return pair(true, round);
    }
    player_hp -= max(1, boss.dmg - player.arm);
    if (player_hp <= 0) {
      return pair(false, round);
    }
  }
}

int main() {

  Character default_player = {
      .hp = 100,
      .dmg = 0,
      .arm = 0,
  };

  Character boss = {
      .hp = 999,
      .dmg = 999,
      .arm = 999,
  };

  vector<vector<Item>> shop{};

  vector<Item> swords{Item("dagger", 8, 4, 0), Item("shortsword", 10, 5, 0),
                      Item("warhammer", 25, 6, 0), Item("longsword", 40, 7, 0),
                      Item("greataxe", 74, 8, 0)};

  shop.push_back(swords);

  vector<Item> armour{
      Item("leather", 13, 0, 1),    Item("chainmail", 31, 0, 2),
      Item("splintmail", 53, 0, 3), Item("bandedmail", 75, 0, 4),
      Item("platemail", 102, 0, 5), Item("none", 0, 0, 0)};

  shop.push_back(armour);

  vector<Item> rings{Item("dmg 1", 25, 1, 0),  Item("dmg 2", 50, 2, 0),
                     Item("dmg 3", 100, 3, 0), Item("def 1", 20, 0, 1),
                     Item("def 2", 40, 0, 2),  Item("def 3", 80, 0, 3),
                     Item("empty a", 0, 0, 0), Item("empty b", 0, 0, 0)};

  shop.push_back(rings);

  vector<int> viable_costs{};

  for (size_t s = 0; s < swords.size(); s++) {
    for (size_t a = 0; a < armour.size(); a++) {
      for (size_t l = 0; l < rings.size(); l++) {
        for (size_t r = 0; r < rings.size(); r++) {
          if (l != r) {
            int cost = 0;
            Character equiped = default_player;

            Item sworded = swords[s];
            cost += sworded.cost;
            equiped.dmg += sworded.dmg;

            Item armed = armour[a];
            cost += armed.cost;
            equiped.arm += armed.arm;

            Item ring_l = rings[l];
            cost += ring_l.cost;
            equiped.dmg += ring_l.dmg;
            equiped.arm += ring_l.arm;

            Item ring_r = rings[r];
            cost += ring_r.cost;
            equiped.dmg += ring_r.dmg;
            equiped.arm += ring_r.arm;

            auto result = simulate(equiped, boss);
            if (result.first) {
              viable_costs.push_back(cost);
            }
          }
        }
      }
    }
  }

  sort(viable_costs.begin(), viable_costs.end(), less<int>());
  cout << viable_costs.front() << endl;

  return 0;
}
