# AGE-Game-Engine
AGE is a simple 2D console game engine runs in UNIX using third library Ncurses.

# How-To-Run
1. You need to install `ncurses` using the following command
   > sudo apt-get install libncurses5-dev libncursesw5-dev
2. `cd` to the `build` directory and type
   > `make`
3. Once it compiles, runs the executable called `vm`.

# Architecture
* see `/doc/uml.pdf`

# Plan of Attack
* see `/doc/plan.md`

# Enhancement
* Quadtree - for fast collision detection (`log(n)`)
  * brute force is `O(n^2)`.

# To Solve
1. displayView: recursively displayEachView OR simply display a 2D array
2. Camera: How camera works perfectly with WindowModel
   1. can `GameWindow` contains mutiple `BoardWindow`
3. board type: view and solid
4. Timer: encapsolate into controller
5. ✔Object: gravitation
6. ✔Model: Do we need another `WindowModel` inheritances from `Model`?
7. ✔Collision: enhancement - brute force detection vs. Quadtree/octree detection

# Support Features
* 
* Enhancement - using Decorator Pattern for switching
  * file I/O (support save and load)
  * colour
  * QuadtreeGrid
  * multiple controller
  * multiple scenes (muti-models may exists)
  * Event System ? (probably no need for this)
