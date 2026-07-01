# Data Structures & Algorithms — EDA, UPC

Coursework for the Data Structures and Algorithms (EDA) course at the
Universitat Politècnica de Catalunya (UPC), Barcelona. Spring 2026.

The course covers algorithm analysis, divide and conquer, trees and
dictionaries, heaps and priority queues, graph algorithms, exhaustive
search, and an introduction to computational complexity (P vs NP).

---

## Jutge Problems

Competitive programming problems solved on [Jutge.org](https://jutge.org),
organized by topic. Each folder contains the original PDF problem statement
and my solution in C++.

### Graph Algorithms (`graphs/`)

Problems involving BFS, DFS, Dijkstra's shortest path, topological sort,
minimum spanning trees, and grid traversal.

| Code | Problem |
|------|---------|
| P90766 | Treasures in a map (3) |
| X41530 | Forest |
| P81453 | Shortest path |
| P56892 | The problem of "the Game" |
| P13994 | Weighted shortest path (2) |
| X13208 | Path on a board |
| P16249 | Task ordering |
| P71496 | Cuts |

### Exhaustive Search (`exhaustive-search/`)

Backtracking problems covering permutations, subsets, constraint
satisfaction, and combinatorial search.

| Code | Problem |
|------|---------|
| P70756 | Partitions |
| P49889 | Consonants and vowels |
| P37197 | Incompatible species |
| X92609 | Two coins of each kind (3) |
| P76807 | Sudoku |
| P46547 | Digits in optimal order |
| P39621 | Cavalls voraços |

---

## El Joc — The Game (`el-joc/`)

The main course project. A four-player strategy game set in a zombie
apocalypse, running for 200 rounds on a 60×60 grid. Each player controls
a clan of units competing for territory, food, and survival against rival
clans and zombies. Clan strength, territorial control, kills, and food
collection all factor into the final score.

My AI player, **Alyosha** (`AIAlyosha.cc`), uses the following strategy:

- **Combat first:** each unit checks its immediate neighbors and attacks
  adjacent zombies and enemies before doing anything else. Enemy attacks
  are only initiated when my clan's strength is greater than or equal to
  the opponent's.
- **BFS pathfinding:** uses breadth-first search to find the nearest food
  and nearest unowned territory, deliberately avoiding cells adjacent to
  zombies during traversal.
- **Zombie avoidance:** checks all 8 neighbors of a candidate cell before
  moving into it; unsafe cells are excluded from the BFS frontier.
- **Priority and distance thresholds:** food within distance 10 is always
  chased; territory within distance 8 is claimed; in the early game
  (rounds 1–60) the food range extends to 20 to build clan strength
  before shifting focus to territorial expansion.
- **Fallback:** if no priority target is reachable, the unit makes a
  random safe move, or any valid move if no safe option exists.

The repository includes the full game engine source provided by the
course, the HTML match viewer, and the Alyosha player implementation.

---

## Repository Structure

```
graphs/                        # Graph algorithm problems (Jutge)
  P90766-treasures-in-a-map-3/
    statement.pdf
    solution.cc
  ...
exhaustive-search/             # Exhaustive search problems (Jutge)
  P70756-partitions/
    statement.pdf
    solution.cc
  ...
el-joc/                        # Course game project
  statement.pdf
  src/
    AIAlyosha.cc               # My AI player
    Board.hh, State.hh, ...    # Game engine (provided by course)
    Makefile
    Viewer/                    # HTML match viewer
```
