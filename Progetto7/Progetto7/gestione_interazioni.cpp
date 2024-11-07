#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"

extern GLFWwindow* window;
extern Curva proiettile;
extern Curva player,spezzata;
extern bool isMouseDown;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern float angolo;
extern mat4 Projection;
extern float  w_update, h_update;
extern bool isDragging;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
     
          mousex = xpos;
          mousey = height - ypos;
          
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse è premuto, memorizza nel campo vertices della struttura "spezzata" di tipo Figura, le coordinate del mouse.

    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);

            mousex = xpos;
            mousey = height - ypos;
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Se il tasto ESCAPE è premuto, chiude la finestra
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

    case GLFW_KEY_SPACE:
        
        if (action == GLFW_PRESS) {
            proiettile.isalive = true;
        }
        /*
        else if (action == GLFW_RELEASE) {
            proiettile.isalive = false;
            proiettile.position.y = 0.0;
            proiettile.position.x = 0.0;
        }
        */
      break;
    
    case GLFW_KEY_R:
        if (mods & GLFW_MOD_SHIFT)
             angolo = angolo + 10.0;
        else
             angolo = angolo - 10.0;
        break;
    default:

        break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
   
    
   
       // Evitare divisioni per zero
    if (h == 0) h = 1;
    
     Projection = ortho(0.0f, (float)width, 0.0f, (float)height);
   

    float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza del  mondo
    //Se l'aspect ratio del mondo   diversa da quella della finestra devo mappare in modo diverso 
    //per evitare distorsioni del disegno
    if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
    {
        //Il viewport viene esteso in altezza per mantenere le proporzioni corrette.
        //La larghezza del viewport è uguale alla larghezza della finestra.
        
        
        w_update = (float)w;
        h_update = w / AspectRatio_mondo;
    }
    else {  //Se ridimensioniamo l'altezza della viewport oppure se l'aspect ratio tra la finestra del mondo
        //e la finestra sullo schermo sono uguali

        w_update = h * AspectRatio_mondo;    //Il viewport viene esteso in larghezza per mantenere le proporzioni corrette.
                                             //L'altezza del viewport è uguale all'altezza della finestra.
        h_update = (float)h;
    }
    glViewport(0.0, 0.0, w_update, h_update);
    
     
}
    

    
 
void aggiornaProiettile(Figura* proiettile) {

    float vel_y_proiettile = 40;
    if (proiettile->isalive==true) {
        proiettile->position.y += vel_y_proiettile;  
        //Controllo se il proiettile raggiunge il bordo

        if (proiettile->position.y > height - 100) {
            proiettile->isalive == false;
            proiettile->position.y = 0.0;
            proiettile->position.x = 0.0;
        }
    }
}

void aggiornaProiettile(Curva* proiettile) {

    float vel_y_proiettile = 15;
    if (proiettile->isalive == true) {
        proiettile->position.y += vel_y_proiettile;
        //Controllo se il proiettile raggiunge il bordo
        
        if (proiettile->position.y > height - 100) {
            proiettile->isalive = false;
            proiettile->position.y = 0.0;
            proiettile->position.x = 0.0;
        }
    }
}

