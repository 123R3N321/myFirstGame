#pragma once
/**
* tentatively, do a very cool "world is round"
 * approach: teleport the player back to the other end of the map
 * when the player is very far out, and when there is
 * no noticeable change in ambiance.
 *
 * have oceans to separate traversable tiles
*/
# include"../systems/sceneSystem.h"
# include "../systems/entitySystem.h"

/**
 * 0 - nothing, void, abyss (maybe change to water in the future)
 *      nullptr, nullptr
 *
 * 1 - ground and low laying unblocking entity, also low density entity: only one
 *      nullptr, ptr to grass/shrub/flowers
 *
 * 2 -  higher unblocking entity
 *      nullptr, ptr to canopy/blossom/character top section/grass tips
 *
 * 3 - blocking entity
 *      ptr to something that blocks, nullptr/anything ptr that is non blocking
 */


std::vector<std::vector<int>> testData =
        {
        {1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1},

                                          };


class WorldScene: public Scene{
public:
    int playerInitPosX = 0;
    int playerInitPosY = 7;


    WorldScene(SceneType sceneTypeArg = Blank, int widthArg = 0, int heightArg = 0,
                   std::vector<std::vector<int>>* mapArrArg = nullptr,
                   GLuint texture_id = 0, float tile_size = 0, int tile_count_x = 0, int tile_count_y = 0, std::vector<Entity*> entitiesArg = {})
                : Scene(sceneTypeArg, widthArg, heightArg, mapArrArg, texture_id, tile_size, tile_count_x, tile_count_y, entitiesArg) {

            // first, call the constructor of the parent part then we initialize our own things
            //todo: do the proper ordered initialization. We skip that step to first get player there
            collisionSystem = new CollisionSystem(testData);
            for(int y = 0; y<testData.size();++y){
                for(int x = 0; x<testData.size();++x){
//                    collisionSystem->addNonBlockingEntity(std::pair<int,int>(x,y), new Entity(1, x, y));
                    collisionSystem->addNonBlockingEntity(std::pair<int,int>(x,y), nullptr);
                }
            }
//todo: I have seg fault, commented out below!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!3lines (2)!!!!!!!!!!!!!!!!!
            //now we initialize the playable character
            player = new Entity(4, playerInitPosX, playerInitPosY);
            LOG("ok, see if init is fine "<<player->precisePosition.second);
            collisionSystem->addBlockingEntity(std::pair<int,int>(playerInitPosX,playerInitPosY), player);

        }

        ~WorldScene(){
            for (auto& eachEntity : entities) {
                delete eachEntity; // Assuming Entity objects were dynamically allocated
            }
        }

/**
 * in addition to the map itself, which is bottom layer
   we render entities in the order of top-down, blocking-unblocking
   thus creating a false sense of 3 dimension depth.

  for now, we hard-code which entities to put there, but in the future we
  will use some kind of rule-tile algo to automate it
 */
    virtual void renderEntities(ShaderProgram* shader){
            //todo: render each created entity based on map order.
            //todo: tentatively, do not leave empty space
        for(int y = 0; y<testData.size();++y){
            for(int x = 0; x<testData.size();++x){
                Entity* blockingImage = collisionSystem->occupancyMap[std::pair<int,int>(x,y)].first;
                Entity* nonblockingImage = collisionSystem->occupancyMap[std::pair<int,int>(x,y)].second;
                if(nullptr != blockingImage){
                    blockingImage->render(shader);
                                                                          LOG("now let's make sure rendering happens at: "<<blockingImage->precisePosition.second);
                }
                if(nullptr != nonblockingImage){
                    nonblockingImage->render(shader);
                }
            }
        }


        };



    void update(std::pair<int,int>instruction = std::pair<int,int>(0,0), float delta_time = 0.0f){
        for (auto& eachEntity : entities) {
            if(nullptr != eachEntity){
                eachEntity->update(instruction, delta_time);
            }
        }
        if(nullptr != collisionSystem){
            delete collisionSystem;
        }
    };

};