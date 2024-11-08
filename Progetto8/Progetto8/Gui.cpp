#pragma once 
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
 
#include <math.h>
extern float clear_color[3];
extern bool viewLines;

void Initialize_IMGUI(GLFWwindow* window){

        IMGUI_CHECKVERSION(); // Verifica la compatibilità della versione di ImGui

        // Create ImGui context
        ImGui::CreateContext(); // Crea un nuovo contesto ImGui

        // Get ImGui IO object to configure options
        ImGuiIO& io = ImGui::GetIO(); // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
        io.FontGlobalScale = 2.0f;  //Dimensione del font

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
        ImGui::ColorEdit4("Colore di Sfondo", clear_color);
        ImGui::Checkbox("Visualizza linee", &viewLines);
 

        ImGui::End(); // Termina la finestra

        // Render ImGui
        ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui

}
 
void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui

}

 
 