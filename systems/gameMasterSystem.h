#pragma once
/**
* This is the master oop that controls everything. It has pointers pointing to everything and
 * NOTHING has a pointer to master.
*/
#ifndef gameMaster_H
#define gameMaster_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "../include/glm/mat4x4.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/ShaderProgram.h"
#include "../include/stb_image.h"
#include "cmath"
#include <ctime>
#include <vector>


//////////////////////above can be ignored. We never touch those///////////////////////////////////////////

#include "../systems/collisionSystem.h"
#include "../systems/entitySystem.h"
#include "../systems/inputSystem.h"
#include "../systems/sceneSystem.h"
#include "../systems/soundSystem.h"
#include "../systems/textSystem.h"


//I do not need direct control of each scene when all of them are children classes of scene abstract class
//#include "../scenes/cubeScene.h"
//#include "../scenes/startMenuScene.h"
//#include "../scenes/transitionScene.h"
//#include "../scenes/worldScene.h"

#define LOG(argument) std::cout << argument << '\n'





class GameMaster{
public:
    /**
     * Im tempted to do the "add on-heap scenes to GameMaster" step here, but that
     * is more trouble some, also it might be good to actually
     * expose all the "new" keywords in the main and nowhere else
     * so it is easier to track possible memory leak in main
     *
     * In essence we give up some "breaindeadness" for better debugging convenience
     *
     * Oh, and, the gameMaster only cares about:
     *  1. the meta data that is saved across different scenes
     *  2. the pointers to those scenes themselves
     */
    std::vector<Scene*> scenes; //contains pointers to all scenes, all should be on the heap btw
    ////skip entity system and collision system as they are handled by scene////

    int playerlifeCount;    //how many lives does the player have left
    int playerEnemySlain;   //how many enemies has the player killed

    GameMaster(std::vector<Scene*> scenes = {}, int playerLifeCount = 3, int playerEnemySlain = 0) :
        scenes(scenes), playerlifeCount(playerLifeCount), playerEnemySlain(playerEnemySlain){
        LOG("===GameMaster Initialized===");
        for(int i = 0; i<scenes.size(); ++i){
            LOG("Loaded scene: "<<scenes[i]->name); //debugging message to check each loaded scene
        }
    }

};

#endif