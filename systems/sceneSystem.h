#pragma once

#ifndef scene
#define scene

#include "../include/ShaderProgram.h"
#define GL_SILENCE_DEPRECATION
#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES 1
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "../include/glm/mat4x4.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

enum SceneType{Blank, Normal};

/**
 * This is an abstract class
 * it is called upon by GameMaster and GameMaster only
 * It only handles initialization, update, that's it
 */
class Scene{
public:
    SceneType sceneType;
    std::string name;   //each scene's name only used for debugging

    int m_width, m_height;  //all scenes have their fixed width and height, matching mapArr data, can stay uninitialized
    std::vector<std::vector<int>> *  mapArr;  //all scenes have their mapArr, just for some it is un-init (black background)
                                    //we use a pointer to save some stack memory
    GLuint          m_texture_id;

    float m_tile_size;
    int   m_tile_count_x;
    int   m_tile_count_y;

    std::vector<float> m_vertices;  //for texture binding
    std::vector<float> m_texture_coordinates;

    // The boundaries of the map dependent on size of tile
    float m_left_bound, m_right_bound, m_top_bound, m_bottom_bound;

    virtual ~Scene(){};   //since this is abstract class, we don have constructor

    Scene(SceneType sceneTypeArg = Blank,int widthArg = 0, int heightArg = 0,
          std::vector<std::vector<int>> * mapArr = nullptr,
          GLuint texture_id = 0, float tile_size = 0, int tile_count_x = 0, int tile_count_y = 0)
    {
        sceneType = sceneTypeArg;
        if(Normal == sceneType){    //strictly check for Normal type
            m_width = widthArg;
            m_height = heightArg;
            m_texture_id = texture_id;

            m_tile_size = tile_size;
            m_tile_count_x = tile_count_x;
            m_tile_count_y = tile_count_y;

            build();
        }
    }

    /**
     * each of the methods below will in turn call
     * the corresponding methods of all objects:
     * game entities, subsystems, etc
     * only called by Normal type
     */
    virtual void build(){   //build defaults to map with texture, never called by a Blank scene

        // Since this is a 2D map, we need a nested for-loop
        for(int y_coord = 0; y_coord < m_height; y_coord++)
        {
            for(int x_coord = 0; x_coord < m_width; x_coord++)
            {
                // Get the current tile
                ////be careful, this is my implementation, modified!
                int tile = (*mapArr)[y_coord][x_coord];

                // If the tile number is 0 i.e. not solid, skip to the next one
                if (tile == 0) continue;

                // Otherwise, calculate its UV-coordinated
                float u_coord = (float) (tile % m_tile_count_x) / (float) m_tile_count_x;
                float v_coord = (float) (tile / m_tile_count_x) / (float) m_tile_count_y;

                // And work out their dimensions and posititions
                float tile_width = 1.0f/ (float)  m_tile_count_x;
                float tile_height = 1.0f/ (float) m_tile_count_y;

                float x_offset = -(m_tile_size / 2); // From center of tile
                float y_offset =  (m_tile_size / 2); // From center of tile

                // So we can store them inside our std::vectors
                m_vertices.insert(m_vertices.end(), {
                        x_offset + (m_tile_size * x_coord),  y_offset +  -m_tile_size * y_coord,
                        x_offset + (m_tile_size * x_coord),  y_offset + (-m_tile_size * y_coord) - m_tile_size,
                        x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                        x_offset + (m_tile_size * x_coord), y_offset + -m_tile_size * y_coord,
                        x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset + (-m_tile_size * y_coord) - m_tile_size,
                        x_offset + (m_tile_size * x_coord) + m_tile_size, y_offset +  -m_tile_size * y_coord
                });

                m_texture_coordinates.insert(m_texture_coordinates.end(), {
                        u_coord, v_coord,
                        u_coord, v_coord + (tile_height),
                        u_coord + tile_width, v_coord + (tile_height),
                        u_coord, v_coord,
                        u_coord + tile_width, v_coord + (tile_height),
                        u_coord + tile_width, v_coord
                });
            }
        }

        // The bounds are dependent on the size of the tiles
        m_left_bound   = 0 - (m_tile_size / 2);
        m_right_bound  = (m_tile_size * m_width) - (m_tile_size / 2);
        m_top_bound    = 0 + (m_tile_size / 2);
        m_bottom_bound = -(m_tile_size * m_height) + (m_tile_size / 2);

    };
    virtual void update() = 0;

    virtual void render(ShaderProgram* shader = nullptr){//note that the cubeScene does not need a shader
        if(Normal == sceneType){
            glm::mat4 model_matrix = glm::mat4(1.0f);
            shader->set_model_matrix(model_matrix);

            glUseProgram(shader->get_program_id());

            glVertexAttribPointer(shader->get_position_attribute(), 2, GL_FLOAT, false, 0, m_vertices.data());
            glEnableVertexAttribArray(shader->get_position_attribute());
            glVertexAttribPointer(shader->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, m_texture_coordinates.data());
            glEnableVertexAttribArray(shader->get_tex_coordinate_attribute());

            glBindTexture(GL_TEXTURE_2D, m_texture_id);

            glDrawArrays(GL_TRIANGLES, 0, (int) m_vertices.size() / 2);
            glDisableVertexAttribArray(shader->get_position_attribute());
            glDisableVertexAttribArray(shader->get_position_attribute());
        }
        //we will define different behavior for the cube scene there. Customized.
    };
};
#endif