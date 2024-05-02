
#define LOG(argument) std::cout << argument << '\n'


#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION    //this is for sprite
#define LOG(argument) std::cout << argument << '\n'
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 5

#define ENEMY_COUNT 3    //add enemies

#ifdef _WINDOWS
#include <GL/glew.h>
#endif


#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "include/glm/mat4x4.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/ShaderProgram.h"
#include "include/stb_image.h"
#include <cmath>


//////////////////////above can be ignored. We never touch those///////////////////////////////////////////
#include "systems/collisionSystem.h"
#include "systems/entitySystem.h"
#include "systems/gameMasterSystem.h"
#include "systems/inputSystem.h"
#include "systems/sceneSystem.h"
#include "systems/soundSystem.h"
#include "systems/textSystem.h"

#include "scenes/cubeScene.h"
#include "scenes/startMenuScene.h"
#include "scenes/transitionScene.h"
#include "scenes/worldScene.h"






int main(int argc, char* argv[]) {


    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("CubeExperiment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext context = SDL_GL_CreateContext(window);



    glEnable(GL_TEXTURE_2D);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ///////////////////////////////////////^^^^^^^^^^^^^^^^^^^^^^^^^////////////////
    bool stopFlag = false;

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    bool logFlag = true;

    bool running = true;
    CubeScene myCube;

    while (running) {
        myCube.render();

//        LOG(bounceFunction((GLfloat)SDL_GetTicks() / 1000.0f,5.0f));

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}