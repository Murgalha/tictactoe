# Tic-Tac-Toe

## Description

This game is a simple Player vs. AI tic-tac-toe game made to practice
my AI programming skills. The AI uses a simple minimax algorithm to decide
its next move.

## Dependencies
This game depends on the [SFML](https://www.sfml-dev.org/) library to manage windows 
and drawings and requires a C++ compiler to...compile it.

### Installing
Follow the instructions to install SFML. Search for a similar package 
if the names mismatch on your distribution. GCC probably is already
installed on your machine.

#### Debian
Update your repos and then download the library  
`# apt-get update && apt-get install libsfml-dev` 

#### Arch
`# pacman -Syyu sfml`

#### Gentoo
`# emerge --ask media-libs/libsfml`

If your distro is not on the list, feel free to make a PR adding it here.

## Playing
To build and run the game, run `make` to compile and execute
the binary file generated (or execute `make run`).
To play the game, simply click on an empty space of the board to make a move
and **try** to win.

## TODO

- Main menu to enter and exit game
- Make Better in-game UI
- Implement alpha-beta pruning on minimax algorithm
