#include <iostream>

#include "ao/ui/window.hpp"
#include "ao/core/tree.hpp"

#include "ao/gl/shaders.hpp"
#include "ao/gl/frame.hpp"

bool Window::Show(Tree* tree)
{
    (void)tree;

    // Initialize the library
    if (!glfwInit())
    {
        return NULL;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);    // multisampling!
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* const window = glfwCreateWindow(
            600, 400, "ao", NULL, NULL);

    if (!window)
    {
        std::cerr << "Error: failed to create window!" << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    auto win = new Window(window);
    win->run();
    delete win;

    return true;
}

////////////////////////////////////////////////////////////////////////////////

Window::Window(GLFWwindow* window)
    : window(window), frame(new Frame())
{
    // Nothing to do here
}

void Window::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
}