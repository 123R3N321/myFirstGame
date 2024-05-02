
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
#include <iostream>

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

enum EntityType{Blocking, NonBlocking};

class Entity{
public:
    std::string name;
    EntityType entityType;
    float moveSpeed;
    std::pair<float, float> precisePosition;   //note this is taken from glm vec3, we need one more layer of conversion
    std::pair<int,int>collisionPosition;
    CollisionSystem* collisionSystem;

    bool isActive = true;   //maybe putting this in initialization is better

    // ––––– ANIMATION ––––– //
    int* animationRight = NULL, // move to the right
    * animationLeft = NULL, // move to the left
    * animationUp   = NULL, // move upwards
    * animationDown = NULL; // move downwards


private:    //only wrap a few private internal methods

    /**
     * overall we need to have 4 rounded values for truly safe collision detection
     */
    /**
     * does not make modifications.
     * @return a rounded up pair for collision system to handle the record
     */
    std::pair<int, int> roundPosition1(){//round up up for collision system
        return std::pair<int, int>(std::ceil(precisePosition.first), std::ceil(precisePosition.second));
    }
    std::pair<int, int> roundPosition2(){//round up down for collision system
        return std::pair<int, int>(std::ceil(precisePosition.first), std::floor(precisePosition.second));
    }
    std::pair<int, int> roundPosition3(){//round down down for collision system
        return std::pair<int, int>(std::floor(precisePosition.first), std::floor(precisePosition.second));
    }
    std::pair<int, int> roundPosition4(){//round down up for collision system
        return std::pair<int, int>(std::floor(precisePosition.first), std::ceil(precisePosition.second));
    }

    /**
     * internal use only function, to actually update the position
     * @param instruction passed forward from move() method
     */
    std::pair<int, int>prospectPosition(std::pair<int, int> instruction){
        std::pair<int,int> prospectPosition(collisionPosition);
        if(instruction.first>0 && instruction.second>0) {    //pos pos
            collisionPosition = roundPosition1();
        }else if (instruction.first>0 && instruction.second<0){ //pos neg
            collisionPosition = roundPosition2();
        }else if(instruction.first<0 && instruction.second<0){ //neg neg
            collisionPosition = roundPosition3();
        }else if(instruction.first<0 && instruction.second>0){ //neg pos
            collisionPosition = roundPosition4();
        }else{  //edge case of either going to zero
         std::cerr<<"moving instruction on "<<name<< "is 0"<<std::endl;
        }
        return prospectPosition;
    }

    void updatePosition(std::pair<int, int> instruction, float deltaTime){   //note we need to assume small moveSpeed
        precisePosition.first += moveSpeed * instruction.first * deltaTime;
        precisePosition.second += moveSpeed * instruction.second * deltaTime;   //update the actual precise position

        collisionPosition = prospectPosition(instruction);  //update the position on the collision map
    }

public:

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
     *
     *  we are not doing inheritance because I want two entity entityTypes to
     *  be able to change into each other
 */
    void move(std::pair<int, int> instruction, float deltaTime){
        if(collisionSystem->allowMovement(prospectPosition(instruction))){//first check if the given movement is valid
            //todo: make a move
            if(Blocking==entityType){
                collisionSystem->removeBlockingEntity(collisionPosition);   //remove the old collision position
                updatePosition(instruction, deltaTime);//update both the precise and the collision position
                collisionSystem->addBlockingEntity(collisionPosition, this);    //now collision map is updated
            }else if(NonBlocking==entityType){
                collisionSystem->removeNonBlockingEntity(collisionPosition);
                updatePosition(instruction, deltaTime);
                collisionSystem->addNonBlockingEntity(collisionPosition, this);
            }else{//error msg
                std::cerr<<"Unknown blocking/nonblocking entity entityType encountered when moving "<<
                name<<std::endl;
            }
        }

    }

    //todo: add more entity methods
};
#endif