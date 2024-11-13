#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"


// ...................... VARIABILI GLOBALI ......................
bool first_time_clicking = true;

extern int height, width;

extern float targetSpeed, speedTransitionRate;
extern float  w_update, h_update;
extern float angolo, speed;
extern float r, g, b;

extern double mousex, mousey;

extern bool isDragging;
extern bool isMouseDown;

extern mat4 Projection;

extern GLFWwindow* window;
extern Curva spezzata;
extern Curva cupola_macchina, proiettile;

// ...............................................................




void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) { 
    mousex = xpos;
    mousey = height - ypos;
          
}




void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);
        
        mousex = xpos;
        mousey = height - ypos;

        proiettile.isalive = true;

        if (first_time_clicking) {
            first_time_clicking = false;
            proiettile.position.x = cupola_macchina.position.x;
            proiettile.position.y = cupola_macchina.position.y;
        } 
    }
}




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float movement_step = 60.0f;

    switch (key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            break;
        case GLFW_KEY_A:
            if (action == GLFW_PRESS) {
                if (cupola_macchina.position.x - 3 * movement_step > 0) {
                    cupola_macchina.position.x -= movement_step;
                }
            }
            break;
        case GLFW_KEY_D:
            if (action == GLFW_PRESS) {
                if (cupola_macchina.position.x + 3 * movement_step < width) {
                    cupola_macchina.position.x += movement_step;
                }
            }
            break;
        case GLFW_KEY_S:
            if (action == GLFW_PRESS) {
                targetSpeed = 0.5f;
            }
            break;
        case GLFW_KEY_W:
            if (action == GLFW_PRESS) {
                targetSpeed = 3.0f;
            }
            break;
        case GLFW_KEY_R:
            if (action == GLFW_PRESS) {
                targetSpeed = 1.0f;
            }
            break;

        default:
            break;
    }

}




void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

    // Evitare divisioni per zero
    if (h == 0) {
        h = 1;
    }
    
    Projection = ortho(0.0f, (float)width, 0.0f, (float)height);
   
    //Rapporto larghezza altezza del  mondo
    float AspectRatio_mondo = (float)(width) / (float)(height);

    //Se ridimensioniamo la larghezza della Viewport 
    if (AspectRatio_mondo > (w / h)) {   
        
        //La larghezza del viewport è uguale alla larghezza della finestra.
        w_update = (float)w;
        
        //Il viewport viene esteso in altezza per mantenere le proporzioni corrette.
        h_update = w / AspectRatio_mondo;
    }
    else {
        
        //Il viewport viene esteso in larghezza per mantenere le proporzioni corrette
        w_update = h * AspectRatio_mondo;

        //L'altezza del viewport è uguale all'altezza della finestra.
        h_update = (float)h;
    }

    glViewport(0.0, 0.0, w_update, h_update);

}
    



void aggiornaProiettile(Figura* proiettile) {

    float vel_y_proiettile = 2.0;

    cout << "proiettile vivo: " << proiettile->isalive << endl;
    if (proiettile->isalive == true) {
        proiettile->position.y += vel_y_proiettile;

        //Controllo se il proiettile raggiunge il 
        if (proiettile->position.y > height - 100) {
            proiettile->isalive = false;
            proiettile->position.y = 0.0;
            proiettile->position.x = 0.0;
        }
    }
}



void aggiornaProiettile(Curva* proiettile) {

    float vel_y_proiettile = 0.6;

    if (proiettile->isalive == true) {
        proiettile->position.y += vel_y_proiettile;

        //Controllo se il proiettile raggiunge il 
        if (proiettile->position.y > height) {
            proiettile->isalive = false;
            proiettile->position.y = 0.0;
            proiettile->position.x = 0.0;
            first_time_clicking = true;
        }
    }
}


