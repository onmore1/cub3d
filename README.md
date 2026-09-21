# cub3D — 3D Raycasting Game

## Description

cub3D is a first-person 3D game built from scratch in C using raycasting,
inspired by Wolfenstein 3D. The goal of the project is to implement a real-time
software renderer that turns a 2D grid map into a textured 3D world from the
player's point of view, using only the MLX42 graphics library for putting
pixels on screen.

### Mandatory features
- Raycasting engine rendering textured walls with distinct textures per
  cardinal direction (N/S/E/W)
- Configurable floor and ceiling colors via `.cub` map file
- Smooth first-person movement (WASD) and rotation (arrow keys / mouse)
- Wall collision detection
- Strict `.cub` file parsing with full map validation (enclosure, single
  spawn, no duplicate settings)

### Bonus features
- **Minimap** — live overhead view centered on the player
- **Animated enemies** with chase, attack, and death animations
- **BFS pathfinding** — enemies compute shortest-path distance fields to the
  player once per frame
- **Sliding doors** opened/closed with `E`
- **Weapon system** — pistol, shotgun, machine gun, and hand-to-hand combat
  with animated gun bob
- **Doom-Guy HUD** — animated face reacting to damage and kills
- **Combo system** — 3 kills within 5 seconds triggers an announcer callout
- **Audio** — sound effects for weapons, steps, kills
  (miniaudio)
- **Mouse look** with delta-time-scaled sensitivity
- **Leg kick** attack (`F`)

## Instructions

### Requirements
- Linux or macOS
- `cmake` (for building MLX42)
- `libglfw3-dev` (or equivalent on your distribution)
- A C compiler (`cc`)

### Build

```bash
make          # mandatory cub3D
make bonus    # full game (doors, enemies, weapons, audio, minimap, HUD…)
make re       # clean rebuild
```

The Makefile automatically downloads and builds MLX42 and miniaudio if not
present.

Both targets share the same `src/` files; the bonus target recompiles them
with `-DBONUS`. Because the 42 norm forbids preprocessor directives inside
function bodies, bonus behaviour is wired in at global scope only:
- **Mandatory stubs** (`src/mandatory_stubs*.c`, linked into the mandatory
  build *only*) provide no-op definitions of bonus entry points so shared
  files can call them without `#ifdef`.
- **Whole-function `#ifdef BONUS / #else` pairs** are used for self-contained
  bonus logic.

### Run

```bash
./cub3d maps/your_map.cub
```

### Controls

| Key                 | Action                                |
|---------------------|---------------------------------------|
| W / A / S / D       | Move forward / left / back / right    |
| Left / Right arrows | Rotate camera                         |
| Mouse               | Look left / right (when locked)       |
| M                   | Toggle mouse lock                     |
| Space               | Fire / punch                          |
| E                   | Interact with door                    |
| F                   | Leg kick attack                       |
| 1 / 2 / 3 / 4       | Machine gun / shotgun / pistol / fists |
| Shift               | Sprint                                |
| Esc                 | Quit                                  |

## Map File Format (`.cub`)

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
100N0000000000000000000 1
...
1111111111111111111111111

| Key  | Description                              |
|------|------------------------------------------|
| `NO` | Path to north wall texture (PNG)         |
| `SO` | Path to south wall texture (PNG)         |
| `WE` | Path to west wall texture (PNG)          |
| `EA` | Path to east wall texture (PNG)          |
| `F`  | Floor color as `R,G,B` (0–255 each)      |
| `C`  | Ceiling color as `R,G,B` (0–255 each)    |

| Char                  | Meaning                                 |
|-----------------------|-----------------------------------------|
| `0`                   | Empty floor tile                        |
| `1`                   | Wall                                    |
| `N` / `S` / `E` / `W` | Player spawn position and facing        |
| `3`                   | Door                                    |
| `X`                   | Enemy spawn point                       |

The map must be fully enclosed by walls, must contain exactly one player
spawn, and all settings must appear before the map grid with no duplicates.

## Technical Overview

### Raycasting
For every vertical column of pixels on screen, a ray is cast from the player's
position into the map grid. The engine uses the **DDA (Digital Differential
Analysis)** algorithm to step the ray through the grid efficiently — computing
exactly when the ray crosses each vertical and horizontal grid line and taking
whichever crossing comes first. When the ray hits a wall, the perpendicular
distance is used to compute the wall slice height. Each wall face (N/S/E/W)
maps to a different texture, and the hit position along the wall determines
which column of the texture is sampled.

### Movement
The player has a direction vector and a camera plane vector that together
define orientation and FOV. Forward movement adds the direction vector to the
position; strafing adds a perpendicular vector. Collisions are checked against
the destination tile before any position change is applied. Rotation uses a
2×2 rotation matrix on both vectors so the FOV stays constant. Mouse input
feeds the same rotation, scaled by sensitivity and delta-time for
frame-rate-independent speed.

### Shooting & Hit Detection
On fire, a probe point is stepped along the player's direction in 0.05-unit
increments. Each step checks for a wall hit, then for an enemy hit via
squared-distance comparison against every living enemy. Damage scales with
weapon type and distance: shotgun deals 100 damage at close range, dropping
to 25 at long range; machine gun deals a flat 15; pistol deals a flat 25;
fists deal 75. A kill increments the combo counter; three kills within five
seconds triggers the announcer.

### Enemy Animations
Each enemy has a 7×8 sprite sheet (56 frames). The active frame advances on a
timer. Idle enemies cycle through walking frames, hurt enemies jump to the
hurt frame for one tick, and dying enemies play the death sequence before
freezing on the last frame. Sprites are projected into screen space using the
inverse of the camera matrix, sized by their projected depth, and sampled
column-by-column with transparency and `z_buffer` occlusion against walls.

### Enemy AI & Pathfinding
Once per frame, a **BFS** runs from the player's tile outward across all
walkable tiles, writing each tile's shortest-path distance into a 2D
`dist_field`. Enemies that have spotted the player pick whichever of their
four neighbours has the lowest distance value — shortest-path movement with
no per-enemy search cost. Enemies that reach the player's tile enter melee
mode (25 damage per hit).

## Resources

### Raycasting & rendering
- Lode Vandevenne, *Raycasting tutorial* — https://lodev.org/cgtutor/raycasting.html
  (the canonical reference for DDA-based raycasting; the basis for the engine)
- Miniaudio Documentaion - https://miniaud.io/docs/manual/index.html
- AI pathfinding - https://www.redblobgames.com/pathfinding/a-star/introduction.html

### Libraries
- **MLX42** — https://github.com/codam-coding-college/MLX42
- **miniaudio** — https://miniaud.io/

### AI usage

  - Norminatting + refactoring
