*This project has been created as part of the 42 curriculum by fducrot, lgranger.*

# cub3D

## Description

cub3D is a 3D raycasting project inspired by Wolfenstein 3D, the first FPS in video game history. The goal is to render a realistic first-person view inside a maze using raycasting techniques, with the miniLibX graphics library.

The program reads a `.cub` scene description file containing the map, wall textures (North, South, East, West) and floor/ceiling colors, then displays the maze in a window the player can navigate.

## Instructions

### Compilation

```bash
make         # compile the mandatory part
make clean   # remove object files
make fclean  # remove object files and binary
make re      # full rebuild
```

### Execution

```bash
./cub3D maps/map.cub
```

The program takes one argument: a valid scene file with the `.cub` extension.

### Controls

- `W` `A` `S` `D` — move through the maze
- `←` `→` — rotate the view left/right
- `ESC` — close the window and quit
- Red cross — close the window and quit

### Bonus controls

- Mouse — rotate the view
- Left click — shoot
- `E` — open/close doors
- `M` — toggle full map display
- `TAB` — toggle mouse cursor visibility

### Scene file format

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
10000N0001
1000000001
1111111111
```

Map characters: `0` (empty space), `1` (wall), `N`/`S`/`E`/`W` (player spawn + orientation), `2` (enemies), `D` or `d` (close or open door). The map must be closed by walls.

## Features

### Mandatory

- `.cub` scene file parsing with full validation
- Raycasting render with textured walls (different texture per side: N/S/E/W)
- Floor and ceiling colors
- WASD movement and arrow-key rotation
- Clean window management (ESC, red cross, minimize)

### Bonus

- Wall collisions
- Minimap system + full map toggle (`M`)
- Doors that open and close (`e`)
- Animated sprites
- Floor and ceiling textures
- Animated enemies that can be shot
- Mouse-controlled view rotation with toggleable cursor (`TAB`)
- Shooting (`left click`)
- Multithreaded rendering for performance optimization

## Resources

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- 42 subject PDF (cub3D v12.0)

### AI usage

AI (Claude) was used as a Socratic mentor during development — asking guiding questions during debugging sessions on the parsing pipeline (`.cub` file validation, map flood fill, color parsing, memory management with Valgrind) rather than generating code directly. All logic and implementation were written and understood by the authors.
