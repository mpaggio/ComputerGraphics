#pragma once 
#include "lib.h"
#include "strutture.h"
#include "ImGui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <math.h>

//Variabili di tipo extern
extern float clear_color[3];
extern bool flagWf;
extern bool isNavigationMode;
extern int selected_obj;
extern bool flagAncora;
extern vector<Mesh>Scena;
extern bool moving_trackball;
extern int sceltaFs;
//Variabili locali
bool isOverImGuiElement, value;
extern string stringa_asse, Operazione;
extern vector<MaterialObj> materials;
extern vector<Shader> shaders;
extern point_light light;
void Initialize_IMGUI(GLFWwindow* window) {

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

void my_interface(GLFWwindow* window)
{

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame(); // Inizia un nuovo frame per ImGui
    ImGui::NewFrame();

    // Create a window for color settings
    ImGui::Begin("Impostazioni", NULL, //il secondo parametro viene utilizzato per controllare se la finestra dovrebbe essere aperta o chiusa. 
        // NULL significa che la finestra sarà sempre aperta.
        ImGuiWindowFlags_NoResize | //   Impedisce all'utente di ridimensionare la finestra.
        ImGuiWindowFlags_AlwaysAutoResize |  //La finestra si ridimensionerà automaticamente per adattarsi al contenuto. 
        ImGuiWindowFlags_NoBackground |  //Disabilita lo sfondo della finestra, rendendola trasparente.
        ImGuiWindowFlags_NoTitleBar |    //Nasconde la barra del titolo della finestra.
        ImGuiWindowFlags_NoMove          //Impedisce all'utente di spostare la finestra
    );
   //Introduci qui gli slider per modificare la variabile uniform della posizione della luce 

    ImGui::SliderFloat("light position x", &light.position.x, -50.0f, 50.0f);
    ImGui::SliderFloat("light position y", &light.position.y, -50.0f, 50.0f);
    ImGui::SliderFloat("light position z", &light.position.z, -50.0f, 50.0f);
    ImGui::Checkbox("Wireframe", &flagWf);
    ImGui::Checkbox("VisualizzaAncora ", &flagAncora);


  
    //Apre un menu contestuale quando si clicca con il tasto destro del mouse su un'area vuota dell'interfaccia utente di ImGui.
   
    isOverImGuiElement = ImGui::IsItemHovered();  //Bool che ha valore vero se il  mouse è attualmente posizionato su un elemento 
    //dell'interfaccia utente di ImGui., falso in caso contrario
    if (!isOverImGuiElement && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
        // Se  Il mouse non è posizionato su un elemento ImGui(!isOverImGuiElement) ed il tasto destro del mouse è stato cliccato
        ImGui::OpenPopup("ModeMenu");  //Apre un popup con l'ID "ModeMenu".
        isNavigationMode = false;  //Imposta la modalita' di navigazione a false
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  //Cambia il cursore del mouse in modalità normale.

    }

    //Se il pop-up menù è stato creato
    ;
    if (ImGui::BeginPopup("ModeMenu")) {
        //Si aggiunge un item denominato Navigazione, che, quando selezionato, mette a true la variabile booleana isNavigationMode
        if (ImGui::MenuItem("Navigazione", NULL, isNavigationMode)) {
            isNavigationMode = true;
        }
        //Si aggiunge un item denominato Interazione , che, quando selezionato, mette a flase la variabile booleana isNavigationMode
        if (ImGui::MenuItem("Interazione ", NULL, isNavigationMode)) {
            isNavigationMode = false;
            moving_trackball = false;
        }
        ImGui::EndPopup();
    }
 
 
    //Apre un menu contestuale quando si clicca con il tasto destro del mouse su un'area vuota dell'interfaccia utente di ImGui.
    isOverImGuiElement = ImGui::IsItemHovered();  //Bool che ha valore vero se il  mouse è attualmente posizionato su un elemento 
    //dell'interfaccia utente di ImGui., falso in caso contrario
    if (!isOverImGuiElement && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::GetIO().KeyShift) {
        // Se  Il mouse non è posizionato su un elemento ImGui(!isOverImGuiElement) ed il tasto destro del mouse è stato cliccato
        ImGui::OpenPopup("Opzioni");  //Apre un popup con l'ID "ModeMenu".
        //isNavigationMode = false;  //Imposta la modalita' di navigazione a false
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  //Cambia il cursore del mouse in modalità normale.

    }

    //Se il pop-up menù è stato creato, aggiungi dei sottomenu annidati
    
    if (ImGui::BeginPopup("Opzioni")) {
        //Si aggiunge un item denominato Navigazione, che, quando selezionato, mette a true la variabile booleana isNavigationMode
        
        cout <<materials[MaterialType::EMERALD].name.c_str() << endl;
        //Sottomenu I relativo ai materiali
        if (ImGui::BeginMenu("Materiali")) {
            if (ImGui::MenuItem(materials[MaterialType::EMERALD].name.c_str())) {
                if (selected_obj > -1) {
                    Scena[selected_obj].material = MaterialType::EMERALD;
                }
            }
           
            ImGui::EndMenu();
        }
        //Sottomenu 2 relativo agli shader
        if (ImGui::BeginMenu("Shader")) {
            if (ImGui::MenuItem(shaders[ShaderOption::NONE].name.c_str()))
            { 
                if (selected_obj > 1) {
                    Scena[selected_obj].sceltaShader = 0;
                }
            }
            
              
            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }
 

    
    ImGui::End(); // Termina la prima interfaccia


    // crea una piccola finestra trasparente in basso a sinistra dello schermo con testo nero, 
    // visualizzando informazioni sull'oggetto selezionato
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImVec2 leftBottom = ImVec2(windowSize.x * 0.15f, windowSize.y * 0.9f); // Posiziona l'angolo in basso a sinistra al 10% a sinistra e al 90% in basso dello schermo
    //Imposta  la posizione della prossima finestra che verrà creata: corner più in basso a sinista.
    ImGui::SetNextWindowPos(leftBottom, ImGuiCond_Always); // ImGuiCond_Always: La posizione verrà impostata sempre, indipendentemente dalle altre condizioni.
    //Visualizza le informazioni sul colore dello sfondo

    
    ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoBackground |  //Disabilita lo sfondo della finestra gui, rendendola trasparente.
        ImGuiWindowFlags_NoMove);

     if (selected_obj >= 0 && selected_obj < Scena.size()) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Oggetto Selezionato:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%s", Scena[selected_obj].nome.c_str());
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Operazione:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f),"%s", Operazione.c_str());
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "%s", stringa_asse.c_str());
        ImGui::SameLine();
        ImGui::Text("%s", Operazione);


    }
    else {
        ImGui::Text("Nessun oggetto selezionato");
    }
   
    ImGui::End(); // Termina la seconda interfaccia



    // Render ImGui
    ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui

}

void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui

}


 