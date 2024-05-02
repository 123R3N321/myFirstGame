#ifndef entity
#define entity


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
/**
 * a class that is just a "puppet"
 * hostility, movement, interaction... all should be handled by
 * some external control
 *
 *  overall handled by main
 *  where input system -->gameMaster-->decides who and how to control
 *  when a mode of control is assumed, then -->use which algo to find
 *  the behavior result
 *
 * All entities have all methods,
 * just for some of them we will never be able to call upon that method
 * this is more fun.
 */

#include"collisionSystem.h"

class Entity{
public:
    int id;
    Entity(int id=3){}

    /**
     * be very careful
     * this method does three things:
     * 1    ask for collision system's permission to move (float round up)
     * 2    perform the movement
     * 3    inform collision system of the location of itself (float round up)
     *      (first, remove from old occupancy spot, then, go into new spot)
     *
     * @param instruction a pair containing the x and y value of attempted movement
     *  note that I use a pair not just two args because potentially I will
     *  just use something like an aStar instruction calculated by some algo
     *  it saves time to only have to call it once and generate a pair of x and y
     */
    CollisionSystem* collisionSystem;
    void move(std::pair<int, int> instruction){


    }
};
#endif