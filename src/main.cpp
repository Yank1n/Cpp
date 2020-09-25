#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Resources/ResourceManager.h"

GLfloat point[]
{
    0.0f, 50.f, 0.0f,
    50.f, -50.f, 0.0f,
    -50.f, -50.f, 0.0f
};

GLfloat color[]
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCood[]
{
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

glm::ivec2 g_screenSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* ptrToWindow, int screenWidth, int screenHeight);
void glfwKeyCallback(GLFWwindow* ptrToWindow, int key, int scanmode,int action, int mode);

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed\n";

        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_screenSize.x, g_screenSize.y, "Battle City", nullptr, nullptr);
    
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed\n";

        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
	    std::cout<<"Can't load GLAD!\n";

	    return -1;
    }

    std::cout << "Render: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);

        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");

        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << "\n";

            return -1;
        }

         auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");

        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << "\n";

            return -1;
        }

        auto tex = resourceManager.loadTextures("DefaultTexture", "res/textures/map_8x8.png");

        std::vector<std::string> subTextureNames{ "block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock", "beton" };

        auto pTextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_8x8.png", std::move(subTextureNames), 8, 8);

        auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "block");
        pSprite->setPosition(glm::vec2(300.f, 100.f));

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

        GLuint texCoord_vbo = 0;
        glGenBuffers(1, &texCoord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCood), texCood, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);

        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);

        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projMatrx = glm::ortho(0.f, static_cast<float>(g_screenSize.x), 0.f, static_cast<float>(g_screenSize.y), -100.f, 100.f);

        pDefaultShaderProgram->setMatrix4("projMat", projMatrx);

        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);

        pSpriteShaderProgram->setMatrix4("projMat", projMatrx);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Use Shader code */
            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pSprite->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

void glfwWindowSizeCallback(GLFWwindow* ptrToWindow, int screenWidth, int screenHeight)
{
    g_screenSize.x = screenWidth;
    g_screenSize.y = screenHeight;
    glViewport(0, 0, g_screenSize.x, g_screenSize.y);
}

void glfwKeyCallback(GLFWwindow* ptrToWindow, int key, int scanmode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(ptrToWindow, GLFW_TRUE);
}