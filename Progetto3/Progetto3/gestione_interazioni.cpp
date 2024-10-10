#pragma once
#include "lib.h"


extern GLFWwindow* window;
extern bool isMouseDown;
extern float r, g, b;
extern double xpos, ypos;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

    // Visualizza le coordinate del mouse che si muove sulla finestra grafica

    std::cout << "Px: " << xpos << " y: " << ypos << std::endl;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse � premuto, visualizza le coordinate del mpuse nella posizione in cui il bottone centrale
  //  del mouse � premuto.

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        //glfwGetCursorPos � un'utilit� fornita dalla libreria GLFW che permette di recuperare la posizione attuale del cursore
        //del mouse all'interno di una finestra OpenGL.
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Coordinate del mouse tasto sinistro premuto : x = " << xpos << ", y = " << ypos << std::endl;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE � premuto, chiude la finestra
    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
            //Imposta a True il flag booleano di chiusura della finestr
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    case GLFW_KEY_F2:
        if (action == GLFW_PRESS) {
            r = 1.0;
            g = 0.0;
            b = 0.0;
        }
        //Quando il testo F2 viene rilasciato lo sfondo riassume colore verde
        else if (action == GLFW_RELEASE) {
            r = 0.0;
            g = 1.0;
            b = 0.0;
        }
        break;

    default:

        break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //  Stampa le dimensioni della finestra ridimensionata
    std::cout << "Dimensione finestra larghezza: " << width << " altezza " << height << std::endl;
}