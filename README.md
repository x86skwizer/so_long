# so_long

A 2D game developed in C using the **miniLibX** library. Your goal is to collect all trophies and reach the exit. This project is part of the 42 school curriculum.  

## Table of Contents
- [Features](#features)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Author](#author)

---

## Features
- **Simple 2D rendering** of images using the miniLibX library.  
- **Collectable items** that the player must pick up before exiting.  
- **Movement** in four directions (up, down, left, right).  
- **Exit condition** that requires the player to collect all trophies (`C`) before reaching the exit (`E`).  

---

## Dependencies
1. **gcc** or another C compiler.  
2. **miniLibX** (provided by 42 on macOS).  
3. **macOS** (since this project uses the miniLibX with macOS frameworks).  

---

## Installation
1. **Clone** this repository:

   ```bash
   git clone https://github.com/your-username/so_long.git
   cd so_long
   ```

2. **Build** the executable:

   ```bash
   make
   ```

   This will compile the source files and produce the `so_long` executable.

---

## Usage

1. **Run** the game:

   ```bash
   ./so_long map.ber
   ```

   Replace `map.ber` with your own `.ber` map if desired.

2. **Map Requirements**:
   - The map must be a valid `.ber` file.  
   - The map must be rectangular and surrounded by walls (`1`).
   - Must contain exactly one player (`P`) and one exit (`E`).
   - Must contain at least one collectible (`C`).
   - Any invalid structure or missing elements will produce an error message.

---

## Controls
| Key             | Action              |
|-----------------|---------------------|
| <kbd>W</kbd>/<kbd>↑</kbd>            | Move player up    |
| <kbd>A</kbd>/<kbd>←</kbd>            | Move player left  |
| <kbd>S</kbd>/<kbd>↓</kbd>            | Move player down  |
| <kbd>D</kbd>/<kbd>→</kbd>            | Move player right |
| <kbd>ESC</kbd> or <kbd>Close Window</kbd> | Exit the game       |

---

## Project Structure

```
├── Makefile
├── ft_mlx.c
├── images
│   ├── door.xpm
│   ├── floor.xpm
│   ├── ralph.xpm
│   ├── trophy.xpm
│   └── wall.xpm
├── includes
│   ├── ft_nbr_base.c
│   ├── ft_printf.c
│   ├── ft_putchar.c
│   ├── ft_putnbr.c
│   ├── ft_putstr.c
│   ├── ft_split.c
│   ├── get_next_line.c
│   ├── get_next_line.h
│   ├── get_next_line_utils.c
│   └── libftprintf.h
├── main.c
├── map.ber
├── map.c
├── move.c
├── so_long.h
└── so_long_utils.c
```

**Key Files**  
- **`Makefile`**: Builds the project into the `so_long` executable.  
- **`main.c`**: Entry point for the program. Initializes the game and handles command line arguments.  
- **`map.c`**: Validates the map file, checks walls, lines, etc.  
- **`move.c`**: Implements player movement and exit conditions.  
- **`so_long.h`**: Header file containing structure definitions, function prototypes, and includes.  
- **`images/`**: XPM image files used for drawing the floor, wall, collectibles, etc.  
- **`includes/`**: Contains helper functions, custom `printf`, and `get_next_line` for reading the map file.

---

## Author
**Yamrire**  
**42 Network** – [student.42.fr](mailto:student.42.fr)  

Feel free to open issues or submit improvements! Enjoy playing **so_long**!