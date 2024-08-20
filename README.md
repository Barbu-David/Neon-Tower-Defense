# Neon-Tower-Defense : CLOSED

	
 The project is now closed. Anyone is free to use the code if they wish, provided they follow the license. It is close to being a skeleton for an tower defense game engine. It was coded and tested in Arch Linux, but it should be compatible with any linux distro. It uses the raylib library for graphics and window management. 
For anyone unfamiliar, a tower defense game consists of the player placing towers in order to stop enemies from reaching a certain point.	
This readme aims to be an overview of the project.
Written entirely in the C programming language, this project really helped me improve my programming skills. The project is a tower defense prototype consisting of the following features:

## ENEMIES
  Each enemy can be defined and read from an enemy file. The file should contain attributes such as sprite, total hit points, speed, the amount of gold gained from killing an enemy, and the amount of lives lost when it breaches. The enemies being defined by files means that it is easy to quickly implement new enemies. Almost everything in this project is managed by files, making it highly customizable, without touching the code.

## PATHS AND WAVES

  The paths that the enemies walk on can be defined by putting the coordinates in a path file. In a level, there can be multiple paths in a single level.
The enemies come in waves. Each wave is defined in a wave file which contains the following: The paths that the enemies will walk on, the types, amounts, and spawn delay of the enemies. It also contains the time the wave should start at, after the level has begun, in seconds. Again, the paths and waves being defined by files makes it easy to add lots of them.

## TOWERS	

  The towers available in each level are, like everything before them, defined in files. The following are specified: damage, bullet speed, range, sprites, bullet type, cost, and available upgrades. The avalible upgrades are other towers.
 Each level has a list with the position of the starting towers and their type. The bullet type is less flexible, as it refers to the function used for bullet movement. Not all bullets should follow a straight trajectory to the target, like the one I implemented, different movement types can be added by coding a new bullet type function.

## GUI AND LEVELS
  Levels can also be defined with files, by specifying all level attributes, such as the tower list, wave list, available gold, number of lives and background sprite. The levels can be selected from a main menu, which is defined in a file, where the available levels can be specified. While in the level, by pressing p, the game can be paused. Pausing does not interfere with the timings. From the pause menu, the player can exit or return to the main menu.

## Technical challenges

  In this project, I used function pointers for the first time, in order to give each bullet type a different movement function. Also for the towers, freeing the allocated memory was more involved, since the towers held available tower upgrades, represented by other towers  which also needed to be freed, so I used a recursive freeing function. 
  Doing all of this memory management of lists to pointers of structs made me appreciate the data structures and classes present in c++ more, as they can reduce the amount of code being written. However, the educational value of going without them for a while is enormous.  Also dividing the project into files and managing the includes was fun.

## SOFTWARE USED

I used gcc for compiling, valgrind and gdb for debugging, raylib as a graphics library, and for file navigation the ranger utility in the terminator browser. For writing I used vim.

## Conclusion

  The project has a few issues, mainly the tower upgrade selection ring should be redone, since it is quite clunky. Also I haven't implemented animations and sound.
  I decided to end programming here, since I am not that interested in doing the game design itself, like adding more levels, enemies, towers, or drawing sprites. The part I really enjoyed was programming the framework for this thing to be possible, and programming something else will help me learn much more than adding these things

  Overall, I really enjoyed it and I learned a lot.
