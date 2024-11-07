#pragma once 
#include <fstream>
#include "lib.h"
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include "strutture.h"
#include "gestione_curve.h"
#include "inizializzazioni_ese6.h"
#pragma warning(disable:4996)
#include <math.h>

//extern ImVec4 clear_color;
 
 extern float clear_color[3];
 extern int Mod, selected_point;
 extern bool visualizzaTg, modTg;
 extern Curva curva;
 extern float* t;
 extern float Tens, Bias, Cont;
//bool my_tool_active = true;
void Initialize_IMGUI(GLFWwindow* window){

        IMGUI_CHECKVERSION(); // Verifica la compatibilità della versione di ImGui

        // Create ImGui context
        ImGui::CreateContext(); // Crea un nuovo contesto ImGui

        // Get ImGui IO object to configure options
        ImGuiIO& io = ImGui::GetIO(); // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
        io.FontGlobalScale =2.0f;  //Dimensione del font
        // Set dark theme
        ImGui::StyleColorsDark(); // Imposta il tema scuro per l'interfaccia

        // Initialize ImGui for GLFW and OpenGL 3.3
        ImGui_ImplGlfw_InitForOpenGL(window, true); // Inizializza ImGui per GLFW
        ImGui_ImplOpenGL3_Init("#version 330 core"); // Inizializza ImGui per OpenGL 3.3
}
 
void my_interface( )
{
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame(); // Inizia un nuovo frame per ImGui
        ImGui::NewFrame();

        // Create a window for color settings
        ImGui::Begin("Impostazioni");
        
        ImGui::ColorEdit4("Colore di Sfondo",clear_color);
        
        ImGui::Text("Gestione dei punti");
        ImGui::RadioButton("Inserimento", &Mod, 0); ImGui::SameLine();
        ImGui::RadioButton("Modifica", &Mod, 1); ImGui::SameLine();
        ImGui::RadioButton("Elimina", &Mod, 2);
       
        if (ImGui::Button("Chiudi Forma ")) {
            int vf = curva.CP.size() - 1;

            curva.CP[vf] = curva.CP[0];
            curva.Derivata.at(vf).x = dx(0, t, Tens, Bias, Cont, &curva);
            curva.Derivata.at(vf).y = dy(0, t, Tens, Bias, Cont, &curva);


        }
       
        if (Mod ==0)
            selected_point = -1;

         ImGui::Text("Gestione Tangenti");
         ImGui::Checkbox("Visualizza Tangenti", &visualizzaTg);  ImGui::SameLine();
         ImGui::Checkbox("Modifica Tangenti", &modTg);
         
         
         if (modTg)  //Se modTg==True entra in modalità modifica
             Mod = 1;

        
         ImGui::Text("Salvataggio Dati");
         if (ImGui::Button("Salva")) {
             std::ofstream outputFile("mycurve.txt");

             if (outputFile.is_open()) {
                 for (int i = 0; i < curva.CP.size(); i++)
                     outputFile << curva.CP[i].x << "  " << curva.CP[i].y << "  " << curva.CP[i].z << std::endl;

                 outputFile.close();
                 std::cout << "Dati scritti con successo." << std::endl;
             }
         }
         ImGui::SameLine();

         if (ImGui::Button("Apri")) {
             int i;
             struct Dati {
                 float x;
                 float y;
                 float z;
             };

             FILE* file = fopen("mycurve.txt", "r");
             if (file == NULL) {
                 perror("Impossibile aprire il file");
             }

             // Vettore per memorizzare i dati
             struct Dati dati[1000]; // Supponiamo che ci siano al massimo 100 righe nel file

             int riga = 0;
             while (fscanf(file, "%f %f %f", &dati[riga].x, &dati[riga].y, &dati[riga].z) == 3) {
                 // Incrementa l'indice della riga
                 riga++;

                 // Puoi aggiungere un controllo qui per evitare il superamento dell'array dati
                 if (riga >= 1000) {
                     printf("Troppe righe nel file. L'array dati   stato completamente riempito.\n");
                     break;
                 }
             }

            

             // Chiudi il file
             fclose(file);


             for (int i = 0; i < riga; i++) {
                 curva.CP.push_back(vec3(dati[i].x, dati[i].y, dati[i].z));
                 curva.colCP.push_back(vec4(0.0, 0.0, 0.0, 1.0));
                 curva.Derivata.push_back(vec3(0.0, 0.0, 0.0));
             }
             curva.ncp = curva.CP.size();

             UPDATE_VAO_Curva(&curva);
         }

        


        ImGui::End(); // Termina la finestra

        // Render ImGui
        ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui

}
 
void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui

}
 

// Create a window called "My First Tool", with a menu bar.
//ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
 
//if (ImGui::BeginMenuBar())
//{
 //   if (ImGui::BeginMenu("File"))
 //   {
     //   if (ImGui::MenuItem("Open..", "Ctrl+O")) { } 
    //    if (ImGui::MenuItem("Save", "Ctrl+S")) { }
     //   if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
    //    ImGui::EndMenu();
    //}
    
   // ImGui::EndMenuBar();
//}
 
 