#define LOG(argument) std::cout << argument << '\n'
#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION    //this is for sprite
#define LOG(argument) std::cout << argument << '\n'
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 16
#define LEVEL1_HEIGHT 16

#define ENEMY_COUNT 3    //add enemies

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
///////////////////////////////////////////////////////below constatnts////////////////////////
// ————— CONSTANTS ————— //
const int   WINDOW_WIDTH = 1280,
        WINDOW_HEIGHT = 960;

const float BG_RED = 0,
        BG_BLUE = 0,
        BG_GREEN = 0,
        BG_OPACITY = 1.0f;

const int   VIEWPORT_X = 0,
        VIEWPORT_Y = 0,
        VIEWPORT_WIDTH = cubeSceneWidth,
        VIEWPORT_HEIGHT = cubeSceneHeight;

const char GAME_WINDOW_NAME[] = "Hello, RandomAssets";

const char V_SHADER_PATH[] = "/home/ren/projects/myFirstGame/include/shaders/vertex_textured.glsl",
        F_SHADER_PATH[] = "/home/ren/projects/myFirstGame/include/shaders/fragment_textured.glsl",
        FONT_SPRITE_FILEPATH[]   = "/home/ren/projects/myGames/include/assets/font1.png";

const float MILLISECONDS_IN_SECOND = 1000.0;

float   g_previous_ticks = 0.0f,
        g_accumulator = 0.0f;

//const char
////SPRITESHEET_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/george_0.png",
//SPRITESHEET_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/Pikachu4x4.png",
//        ENEMY0_SPRITE_PATH[] = "/home/ren/projects/myGames/include/assets/RachelsRocket.png",
//        MAP_TILESET_FILEPATH[]  = "/home/ren/projects/myGames/include/assets/tileset.png",
//        BGM_FILEPATH[]          = "/home/ren/projects/myGames/include/assets/LittlerootTownBGM.mp3",
//        JUMP_SFX_FILEPATH[]     = "/home/ren/projects/myGames/include/assets/pika.wav";

/////////////////////////////////////////above section is param tuning////////////////////////////////////////

SDL_Window* g_display_window;
ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;
SDL_GLContext context;
void initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow(GAME_WINDOW_NAME,
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    g_view_matrix = glm::mat4(1.0f);
//    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    g_projection_matrix = glm::ortho(-10.0f, 10.0f, -7.75f, 7.75f, -1.0f, 1.0f);
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    glUseProgram(g_shader_program.get_program_id());
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ThreeDInit(){    //only called at some point after initialise() is called
    g_shader_program.cleanup();
    glUseProgram(0);
    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_DEPTH_TEST);
}

void TwoDInit(){  //only called after cubeInit()
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    g_view_matrix = glm::mat4(1.0f);


    //todo: attempt to adjust camera zoom out
    //    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
//    g_projection_matrix = glm::ortho(-10.0f, 10.0f, -8.75f, 8.75f, -1.0f, 1.0f);



    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    glUseProgram(g_shader_program.get_program_id());
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
}

GLuint map_texture_id;
GameMaster gameMaster;
void worldInit(){
    map_texture_id = load_texture(MAP_TILESET_FILEPATH);

    gameMaster.scenes.push_back(new WorldScene(Normal, LEVEL1_WIDTH, LEVEL1_HEIGHT, &testData, map_texture_id, 1.0f, 4, 1));
//    gameMaster.scenes[0]->
}

void update()
{
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;

    delta_time += g_accumulator;

    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }

    while (delta_time >= FIXED_TIMESTEP)
    {
//        g_game_state.player->update(FIXED_TIMESTEP, g_game_state.player, NULL, 0, g_game_state.map);
        delta_time -= FIXED_TIMESTEP;
    }

    g_accumulator = delta_time;


    g_view_matrix = glm::mat4(1.0f);
//    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_game_state.player->get_position().x, 0.0f, 0.0f));//moving camera to follow player
}


int main(int argc, char* argv[]) {

    //successfuly switch between them: 2d -- 3d -- 2d
    initialise();
    ThreeDInit();
    TwoDInit();
    worldInit();
//    LOG()

    bool running = true;
//    CubeScene myCube;
    LOG("Player should be moved: "<<gameMaster.scenes[0]->player->precisePosition.first);

    while (running) {
//        myCube.render();
        gameMaster.scenes[0]->render(&g_shader_program);




        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Swap buffers
        SDL_GL_SwapWindow(g_display_window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(g_display_window);
    SDL_Quit();

    delete gameMaster.scenes[0];

    return 0;
}