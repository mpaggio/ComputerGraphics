
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "Lib.h"
#include "Structures.h"
#include "ShaderMaker.h"
#include "UserInterfaceHandler.h"
#include "GraphicInitializer.h"

//Variabili globali
unsigned int programId;
unsigned int VAO;
unsigned int VBO;
bool isMouseDown = false;
float r = 0.0, g = 0.0, b = 0.0;
Figura figure = {};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())   //se glfwInit() dà valore falso, return -1
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Abilita il double buffering */
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate(); //LIbera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea il context corrente e lo associa a wundow. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

    INIT_SHADER();

    //INIT_TRIANGLE(&figure);
    //INIT_SQUARE(&figure);
    //INIT_HEART(&figure);
    INIT_BUTTERFLY(&figure);

    INIT_VAO(&figure);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        /* Render here */
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(figure.VAO);
        glDrawArrays(figure.render, 0, figure.nVertices);  // Fa partire il processo di rendering meiante i dati che sono salvati nel VAO

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);
    glDeleteBuffers(1, &figure.VBO_vertices);
    glDeleteBuffers(1, &figure.VBO_colors);
    glDeleteVertexArrays(1, &figure.VAO);
    glfwTerminate();


    return 0;
}