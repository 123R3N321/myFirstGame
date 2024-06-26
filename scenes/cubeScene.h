#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION    //this is for sprite
#define LOG(argument) std::cout << argument << '\n'
#include "../systems/sceneSystem.h"
#include "../include/glm/gtc/type_ptr.hpp"


const int cubeSceneWidth = 1280;   //use a smaller window
const int cubeSceneHeight = 960;


const char
        DICE1[] = "/home/ren/projects/myGames/include/assets/Moon.jpeg",
        DICE2[] = "/home/ren/projects/myGames/include/assets/Moon.jpeg",
        DICE3[] = "/home/ren/projects/myGames/include/assets/Moon.jpeg",
        DICE4[] = "/home/ren/projects/myGames/include/assets/Moon.jpeg",
        DICE6[] = "/home/ren/projects/myGames/include/assets/Moon.jpeg",
        DICE5[] = "/home/ren/projects/myGames/include/assets/simpleTile.png";



float Axis[] = {                        //overall 3by3 is enough
        1.0f,1.0f,1.0f,     //blue
        1.0f,-1.0f,1.0f,    //pink
        1.0f,1.0f,-1.0f,    //cyan
};


GLfloat texture_coordinates[] = {
        // Front face (Red)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left

        // Back face (Green)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left

        // Top face (Blue)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left

        // Bottom face (Yellow)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left

        // Right face (Magenta)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left

        // Left face (Cyan)
        0.0f, 0.0f, // Bottom-left
        1.0f, 0.0f, // Bottom-right
        1.0f, 1.0f, // Top-right
        0.0f, 1.0f, // Top-left
};

GLfloat frontVertices[] = {
        -0.5f, -0.5f, 0.5f,  // Vertex 1
        0.5f, -0.5f, 0.5f,   // Vertex 2
        -0.5f, 0.5f, 0.5f,   // Vertex 3
        0.5f, -0.5f, 0.5f,   // Vertex 4
        0.5f, 0.5f, 0.5f,    // Vertex 5
        -0.5f, 0.5f, 0.5f    // Vertex 6
};

GLfloat frontTexCoords[] = {
        0.0f, 0.0f,  // Texture coordinate for Vertex 1 (bottom-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 2 (bottom-right corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 3 (top-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 4 (bottom-right corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 5 (top-right corner)
        0.0f, 1.0f   // Texture coordinate for Vertex 6 (top-left corner)
};

// Back face
GLfloat backVertices[] = {
        -0.5f, -0.5f, -0.5f, // Vertex 1
        0.5f, -0.5f, -0.5f,  // Vertex 2
        -0.5f, 0.5f, -0.5f,  // Vertex 3
        0.5f, -0.5f, -0.5f,  // Vertex 4
        0.5f, 0.5f, -0.5f,   // Vertex 5
        -0.5f, 0.5f, -0.5f   // Vertex 6
};

GLfloat backTexCoords[] = {
        1.0f, 1.0f,  // Texture coordinate for Vertex 1 (top-right corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 2 (top-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 3 (bottom-right corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 4 (top-left corner)
        0.0f, 0.0f,  // Texture coordinate for Vertex 5 (bottom-left corner)
        1.0f, 0.0f   // Texture coordinate for Vertex 6 (bottom-right corner)
};

// Top face
GLfloat topVertices[] = {
        -0.5f, 0.5f, -0.5f,  // Vertex 1
        0.5f, 0.5f, -0.5f,   // Vertex 2
        -0.5f, 0.5f, 0.5f,   // Vertex 3
        0.5f, 0.5f, -0.5f,   // Vertex 4
        0.5f, 0.5f, 0.5f,    // Vertex 5
        -0.5f, 0.5f, 0.5f    // Vertex 6
};

GLfloat topTexCoords[] = {
        0.0f, 1.0f,  // Texture coordinate for Vertex 1 (bottom-left corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 2 (bottom-right corner)
        0.0f, 0.0f,  // Texture coordinate for Vertex 3 (top-left corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 4 (bottom-right corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 5 (top-right corner)
        0.0f, 0.0f   // Texture coordinate for Vertex 6 (top-left corner)
};


// Bottom face
GLfloat bottomVertices[] = {
        -0.5f, -0.5f, -0.5f, // Vertex 1
        0.5f, -0.5f, -0.5f,  // Vertex 2
        -0.5f, -0.5f, 0.5f,  // Vertex 3
        0.5f, -0.5f, -0.5f,  // Vertex 4
        0.5f, -0.5f, 0.5f,   // Vertex 5
        -0.5f, -0.5f, 0.5f   // Vertex 6
};

GLfloat bottomTexCoords[] = {
        0.0f, 0.0f,  // Texture coordinate for Vertex 1 (top-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 2 (top-right corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 3 (bottom-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 4 (top-right corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 5 (bottom-right corner)
        0.0f, 1.0f   // Texture coordinate for Vertex 6 (bottom-left corner)
};

// Right face
GLfloat rightVertices[] = {
        0.5f, -0.5f, -0.5f,  // Vertex 1
        0.5f, 0.5f, -0.5f,   // Vertex 2
        0.5f, -0.5f, 0.5f,   // Vertex 3
        0.5f, 0.5f, -0.5f,   // Vertex 4
        0.5f, 0.5f, 0.5f,    // Vertex 5
        0.5f, -0.5f, 0.5f    // Vertex 6
};

GLfloat rightTexCoords[] = {
        0.0f, 0.0f,  // Texture coordinate for Vertex 1 (bottom-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 2 (bottom-right corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 3 (top-left corner)
        1.0f, 0.0f,  // Texture coordinate for Vertex 4 (bottom-right corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 5 (top-right corner)
        0.0f, 1.0f   // Texture coordinate for Vertex 6 (top-left corner)
};

// Left face
GLfloat leftVertices[] = {
        -0.5f, -0.5f, -0.5f, // Vertex 1
        -0.5f, 0.5f, -0.5f,  // Vertex 2
        -0.5f, -0.5f, 0.5f,  // Vertex 3
        -0.5f, 0.5f, -0.5f,  // Vertex 4
        -0.5f, 0.5f, 0.5f,   // Vertex 5
        -0.5f, -0.5f, 0.5f   // Vertex 6
};

GLfloat leftTexCoords[] = {
        1.0f, 0.0f,  // Texture coordinate for Vertex 1 (bottom-right corner)
        0.0f, 0.0f,  // Texture coordinate for Vertex 2 (bottom-left corner)
        1.0f, 1.0f,  // Texture coordinate for Vertex 3 (top-right corner)
        0.0f, 0.0f,  // Texture coordinate for Vertex 4 (bottom-left corner)
        0.0f, 1.0f,  // Texture coordinate for Vertex 5 (top-left corner)
        1.0f, 1.0f   // Texture coordinate for Vertex 6 (top-right corner)
};



class CubeScene : public Scene{
public:
    float rotationSpeed = 50.0f; //45 - 55 ok, global param for speed of diagonal rotation
    int axisMode = 0;   //0, 1, 2   (different random number results)
    float height = 5.0f;    //3 - 7 ok, global param for falling height (so also size of dice)

    GLuint DICE1ID;
    GLuint DICE2ID;
    GLuint DICE3ID;
    GLuint DICE4ID;
    GLuint DICE5ID;
    GLuint DICE6ID;



    float totalRotationAngle = 0.0f;    //non-user tracker param
    float rotationAngle = 0.0f;

    bool stopFlag = false;
    bool logFlag = true;








    void drawCubeFace(GLfloat* vertices, GLfloat* texCoords, GLuint textureID) {
        // Enable vertex array
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // Specify vertex data
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

        // Bind texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Draw the face
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Disable vertex array
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }





    void standardDraw(GLuint DICE1ID, GLuint DICE2ID, GLuint DICE3ID, GLuint DICE4ID, GLuint DICE5ID, GLuint DICE6ID){

        drawCubeFace(frontVertices, frontTexCoords, DICE1ID);

        drawCubeFace(backVertices, backTexCoords, DICE2ID);

        drawCubeFace(topVertices, topTexCoords, DICE3ID);

        drawCubeFace(bottomVertices, bottomTexCoords, DICE4ID);

        drawCubeFace(rightVertices, rightTexCoords, DICE5ID);

        drawCubeFace(leftVertices, leftTexCoords, DICE6ID);

    }

    float bounceFunction(float time, float height) {
        if(time<1.76){
            return -exp(time) + 1;}
        else if(time<sqrt( 9.81/8 * height)){  //hit gorund instance
            return exp(-time) * sin(17 * time) - height;
        }else{  //stabe stationary instance
            return -height;
        }
    }

    std::string callRes(int angle){
        angle /= 10;
        angle *= 10;    //a simple digit trim
//    LOG("angle rounded: "<<angle);
//    LOG("check again? "<<angle%180);
        if(0 == axisMode){
            if(0 == angle%360){
                return "pink";
            }
            else if (0 == angle%180){   //somehow casting not working
                return "blue";
            }else{    //90 deg
                return "red";
            }
        }
        else if(1 == axisMode){
            return "pink";  //unfinished
        }
        else{
            return "cyan";
        }

    }



    void update(){}

    virtual void renderEntities(){};

    virtual void render(ShaderProgram* shader = nullptr) {//note that the cubeScene does not need a shader
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)cubeSceneWidth / (GLfloat)cubeSceneHeight, 0.1f, 100.0f);
        glLoadMatrixf(glm::value_ptr(projectionMatrix));

        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, bounceFunction((GLfloat)SDL_GetTicks() / 1000.0f,height));
        if(rotationSpeed>37.5f){rotationSpeed -= (GLfloat)SDL_GetTicks() / 1000.0f;}
        if(rotationSpeed>7.5f){rotationSpeed -= (GLfloat)SDL_GetTicks() / 10000.0f;}
        if(!stopFlag) rotationAngle = (GLfloat)SDL_GetTicks() / 100.0f * rotationSpeed; //problem is this line cannot be easily adjusted to other modes of control
        glRotatef(rotationAngle, Axis[axisMode*3], Axis[axisMode*3 + 1], Axis[axisMode*3 + 2]); // Rotate the cube
        totalRotationAngle += rotationAngle;
        if(totalRotationAngle/100 >= 540){  //540, 720, 960 good
            rotationSpeed=0;
            stopFlag = true;
            if(logFlag){
                LOG("end angle: "<<totalRotationAngle/100);
                LOG(callRes(std::round(totalRotationAngle/100)));
                logFlag = false;
            }
        } //stop rotation, only safe beyond 180 deg as 90 deg time window not enough
        // Draw the cube
//                            drawCube();
        standardDraw(DICE1ID, DICE2ID,DICE3ID,DICE4ID,DICE5ID,DICE6ID);
        // Swap buffers
        ////should be called by the overall render func
//        SDL_GL_SwapWindow(window);
    }

    /**
     * put constructor to the last, doen't even hurt
     */
    CubeScene(){
        DICE1ID = load_texture(DICE1); //sprite
        DICE2ID = load_texture(DICE2); //sprite
        DICE3ID = load_texture(DICE3); //sprite
        DICE4ID = load_texture(DICE4); //sprite
        DICE5ID = load_texture(DICE5); //sprite
        DICE6ID = load_texture(DICE6); //sprite
    }


};