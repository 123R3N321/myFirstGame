#pragma once

#ifndef entity
#define entity

#define LOG(argument) std::cout << argument << '\n'


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
#include "sceneSystem.h"



const char
//SPRITESHEET_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/george_0.png",
PLAYER_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/Pikachu4x4.png",
        ENEMY0_SPRITE_PATH[] = "/home/ren/projects/myGames/include/assets/RachelsRocket.png",
        MAP_TILESET_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/simpleTile.png",
        BGM_FILEPATH[]          = "/home/ren/projects/myGames/include/assets/LittlerootTownBGM.mp3",
        JUMP_SFX_FILEPATH[]     = "/home/ren/projects/myGames/include/assets/pika.wav";



/**
 * convert between a pair of x y val to vec3 used by glm
 * @return
 */
glm::vec3 vecPostion(std::pair<float, float> position){
    glm::vec3 vec(0.0f);
    vec.x = position.first;
    vec.y = -position.second;
    return vec;
}



enum EntityType{Blocking, NonBlocking};

class Entity{
public:
    std::string name;
    EntityType entityType;
    float moveSpeed;
    std::pair<float, float> precisePosition;   //note this is taken from glm vec3, we need one more layer of conversion
    std::pair<int,int>collisionPosition;
    CollisionSystem* collisionSystem;

    bool m_is_active = true;   //maybe putting this in initialization is better
    bool m_is_moving = false;   //this will be updated by instruction system

    // ––––– ANIMATION ––––– //
    int* m_animation_right = NULL, // move to the right
    * m_animation_left = NULL, // move to the left
    * m_animation_up   = NULL, // move upwards
    * m_animation_down = NULL; // move downwards

    glm::mat4 m_model_matrix;

    float m_width = 1;  //might not be needed
    float m_height = 1;

    static const int    SECONDS_PER_FRAME = 4;
    static const int    LEFT    = 0,
            RIGHT   = 1,
            UP      = 2,
            DOWN    = 3;

    // ————— ANIMATION ————— //
    int** m_walking = new int* [4]
            {
                    m_animation_left,
                    m_animation_right,
                    m_animation_up,
                    m_animation_down
            };

    int m_animation_frames  = 0,
            m_animation_index   = 0,
            m_animation_cols    = 0,
            m_animation_rows    = 0;

    int*    m_animation_indices = NULL;
    float   m_animation_time = 0.0f;

    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;   //for the moment, not used

    GLuint    m_texture_id;


    Entity();
    ~Entity(){};

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index)
    {
        // Step 1: Calculate the UV location of the indexed frame
        float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
        float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

        // Step 2: Calculate its UV size
        float width = 1.0f / (float)m_animation_cols;
        float height = 1.0f / (float)m_animation_rows;

        // Step 3: Just as we have done before, match the texture coordinates to the vertices
        float tex_coords[] =
                {
                        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
                        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
                };

        float vertices[] =
                {
                        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
                        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
                };

        // Step 4: And render
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->get_position_attribute());

        glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
        glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(program->get_position_attribute());
        glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
    }






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
        if (0 == instruction.first && 0 == instruction.second){
            m_is_moving = false;
            return;
        }
        m_is_moving = true;

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


    void update(std::pair<int, int> instruction, float deltaTime)
    {


        if (!m_is_active) return;

        if (m_animation_indices != NULL)
        {
            if (m_is_moving)
            {
                m_animation_time += deltaTime;
                float frames_per_second = (float)1 / SECONDS_PER_FRAME;

                if (m_animation_time >= frames_per_second)
                {
                    m_animation_time = 0.0f;
                    m_animation_index++;

                    if (m_animation_index >= m_animation_frames)
                    {
                        m_animation_index = 0;
                    }
                }
            }
        }
        updatePosition(instruction, deltaTime); //position changes
        m_model_matrix = glm::mat4(1.0f);
        m_model_matrix = glm::translate(m_model_matrix, vecPostion(precisePosition));   //the translation happens with precise location
    }


    void render(ShaderProgram* program) //exact code copy
    {
        program->set_model_matrix(m_model_matrix);

        if (m_animation_indices != NULL)
        {
            draw_sprite_from_texture_atlas(program, m_texture_id, m_animation_indices[m_animation_index]);
            return;
        }

        float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
        float tex_coords[] = { 0.0,  1.0, 1.0,  1.0, 1.0, 0.0,  0.0,  1.0, 1.0, 0.0,  0.0, 0.0 };

        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->get_position_attribute());
        glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
        glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(program->get_position_attribute());
        glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
    }

    /**
     * initcode matches the mapArr numbers, default give a small grass
     * @param initcode
     */
    Entity(int initcode=1, int x = 0, int y = 0 ){
        precisePosition = std::pair<int, int>(x,y);
        collisionPosition = std::pair<float, float>(x,y);
        if(1 == initcode){

        }else if(2 == initcode){

        }else if(3 == initcode){

        }else if(4 == initcode){    //create a playable character
            entityType = Blocking;
            m_texture_id = load_texture(PLAYER_FILEPATH);


            m_walking[DOWN] = new int[4] { 0, 1, 2, 3 };
            m_walking[LEFT] = new int[4] { 4, 5, 6, 7 };
            m_walking[RIGHT] = new int[4] { 8, 9, 10, 11 };
            m_walking[UP] = new int[4] { 12, 13, 14, 15 };

            m_animation_indices = m_walking[RIGHT];  // start George looking left
            m_animation_frames = 4;
            m_animation_index = 0;
            m_animation_time = 0.0f;
            m_animation_cols = 4;
            m_animation_rows = 4;
            m_height = 0.8f;
            m_width = 0.8f;
            LOG("This is to see that player is created");
        }
    }

};
#endif