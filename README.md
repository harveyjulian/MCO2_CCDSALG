# Rat Maze Simulator (BFS)

A terminal-based maze solver written in C. It loads a maze from a text file and uses **Breadth-First Search (BFS)** to guide a "rat" from the start cell (`S`) to the goal cell (`G`), animating the exploration and the final path directly in the terminal.

## Features

- Interactive menu (load a maze, run the simulation, quit)
- Step-by-step animation of the BFS frontier as it explores the maze
- Final shortest path traced and highlighted once the goal is found
- Search metrics after each run: cells explored, path length, and execution time
- Bundled test maze files covering single-solution, multiple-solution, and no-solution cases

## Project Structure

```
MCO2_CCDSALG-main/
├── src/
│   ├── include/
│   │   ├── common.h      # shared constants (MAX_DIM, MIN_DIM, MAX_QUEUE) + Point struct
│   │   ├── maze.h        # Maze struct, loadMaze/isInBounds/isWalkable declarations
│   │   ├── queue.h       # Queue struct, FIFO queue declarations
│   │   ├── render.h      # clearScreen/renderMaze declarations
│   │   ├── search.h      # SearchResult struct, runBFS declaration
│   │   └── ui.h          # menu/banner/metrics declarations
│   ├── main.c            # program entry point
│   ├── maze.c            # loads a maze file, bounds/walkable checks
│   ├── queue.c           # self-implemented FIFO queue used by BFS
│   ├── render.c          # draws the maze + rat to the terminal
│   ├── search.c          # the BFS algorithm and path reconstruction
│   └── ui.c              # menu loop, banners, metrics display
└── Test Cases/            # sample maze files you can load from the menu
    ├── Single/             # mazes with exactly one path from S to G (30 files)
    ├── Multiple/           # mazes with more than one valid path (30 files)
    └── No Solution/        # mazes where G is unreachable (30 files)
```

## Requirements

- A C compiler (GCC or Clang)
- A POSIX environment — the code uses `unistd.h` and `usleep()` for the animation delay
  - **Linux / macOS**: works out of the box
  - **Windows**: build with WSL, or MinGW-w64/MSYS2 (plain MSVC/`cl.exe` will not work without changes)
- A terminal that supports UTF-8 and ANSI escape codes (any modern terminal — Windows Terminal, iTerm2, GNOME Terminal, the VS Code integrated terminal, etc.) so the block characters (`█`) and colors render correctly

## Building

There's no Makefile yet, so compile all the source files together:

```bash
gcc -std=c99 -Wall -Wextra src/main.c src/maze.c src/queue.c src/render.c src/search.c src/ui.c -o rat_sim
```

This produces an executable named `rat_sim` (use `rat_sim.exe` on Windows/MinGW).

## Running

```bash
./rat_sim
```

You'll see a menu:

```
[1] Start Simulator
[2] Load File
[3] Quit
```

1. Choose **[2]** and enter the path to a maze `.txt` file when prompted.
2. Once a maze is loaded, choose **[1]** to run BFS and watch the animation. Metrics (cells explored, path length, execution time) are printed at the end.
3. Choose **[3]** at any time to exit.

> **Note on filenames with spaces:** the filename prompt reads input with `scanf`, which stops at the first space. Since the bundled test folder is named `Test Cases`, a path like `Test Cases/Single/maze1.txt` won't load correctly as typed. Either `cd` into the maze's folder first and enter just the filename (e.g. `maze1.txt`), or copy the maze file somewhere without spaces in the path.

## Maze File Format

```
<rows> <cols>
<row 1>
<row 2>
...
<row N>
```

- `rows` and `cols` must each be between 15 and 30 (inclusive).
- Each of the following `rows` lines must be exactly `cols` characters wide.
- Symbols:
  - `#` — wall
  - ` ` (space) — open floor
  - `S` — start position (exactly one required)
  - `G` — goal position (exactly one required)

Example (7×7):

```
7 7
#######
#S    #
# ### #
# #   #
# # ###
#    G#
#######
```

If the file is missing, malformed, out of the 15–30 size range, or doesn't contain exactly one `S` and one `G`, loading will fail and you'll be asked to try again.

## Test Cases

The `Test Cases/` folder has ready-made mazes you can load right away, grouped by outcome:

| Folder | Contents |
|---|---|
| `Single/` | Exactly one path exists from `S` to `G` |
| `Multiple/` | More than one valid path exists |
| `No Solution/` | `G` is unreachable from `S` |

Each folder has mazes ranging from 15×15 up to 29×29, useful for checking correctness and observing how execution time and cells explored scale with maze size.

> One file has a typo in its extension: `Test Cases/Multiple/maze17.tzt` (should be `.txt`). Rename it if you want to load it from the menu.
