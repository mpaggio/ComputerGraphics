#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"

extern GLFWwindow* window;
 
extern bool isMouseDown;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern float angolo;
extern Figura proiettile;

void cursor_position_callback(
    GLFWwindow* window, double xpos, double ypos) {

    // Visualizza le coordinate del mouse che si muove sulla finestra grafica

    mousex = xpos;
    mousey = height-ypos;
    //std::cout << "Coordinate del mouse  : x = " << xpos << ", y = " << ypos << std::endl;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse � premuto, visualizza le coordinate del mpuse nella posizione in cui il bottone centrale
  //  del mouse � premuto.
    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        //glfwGetCursorPos � un'utilit� fornita dalla libreria GLFW che permette di recuperare la posizione attuale del cursore
        //del mouse all'interno di una finestra OpenGL.
        glfwGetCursorPos(window, &xpos, &ypos);
        mousex = xpos;
        mousey = height-ypos;
         
         //std::cout << "Coordinate del mouse tasto sinistro premuto : x = " << xpos << ", y = " << ypos << std::endl;
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

   
    case GLFW_KEY_D:
        if (action == GLFW_PRESS) {
            angolo = angolo - 10.0;
        }
        break;

    case GLFW_KEY_A:
        if (action == GLFW_PRESS) {
            angolo = angolo + 10.0;
        }
        break;

    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS) {
            proiettile.isalive = true;
        }
        break;

    default:
        break;
    }

    


}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

}


void aggiornaProiettile(Figura* proiettile) {
    if (proiettile->isalive) {
        proiettile->position.y += 20.0f;
        if (proiettile->position.y > height) {
            proiettile->position.y = 0.0f;
            proiettile->position.x = 0.0f;
            proiettile->isalive = false;
        }
    }
}
