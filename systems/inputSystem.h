
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
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 5

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

