/**
* tentatively, do a very cool "world is round"
 * approach: teleport the player back to the other end of the map
 * when the player is very far out, and when there is
 * no noticeable change in ambiance.
 *
 * have oceans to separate traversable tiles
*/
# include"../systems/sceneSystem.h"


std::vector<std::vector<int>> testData =
        {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2},
        {2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}

                                          };


class WorldScene: public Scene{
public:

        WorldScene(SceneType sceneTypeArg = Blank, int widthArg = 0, int heightArg = 0,
                   std::vector<std::vector<int>>* mapArrArg = nullptr,
                   GLuint texture_id = 0, float tile_size = 0, int tile_count_x = 0, int tile_count_y = 0)
                : Scene(sceneTypeArg, widthArg, heightArg, mapArrArg, texture_id, tile_size, tile_count_x, tile_count_y) {
            // Constructor implementation for WorldScene
        }


    void update(){};

};