#ifndef scene
#define scene

#include "../include/ShaderProgram.h"

/**
 * This is an abstract class
 * it is called upon by GameMaster and GameMaster only
 * It only handles initialization, update, that's it
 */
class Scene{
public:
    std::string name;   //each scene's name only used for debugging

    virtual ~Scene() = 0;   //since this is abstract class, we don have constructor

    /**
     * each of the methods below will in turn call
     * the corresponding methods of all objects:
     * game entities, subsystems, etc
     */
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render(ShaderProgram* shader) = 0; //note that the cubeScene does not need a shader
};
#endif