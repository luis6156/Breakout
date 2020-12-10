#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "resource_manager.h"
#include "text_renderer.h"
#include <stb/stb_image.h>

#include <iostream>

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Render FPS
void renderFPS(TextRenderer *Text, double dt);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

// FPS flag
bool show_FPS = false;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Window icon
    // -----------
    GLFWimage images[1];
    images[0].pixels = stbi_load("icon/Breakout_icon_16x16.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(window, 1, images); 
    stbi_image_free(images[0].pixels);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    Breakout.Init();

    // initialize text
    TextRenderer* Text = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    Text->Load("fonts/OCRAEXT.TTF", 24);

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    int nbFrames = 0;
    int FPS = 0;
    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        double currentTime = glfwGetTime();
        nbFrames++;

        // FPS calculations
        // ----------------
        if (currentTime - lastTime >= 1.0)
        {
            FPS = nbFrames;
            nbFrames = 0;
            lastTime += 1.0;
        }

        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        Breakout.ProcessInput(deltaTime);

        // update game state
        // -----------------
        Breakout.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();
        
        // Show FPS
        // --------
        if (show_FPS)
            renderFPS(Text, 1000.0 / FPS);

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && Breakout.State == GAME_MENU)
        glfwSetWindowShouldClose(window, true);
    // Disable VSYNC
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        glfwSwapInterval(0);
    // Enable VSYNC
    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
        glfwSwapInterval(1);
    // Enable/Disable FPS counter
    if (key == GLFW_KEY_8 && action == GLFW_PRESS)
        show_FPS = !show_FPS;
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            Breakout.Keys[key] = false;
            Breakout.KeysProcessed[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void renderFPS(TextRenderer *Text, double dt)
{
    // render FPS
    std::stringstream FPS; FPS << (1.0 / dt * 1000.0);
    Text->RenderText("FPS: " + FPS.str(), SCREEN_WIDTH - 90.0f, 10.0f, 0.7f);
    // render ms/frames
    std::stringstream msf; msf << (float)dt;
    Text->RenderText("ms/frames: " + msf.str(), SCREEN_WIDTH - 190.0f, 30.0f, 0.7f);
}
