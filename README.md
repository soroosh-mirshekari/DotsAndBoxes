# Dots and Boxes  
Terminal-Based Strategy Game in C++

## Overview
This project is a complete terminal-based implementation of the classic *Dots and Boxes*
strategy game, developed in C++ with a focus on clean object-oriented design and
correct game logic.

## Objective
The objectives of this project are to:
- implement the full game logic of Dots and Boxes from scratch,
- correctly manage turns, scoring, and box completion rules,
- design a modular system that is easy to extend and maintain.

## Approach
The game is structured around:
- a clear separation of game state, player logic, and input handling,
- vector-based data structures to represent the board and edges,
- robust validation to handle invalid or conflicting player actions.

Special attention is given to maintaining a consistent game state and enforcing
rules accurately throughout gameplay.

## Key Concepts
object-oriented programming • state management • turn-based game logic •
data structures • input validation • file I/O (score tracking)

## Project Structure
- `main.cpp`: program entry point and game loop  
- `Game` class: board representation and rule enforcement  
- `Player` class: player state and scoring logic  

## How to Run
```bash
g++ -std=c++17 main.cpp -o dots_and_boxes
./dots_and_boxes
