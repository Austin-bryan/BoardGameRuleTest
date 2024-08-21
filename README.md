### Board Game Rule Test

## Overview
This project is a C++ console-based simulator designed to test and refine the rules of a 3D board game. Before implementing the graphical user interface (GUI) and more complex game mechanics, this tool was developed to allow for easy tweaking and testing of the game's rules. It provides a straightforward environment to simulate game scenarios, experiment with different rules, and ensure the game mechanics are well-balanced.

## Purpose
The primary purpose of this project was to:

- **Test Game Rules**: The simulator allows for quick iterations and testing of various game rules, ensuring they are fun, balanced, and fair before moving on to the more complex task of implementing a 3D GUI.
- **Tweak and Refine Mechanics**: By simulating the game in a console environment, it’s easier to identify and fix any issues with the game mechanics, such as resource management, turn order, and player interactions.
- **Provide a Foundation**: The logic and mechanics implemented in this console-based project will serve as the foundation for the final 3D board game, making it easier to transition from rule testing to full game development.

## Features
- **Card Mechanics**: The game includes various card types, each with different effects, such as modifying rolls, impacting opponents, or managing resources.
- **Player Management**: Supports multiple players, each with their own hand of cards, money, and stamina.
- **Customizable Plays**: Players can create custom plays using their cards, allowing for flexible strategy development.
- **Console UI**: Utilizes colored console output to enhance readability and player experience, making it easier to visualize game elements like card suits and player turns.

## How It Works
**Starting the Game**: Players are prompted to enter their names and are dealt a hand of cards.
**Making a Move**: Players take turns making moves, spending or earning money, playing cards, or trading with other players.
**Testing Scenarios**: The game’s mechanics, such as dice rolls, card plays, and stamina management, are simulated to ensure that the rules are correctly implemented and balanced.
**Iterative Testing**: The console-based nature of the game allows for rapid changes to the rules, with immediate feedback on how those changes affect gameplay.

## Installation
To compile and run the project, ensure you have a C++ compiler installed. Clone the repository and use the following commands to build and execute the game:

```
git clone https://github.com/Austin-bryan/BoardGameRuleTest
cd [repository-directory]
g++ -o CardGame *.cpp
./CardGame
```

## Usage
- **Running the Game**: Start the game and follow the on-screen prompts to simulate a board game session.
- **Tweaking Rules**: Modify the rules in the codebase as needed, recompile, and run the simulation to test the effects of those changes.

## Future Work
This project is a stepping stone towards the full 3D board game implementation. Once the rules are finalized and thoroughly tested, the next steps will include:

- Developing the 3D GUI to bring the game to life visually.
- Implementing additional features and refining the game mechanics based on the insights gained from this testing tool.

## Authors
This project was developed by Austin Bryan as part of a larger board game development process.
