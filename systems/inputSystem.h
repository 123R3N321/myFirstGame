
#pragma once
/**
* Author: Ren
* Assignment: Rise of the AI
* Date due: 2024-03-23, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

/**
 * more note: x pos 13 means good.
 */

#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#define LOG(argument) std::cout << argument << '\n'
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f

#define ENEMY_COUNT 3    //add enemies

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

/**
 * 2 notes: I am really not sure if the mixer can work at all
 * And that once I remove this main file from cmake, it will fail to detect SDL, so don't panic
 * Just add it back to cmake and problem solved

oh, and, platform location x 4+, y-0.1+

 */

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

#include "sceneSystem.h"   //because we only control the player inside the world scene

class InputSystem{
public:
    Scene* targetScene;
    std::pair<int, int> instruction;

    InputSystem(Scene* targetSceneArg = nullptr){
        targetScene = targetSceneArg;   //which scene we are controlling
    }



    float lockLife = 0.0f;

    bool keyLock = false;
//    void process_input()
//    {
//        taetScene->player->move(instruction, floa);
//
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            switch (event.type) {
//                case SDL_QUIT:
//                case SDL_WINDOWEVENT_CLOSE:
//                    g_game_is_running  = false;
//                    break;
//
//                case SDL_KEYDOWN:
//                    switch (event.key.keysym.sym) {
//                        case SDLK_q:
//                            // Quit the game with a keystroke
//                            g_game_is_running  = false;
//                            break;
//
//                        case SDLK_SPACE:
//                            // Jump
//                            if (g_game_state.player->m_collided_bottom)
//                            {
//                                g_game_state.player->m_is_jumping = true;
//                                Mix_PlayChannel(-1, g_game_state.jump_sfx, 0);
//                            }
//                            break;
//
//                        case SDLK_k:
//                            // Jump
//                            if (g_game_state.player->m_collided_bottom)
//                            {
//                                g_game_state.player->m_is_jumping = true;
//                                Mix_PlayChannel(-1, g_game_state.jump_sfx, 0);
//                            }
//                            break;
//
//                        case SDLK_RETURN:   //I am playing with level switch here
//                            // Jump
//                            LOG("ret pressed"<<" "<<"lockLife: "<<lockLife<<std::endl);
//                            if(!keyLock){
//                                LOG("actually fired"<<'\n');
//                                meta_lvl_count++;
//                                handleMem();    //delete everything from previous level
//                                meta_init();
//                                keyLock = true;
//                            }
//                            //initialize differently based on level by calling meta_init
//                            break;
//
//                        default:
//                            break;
//                    }
//
//                default:
//                    break;
//
//
//
//
//
//            }
//        }
//
//        const Uint8* key_state = SDL_GetKeyboardState(NULL);
//
//        if (key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A])
//        {
//            g_game_state.player->move_left();
//            g_game_state.player->m_animation_indices = g_game_state.player->m_walking[g_game_state.player->LEFT];
//        }
//        else if (key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D])
//        {
//            g_game_state.player->move_right();
//            g_game_state.player->m_animation_indices = g_game_state.player->m_walking[g_game_state.player->RIGHT];
//        }
//
//        // This makes sure that the player can't move faster diagonally
//        if (glm::length(g_game_state.player->get_movement()) > 1.0f)
//        {
//            g_game_state.player->set_movement(glm::normalize(g_game_state.player->get_movement()));
//        }
//    }



};