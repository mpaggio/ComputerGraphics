#pragma once
#include <iostream>
#include <fstream>

#include "lib.h"
#include "strutture.h"
#include "gestione_interazioni_ese6_S.h"
#include "inizializzazioni_ese6.h"
#include "gestione_curve.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"

extern GLFWwindow* window;
extern Curva curva, Derivata;
extern float Tens, Bias, Cont;
extern float r, g, b;
extern double mousex,mousey;
extern int height, width;
extern int Mod;
extern bool modTg;
extern int selected_point;
extern float* t;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    float mousex_m, mousey_m;

    mousex = xpos;
    mousey = height - ypos;
         
    mousex_m = 2 * (mousex / width) - 1; 
    mousey_m = 2 * (mousey / height) - 1;
   
    
          if (Mod == 1 && !modTg)
          {
              
              if (selected_point >= 0)
              {
               
                  cout << mousex_m << endl;
                  cout << mousey_m << endl;
                  cout << Mod << endl;
                  curva.CP[selected_point] = vec3(mousex_m, mousey_m, 0.0);
                  curva.colCP[selected_point] = vec4(0.0, 0.0, 1.0, 1.0);
            
              }
          }
          
        
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //Se il bottone sinistro del mouse è premuto, memorizza nel campo vertices della struttura "curva" di tipo Figura, le coordinate del mouse.

    double xpos, ypos;
    float mousex_m, mousey_m;
    float dist,dist1;
    float TOLL = 5.0;
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && !ImGui::IsAnyItemHovered()) {
        if (action == GLFW_PRESS) {
            if (Mod == 1) {

                glfwGetCursorPos(window, &xpos, &ypos);
                mousex = xpos;
                mousey = height - ypos;
                mousex_m = 2.0 / (float)(width) * mousex - 1;
                mousey_m = 2.0 / (float)(height) * mousey - 1;
                vec2 mousepos = vec2(mousex_m, mousey_m);
                dist = 1000;
                for (int i = 0; i < curva.ncp; ++i) {
                    vec2 vertice = vec2(curva.CP[i].x, curva.CP[i].y);
                    dist1 = glm::distance(mousepos, vertice);
                    if (dist1 < dist) {
                        selected_point = i;
                        dist = dist1;
                    }
                }
                //Ogni volta che seleziono un vertice annullo i suoi Tens, Cont e Bias.
                Tens = 0.0;
                Cont = 0.0;
                Bias = 0.0;

                cout << "Selected Point in Mouse " << endl;
                cout << selected_point << endl;
                if (dist > TOLL)
                    selected_point = -1;
            }
                
            else if (Mod == 0) {

                    glfwGetCursorPos(window, &xpos, &ypos);
                    mousex = xpos;
                    mousey = height - ypos;
                    mousex_m = 2.0 / (float)(width)*mousex - 1;
                    mousey_m = 2.0 / (float)(height)*mousey - 1;
                  

                    //Memorizzo il vertice del mouse nel campo vertices della struttura curva
                    curva.CP.push_back(vec3(mousex_m, mousey_m, 0.0));
                   
                    //Assegno il colore a dogni vertice
                    curva.colCP.push_back(vec4(1.0, 1.0, 0.0, 1.0));
                    curva.Derivata.push_back(vec3(0.0, 0.0, 0.0));
                    curva.ncp = curva.CP.size();
                    
                    UPDATE_VAO_Curva(&curva);
                }

            else if (Mod == 2)
            {
                //Elimino l'ultimo vertice di controllo introdotto.
                if (!curva.CP.empty()) {
                    curva.CP.pop_back();
                    curva.colCP.pop_back();
                }
            }
            
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        Mod = 0;  //Torno in modalità inserisce e confermo la posizone del vertice dopo lo spostamento
}
 
    void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {

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
        
        default:

            break;
        }


 

    }



void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{

    

    
}





 
