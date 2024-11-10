#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
#include "rendering.h"
 
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#define PI 3.14159265358979323


// ........................ VARIABILI GLOBALI ........................

int height = 1000, width = 1000;
int frame;
int i, j;
int nClouds;

unsigned int programId, programIdS, programId_text;
unsigned int VAO_Text, VBO_Text;

float r = 0.0, g = 0.2, b = 1.0;
float alpha;
float angolo = 0.0;
float w_update, h_update;
float deltaTime = 0.0f;
float lastFrame;

double mousex,mousey;
bool show_bounding_boxes = false;

Figura background = {}, sfera_di_energia = {};
Curva  corpo_navicella = {}, cupola_navicella = {}, asteroide = {}, alieno = {};

GLuint MatProj, MatModel, MatProjS, MatModelS, vec_resS,loc_time;
GLuint loc_numberOfClouds, loc_cloudDensity;

mat4 Projection;
vec2 resolution;
vector<Figura> Scena;

// ..........................................................................


 

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }   

    //Imposta le proprietà del contesto e del profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Abilita il double buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Crea una finestra in modalità window e il suo contesto OpenGL
    window = glfwCreateWindow(height,width, "Hello World", NULL, NULL);
    if (!window) {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    //crea il context corrente e lo associa a window
    glfwMakeContextCurrent(window);

    //verifica se la libreria GLAD è riuscita a caricare correttamente tutti i puntatori alle funzioni OpenGL necessarie.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    
    // ........................ FUNZIONI DI CALLBACK ........................
    
    // Setta la funzione di callback per la tastiera
    glfwSetKeyCallback(window, key_callback);

    // Setta la funzione di callback per la posizione del cursore del mouse
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Setta la funzione di callback per i bottoni del mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Setta la funzione di callback per la dimensione del frame buffer
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ...........................................................................
    
    
    INIT_SHADER();


    // ........................ CREAZIONE DELLE GEOMETRIE ........................
    
    // CUPOLA NAVICELLA
    cupola_navicella.programId = programId;
    cupola_navicella.position.x = width / 2.0;
    cupola_navicella.position.y = height / 3.0;
    cupola_navicella.scale = vec3(180.0, 180.0, 1.0);
    INIT_CUPOLA_NAVICELLA(&cupola_navicella);
    INIT_VAO_Curva(&cupola_navicella);

    // CORPO NAVICELLA
    corpo_navicella.programId = programId;
    corpo_navicella.position.x = 0.0;
    corpo_navicella.position.y = 0.0;
    INIT_CORPO_NAVICELLA(&corpo_navicella);
    INIT_VAO_Curva(&corpo_navicella);

    //ALIENO
    alieno.programId = programId;
    alieno.position.x = 0.0;
    alieno.position.y = 0.0;
    INIT_ALIENO(&alieno);
    INIT_VAO_Curva(&alieno);

    // BACKGROUND
    background.nTriangles = 2;
    background.programId = programIdS;
    background.scale = vec3(2.0*float(width),2.0*float(height), 1.0);
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);

    // SFERA DI ENERGIA
    sfera_di_energia.nTriangles = 100;
    sfera_di_energia.programId = programId;
    sfera_di_energia.isalive = false;
    sfera_di_energia.scale = vec3(30.0, 30.0, 1.0);
    INIT_CIRCLE_WITH_SPIKES(0.0, 0.0, 1.5, 10, & sfera_di_energia);
    sfera_di_energia.timerFig = 0.0;
    INIT_VAO(&sfera_di_energia);
    Scena.push_back(sfera_di_energia);
    
    // .......................................................................
   


    // ............. DEFINIZIONE DELLE MATRICI DI TRASFORMAZIONE .............

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
   
    MatProjS = glGetUniformLocation(programIdS, "Projection");
    MatModelS = glGetUniformLocation(programIdS, "Model");
    
    vec_resS = glGetUniformLocation(programIdS, "resolution");
    loc_time = glGetUniformLocation(programIdS, "time");
    loc_numberOfClouds = glGetUniformLocation(programIdS, "numberOfClouds");

    // .......................................................................



    // Imposta la posizione iniziale del mouse
    int oX = int(float(width)/2.0);
    int oY = int(float(height) / 2.0);

    // Imposta il cursore in posizione (0,0) e disabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, oX, oY);
    
    //Riabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    glfwSetCursorPosCallback(window, cursor_position_callback);

    resolution= vec2(float(height), float(width));
    
    // Crea l'interfaccia grafica ImGUI per la finestra
    Initialize_IMGUI(window);

    

    // .......................... GAME LOOP .................................

    while (!glfwWindowShouldClose(window))
    {
        // Variabile del tempo corrente
        float currentFrame = glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frame++;
        
        // Renderizzazione
        my_interface();
        render(currentFrame, frame);

        // Renderizza i dati di disegno di ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Cambia il front buffer con il back buffer
        glfwSwapBuffers(window);

        // Polling di eventi
        glfwPollEvents();
    }

    // .......................................................................


    // Chiude il menu di interfaccia con l'utente
    close_GUI();

    glDeleteProgram(programId);
    glDeleteProgram(programIdS);
    
    // Disttrugge ogni elemento della scena
    for (i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }

    // Termina l'applicazione
    glfwTerminate();
    return 0;
}

 


 
 