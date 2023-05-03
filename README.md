# ENGG1340_Group70
## TEAM MEMBERS:

- Nicholas Wilson Kurniawan 3036011720
- Dorjderem Namsraijav 3035962362 
- Richie Wilynnton 3036094332
- Guo Pengyu 3036105507
- Cheung Tsz Wing 3036067262

## Game Description:
Text-Based 3D-Racing Game->
- The goal of the game is to finish the racecourse in the shortest possible time.
-  Players can steer the car left and right, and speed up/slow down the car
- Be careful! Going off track will significantly slow down the car, so make sure to stay on track, especially when going around curvatures! 

Controls ->
- "A" - Steer Left
- "D" - Steer Right
- "W" - Speed up
- "S" - Slow down
- "Q" - Quit the game (anytime)

## Features
- Generation of random game sets or events\
The curvatures (turns) that are generated in the track were randomized.\
By introducing randomization to the generation of track curvatures, each round will offer a unique experience with an entirely different course layout, adding to the game's replay value and excitement.

- Data structures for storing game status\
-Classes\
Object-Oriented Programming (Reduce Conflicts of Variables)\
Store variables and method functions.\
Improve the readability and maintainability of code.\
-Vectors\
Store information of the distances and curvatures of each track section\
Store laptimes of each round of attempts.

- Dynamic memory management\
After finishing every round, the values stored in the classes need to be reset
to their default values.\
To do this, we used the "new" function to allocate new memory for the classes to be used in the 
next round.

- File input/output\
In order to easily implement the design of the car and the background, we first designed them
inside a .txt file using numbers.\
Then, we extracted the values from the .txt files and converted the
numbers to their dedicated colors using "init_pair" from the NCurses library.\ 
Designing the sprites through this method proved to be far more efficient and effective 
than manually editing each pixel through code.

- Multiple Files\
To enhance code organization, each class is stored in a separate file and later imported into the main file where they are utilized.
## Libraries:
- NCurses ->\
By utilizing this library, we were able to enhance the presentation of our game by rendering it with vibrant colored pixels instead of plain keyboard characters, resulting in a more visually appealing and intuitive user interface with improved overall design.

## Instructions:
- Run these commands in the terminal in the following order->
1. "make"
2. "./main"
- After this, resize the terminal according to the size specified on the screen. If the terminal is already properly sized, the menu screen should pop up.
