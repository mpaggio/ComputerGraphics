#include <GLFW/glfw3.h>
#include <iostream>

extern GLFWwindow* window;
extern bool isMouseDown;
extern float r, g, b;

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isMouseDown = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isMouseDown = false;
    }

    std::cout << "isMouseDown " << isMouseDown << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "window size is " << width << "x" << height << std::endl;
    glViewport(0.0, 0.0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Cambia il colore dello sfondo
        r = 1.0;
        g = 1.0;
        b = 1.0;
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else {
        // Cambia il colore dello sfondo
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

}