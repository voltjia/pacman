# Pac-Man

ECE 385 Final Project

## Introduction

We have implemented basic scenes of the famous game "Pac-Man" as our ECE 385 final project.

## Dependency

* [Quartus Prime Lite v18.1](https://fpgasoftware.intel.com/18.1/?edition=lite)
* [MAX 10 DE10 - Lite](https://fpgacloud.intel.com/devstore/board/max-10-de10-lite/)

This Quartus version includes necessary components involved in this project for programming the hardware, the DE10-Lite FPGA board, and a built-in Eclipse for programming NIOS II application.

## Installation

1. Download or `git clone` this repository;
2. Open as a project in Quartus;
2. Use Platform Designer tool to generate HDL;
3. Compile the project;
4. Program the FPGA board;
5. Import `pacman` and `pacman_bsp` folders inside `software` folder into built-in Eclipse;
6. Generate BSP within `pacman_bsp`;
7. Build all software project;
8. Run.

## Usage

After the program starts, the main scene will show up. You may see four ghosts of different colors and a yellow Pac-Man at the bottom of the screen. Press arrow keys - up, down, left, and right - to control the movement of the Pac-Man. After eating each food, the player gets 5 scores, which should be displayed at the top of the screen. When you eat all the food in the scene without being caught by the ghosts, you win, and a "You Win" scene shows up. However, if you are caught by the ghosts during gameplay, then you fail, and a "Game Over" scene shows up. In order to restart the game, simply press the `enter` key.

You may also try the double-player mode by pressing `space` key, in which one player controls the Pac-Man by the arrow keys, and another player controls a ghost by WASD keys. The Pac-Man gets 1 score for each second not being caught by the ghost. If the total score reaches 300, then Pac-Man wins, but if the Pac-Man gets caught before that, then the ghost wins.

## License

MIT License © Jiacheng Huang, Wenhao Tan
