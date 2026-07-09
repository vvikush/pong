# Pong
A simple two-player Pong clone written in C for the terminal.

The game uses ASCII graphics, runs in step-by-step mode, displays the current score, and ends when one of the players reaches 21 points.

## Features

* 80x25 terminal game field
* ASCII-based rendering
* Two-player paddle controls
* Score tracking
* Winner announcement at 21 points
* Structured C implementation

## Controls

| Key   | Action                 |
| ----- | ---------------------- |
| A     | Move left paddle up    |
| Z     | Move left paddle down  |
| K     | Move right paddle up   |
| M     | Move right paddle down |
| Space | Skip turn              |

## Build

```bash
gcc src/pong.c -o pong
```

## Run

```bash
./pong
```

## Bonus

If the interactive version is implemented:

```bash
gcc src/pong_interactive.c -lncurses -o pong_interactive
./pong_interactive
```
