#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int g_screenWidth = 640;
int g_screenHeight = 480;
void glfwWindowSizeCallback(GLFWwindow* ptrToWindow, int screenWidth, int screenHeight);
void glfwKeyCallback(GLFWwindow* ptrToWindow, int key, int scanmode,int action, int mode);

int main(void)
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
    GLFWwindow* pWindow = glfwCreateWindow(g_screenWidth, g_screenHeight, "Battle City", nullptr, nullptr);
    
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

    glClearColor(0, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void glfwWindowSizeCallback(GLFWwindow* ptrToWindow, int screenWidth, int screenHeight)
{
    g_screenWidth = screenWidth;
    g_screenHeight = screenHeight;
    glViewport(0, 0, g_screenWidth, g_screenHeight);
}

void glfwKeyCallback(GLFWwindow* ptrToWindow, int key, int scanmode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(ptrToWindow, GLFW_TRUE);

}
