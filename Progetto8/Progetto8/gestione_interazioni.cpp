#pragma once
#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni.h"

extern GLFWwindow* window;
extern mat4 Projection;
extern int height, width;
extern PerspectiveSetup SetupProspettiva;
extern ViewSetup SetupTelecamera;
extern float w_up, h_up;

 
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
     
         
          
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse è premuto, memorizza nel campo vertices della struttura "spezzata" di tipo Figura, le coordinate del mouse.

    double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);

        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
    float cameraSpeed = 0.01f;

    // Se il tasto ESCAPE è premuto, chiude la finestra
    switch (key) {

        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS)
                //Imposta a True il flag booleano di chiusura della finestr
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

        case GLFW_KEY_W:
            if (action == GLFW_PRESS) {
                SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
                SetupTelecamera.position += SetupTelecamera.direction * cameraSpeed;
            }
            break;

        case GLFW_KEY_A:
            if (action == GLFW_PRESS)
                SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
                vec3 slide_vector2 = cross(SetupTelecamera.direction, SetupTelecamera.upVector);
                SetupTelecamera.position += slide_vector2 * cameraSpeed;
                SetupTelecamera.target += slide_vector2 * cameraSpeed;
                break;

        case GLFW_KEY_S:
            if (action == GLFW_PRESS)
                SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
                SetupTelecamera.position -= SetupTelecamera.direction * cameraSpeed;
                break;

        case GLFW_KEY_D:
            if (action == GLFW_PRESS)
                SetupTelecamera.direction = SetupTelecamera.target - SetupTelecamera.position;
                vec3 slide_vector = cross(SetupTelecamera.direction, SetupTelecamera.upVector);
                SetupTelecamera.position -= slide_vector * cameraSpeed;
                SetupTelecamera.target -= slide_vector * cameraSpeed;
                break;

        default:

            break;
    }

}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

    //Imposto la matrice di proiezione per la scena da diegnare
    

    float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza di tutto ciò che è nel mondo
    //Se l'aspect ratio del mondo è diversa da quella della finestra devo mappare in modo diverso 
    //per evitare distorsioni del disegno
    if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
    {
       
        w_up = (float)w;
        h_up = w / AspectRatio_mondo;
    }
    else {  //Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo 
        //e la finestra sullo schermo sono uguali
        glViewport(0, 0, h * AspectRatio_mondo, h);
        w_up = h * AspectRatio_mondo;
        h_up = (float)h;
    }
    glViewport(0, 0, w_up, h_up);
}

    
 

