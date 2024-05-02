# This is created for the final project of CS3113

##  General directory
- algos:

stores algorithms, for the purpose of generality, all files within function without dependency beyond stdlib
- assets:

all artwork used for the game. all sprites and sounds

- include:

system support. Code by prof Cruz. Not to be touched.

- scenes:

scenes will contain player character and map and npc, including the special 3D scene

- systems:

all kinds of miscellaneous tools: text support, input, character control, etc

## and:

- main.cpp

where the game runs.

- testField.cpp

a playground for all sorts of testcodes.

## design choices, usage, etc:

- overall code style:

global param in each scene h-file for adjustments
OOP approach to the max (why else are we using cpp at all)
dynamic memory for ambitious large game scenes (memory leak is your top concern)


- navigate the main cpp-file:

The first thing to be defined is a GameMaster which is a struct holding pointers to all component systems
the GameMaster is defined only in main for the reason that not all game contains all the systems
such a a game without sound, or without input

