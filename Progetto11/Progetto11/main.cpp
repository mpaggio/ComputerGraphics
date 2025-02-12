#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "geometria.h"
#include "gestione_interazioni.h"
#include "gestione_telecamera.h"
#include "utilities.h"
#include "geometria_obj.h"
#include "enum_illuminazione.h"
#include "gestioneTexture.h"
#include "rendering.h"
#include "event_management.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#include <math.h>
   
unsigned int programId, programId1, programIdr;
GLFWwindow* window;

float clear_color[3] = { 0.4,0.4,0.4 };
int height = 1280, width = 1280;

//Gestione Telecamera e Prospettiva
mat4 Projection, View;
ViewSetup SetupTelecamera;
PerspectiveSetup SetupProspettiva;
int cubemapTexture;

//geometria della scena
Mesh sky;
vector<Mesh> Scena;

// Vettore contenente una collezione di vettori, dove ogni vettore contiene oggetti di tipo MeshObj
vector<vector<MeshObj>> ScenaObj; 
 

//Luci,materiali e shaders
point_light light, light2;
vector<MaterialObj> materials;
vector<Shader> shaders;

// variabili uniform per le matrici di modellazione, di vista, posizione della telecamera e scelta_shader da utilizzare.
 Uniform uniform;

 //Uniform per la gestione dell'illuminazione
 LightShaderUniform light_unif = {}, light_unif2 = {};


string Meshdir = "Meshes/";
string Imagedir = "Textures/";
string SkyboxDir = "SkyBoxes/stars/";


 

//Interfaccia
bool flagWf = false;
bool flagAncora = false;
bool flagBV = false;
 
//Larghezza ed altezza della finestra dopo l'aggiornamento da parte dell'utente
float w_up = width, h_up = height; 

//Per la gestione dell'animazione
float frame = 0.0;
float cameraSpeed = 0.05;

//Variabile che contiene l'indice dell'oggetto selezionato nella scena
int selected_obj = -1;
int selected_obj_j = -1;

vector<string> path_texture;
vector <int> texture;


int main(void) {
    int cubemapTexture;
    
    //Inizializzazione GLFW e GLAD
    int value = INIT_GLAD_GLFW();

    string path_texture_name = Imagedir +  "grey-cement.jpg";
    path_texture.push_back(path_texture_name);
    path_texture_name = Imagedir + "rainbow_road.jpg";
    path_texture.push_back(path_texture_name);
    path_texture_name = Imagedir + "scacchi.jpg";
    path_texture.push_back(path_texture_name);
    path_texture_name = Imagedir + "muromattoni.jpg";
    path_texture.push_back(path_texture_name);

    // Inizializza la scena
    INIT_Scene(path_texture, &texture, &cubemapTexture);

    // Gestione eventi
    event_management(window);

    // Ricava dal program shader (identificato da programId) le locations delle variabili uniform
    getUniform();

    // Abilita il test di profondità.
    glEnable(GL_DEPTH_TEST);

    // Imposta la trasparenza ed il blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Inizializza IMGUI
    Initialize_IMGUI(window);

    GLint maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    std::cout << "Numero massimo di texture unit: " << maxTextureUnits << std::endl;

    /* Loop until the user closes the window */
    glViewport(0.0, 0.0, width, height);

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
         
        my_interface(window);
               
        rendering(currentFrame,uniform, light_unif, light_unif2,texture, cubemapTexture);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    close_GUI();

    glfwTerminate();

    return 0;
}