#pragma once 
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h" 
#include <math.h>



extern bool show_bounding_boxes;



void Initialize_IMGUI(GLFWwindow* window){

    // Verifica la compatibilità della versione di ImGui
    IMGUI_CHECKVERSION();

    // Crea un nuovo contesto ImGui
    ImGui::CreateContext();

    // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
    ImGuiIO& io = ImGui::GetIO(); 

    // Imposta il tema scuro per l'interfaccia
    ImGui::StyleColorsDark(); 

    // Inizializza ImGui per GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true); 

    // Inizializza ImGui per OpenGL 3.3
    ImGui_ImplOpenGL3_Init("#version 330 core");
}




void my_interface( ) {
        
    // Inizia un nuovo frame per ImGui
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Crea una finestra per le impostazioni dei colori
    ImGui::Begin("Impostazioni");

    // Crea una checkbox per mostrare i bounding box
    ImGui::Checkbox("Mostra Bounding Box", &show_bounding_boxes);

    // Crea uno slider per selezionare il numero di nuvole dello sfondo
    //ImGui::SliderInt("# ofClouds", &nClouds, 1,15, "%d");

    // Termina la finestra
    ImGui::End();

    // Renderizza gli elementi dell'interfaccia ImGui
    ImGui::Render();
}
 



void close_GUI() {

    // Chiude l'integrazione con OpenGL
    ImGui_ImplOpenGL3_Shutdown();

    // Chiude l'integrazione con GLFW
    ImGui_ImplGlfw_Shutdown();

    // Distrugge il contesto ImGui
    ImGui::DestroyContext();
}
 
 