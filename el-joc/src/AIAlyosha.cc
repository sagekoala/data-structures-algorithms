#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Alyosha


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */

  // Directions
  const vector<Dir> directions = {Down, Right, Up, Left};

  vector<int> dr = {1, 0, -1, 0};
  vector<int> dc = {0, 1, 0, -1};

  enum {
    FOOD = 0,
    TERRITORY = 1,
    ZOMBIE_TARGET = 2,
    ENEMY = 3,
  };

  static const int INF = 1000000000;

  bool is_zombie_pos(Pos p) {
    if (!pos_ok(p)) return false;

    Cell c = cell(p);
    if (c.id == -1) return false;

    Unit u = unit(c.id);
    return u.type == Zombie;
  }

  vector<int> dr8 = {-1, -1, -1, 0, 0, 1, 1, 1};
  vector<int> dc8 = {-1, 0, 1, -1, 1, -1, 0, 1};
  bool near_zombie(Pos p) {
    for (int k = 0; k < 8; ++k) {
      Pos q(p.i + dr8[k], p.j + dc8[k]);
      if (pos_ok(q) && is_zombie_pos(q)) return true;
    }
    return false;
  }

  bool is_target(Cell c, int target_type, int my_str) {
    if (target_type == FOOD) {
      return c.food;
    }

    if (target_type == TERRITORY) {
      return c.owner != me() && c.id == -1 && !c.food;
    }

    if (target_type == ZOMBIE_TARGET) {
      if (c.id == -1) return false;
      Unit u = unit(c.id);
      return u.type == Zombie;
    }

    if (target_type == ENEMY) {
      if (c.id == -1) return false;

      Unit u = unit(c.id);
      if (u.type != Alive) return false;
      if (u.player == me()) return false;

      
      return my_str >= strength(u.player); 
    }
    return false;
  }

  int adjacent_target(Pos source, int target_type, int my_str) {
    for (int d = 0; d < 4; ++d) {
      Pos next_pos(source.i + dr[d], source.j + dc[d]);

      if (pos_ok(next_pos)) {
        Cell c = cell(next_pos);

        if (c.type == Street && is_target(c, target_type, my_str)) {
          return d;
        }
      }
    }

    return -1;
  }

  pair<int,int> bfs_find_nearest(Pos source, int target_type, int my_str) {
    int R = board_rows();
    int C = board_cols();

    vector<vector<int> > dist(R, vector<int>(C, INF));
    vector<vector<int> > first_dir(R, vector<int>(C, -1));

    queue<Pos> q;
    dist[source.i][source.j] = 0;
    q.push(source);

    while (!q.empty()) {
      Pos cur = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d) {
        Pos next_pos(cur.i + dr[d], cur.j + dc[d]);

        if (!pos_ok(next_pos)) continue;
        if (dist[next_pos.i][next_pos.j] != INF) continue;

        Cell c = cell(next_pos);
        if (c.type != Street) continue;

        int next_dist = dist[cur.i][cur.j] + 1;
        int next_first_dir = d;

        if (cur != source) {
          next_first_dir = first_dir[cur.i][cur.j];
        }

        // Found what we are looking for
        if (is_target(c, target_type, my_str)) {
          if (target_type == ZOMBIE_TARGET || target_type == ENEMY || !near_zombie(next_pos)) {
            return make_pair(next_first_dir, next_dist);
          }
        }

        // Do not walk through units or dangerous cells
        bool safe_cell = !near_zombie(next_pos);

        if (c.id == -1 && safe_cell) {
          dist[next_pos.i][next_pos.j] = next_dist;
          first_dir[next_pos.i][next_pos.j] = next_first_dir;
          q.push(next_pos);
        }
      }
    }

    return make_pair(-1, INF);
  }

  virtual void play () {
    int my_id = me();
    int my_str = strength(my_id);

    vector<int> my_units = alive_units(my_id);
    vector<int> perm = random_permutation(my_units.size());

    for (int idx = 0; idx < (int)my_units.size(); ++idx) {
      int uid = my_units[perm[idx]];
      Unit u = unit(uid);
      Pos unit_pos = u.pos;

      // Kill adjacent zombies
      int zombie_dir = adjacent_target(unit_pos, ZOMBIE_TARGET, my_str);
      if (zombie_dir != -1) {
        move(uid, directions[zombie_dir]);
        continue;
      }

      // Attack adjacent enemy
      int enemy_dir = adjacent_target(unit_pos, ENEMY, my_str);
      if (enemy_dir != -1) {
        move(uid, directions[enemy_dir]);
        continue;
      }

      // Food
      pair<int,int> food = bfs_find_nearest(unit_pos, FOOD, my_str);
      int food_dir = food.first;
      int food_dist = food.second;

      if (food_dir != -1 && food_dist <= 10) {
        move(uid, directions[food_dir]);
        continue;
      }

      pair<int,int> territory = bfs_find_nearest(unit_pos, TERRITORY, my_str);
      int territory_dir = territory.first;
      int territory_dist = territory.second;

      if (territory_dir != -1 && territory_dist <= 8) {
        move(uid, directions[territory_dir]);
        continue;
      }

      // Early food 
      if (round() <= 60 && food_dir != -1 && food_dist <= 20) {
        move(uid, directions[food_dir]);
        continue;
      }

      if (territory_dir != -1) {
        move(uid, directions[territory_dir]);
        continue;
      }

      if (food_dir != -1 && food_dist <= 20) {
        move(uid, directions[food_dir]);
        continue;
      }

      // Random safe move
      vector<int> rperm = random_permutation(4);
      bool moved = false;

      for (int i = 0; i < 4 && !moved; ++i) {
        int d = rperm[i];
        Pos next_pos(unit_pos.i + dr[d], unit_pos.j + dc[d]);

        if (pos_ok(next_pos)) {
          Cell c = cell(next_pos);

          if (c.type == Street && c.id == -1 && !near_zombie(next_pos)) {
            move(uid, directions[d]);
            moved = true;
          }
        }
      }

      // If no safe move, move somewhere valid
      for (int i = 0; i < 4 && !moved; ++i) {
        int d = rperm[i];
        Pos next_pos(unit_pos.i + dr[d], unit_pos.j + dc[d]);

        if (pos_ok(next_pos)) {
          Cell c = cell(next_pos);

          if (c.type == Street && c.id == -1) {
            move(uid, directions[d]);
            moved = true;
          }
        }
      }
    }
  }
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);