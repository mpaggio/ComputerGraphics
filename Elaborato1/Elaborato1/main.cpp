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

int height = 1100, width = 1100;
int frame;
int i, j;

unsigned int programId, programIdS, programId_text;
unsigned int VAO_Text, VBO_Text;

float r = 0.0, g = 0.2, b = 1.0;
float alpha;
float speed = 1.0f, targetSpeed = 1.0f, speedTransitionRate = 5.0f, minSpeed = 0.1f;
float deltaTime = 0.0f, lastFrame = 0.0f;
float w_update = height, h_update = width;

double mousex,mousey;
bool show_bounding_boxes = false, game_end = false;

Figura background = {};
Curva cupola_macchina = {}, corpo_macchina = {}, ruota_macchina = {}, proiettile = {}, macchia_fango = {}, buco_strada = {};

GLuint MatProj, MatModel, MatProjS, MatModelS, vec_resS,loc_time, loc_deltaTime;
GLint loc_speed, loc_resolution;

mat4 Projection;
vec2 resolution;
vector<Figura> Scena;

GLFWwindow* window;

// ..........................................................................


 

int main(void) {

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
    
    // CUPOLA MACCHINA
    cupola_macchina.programId = programId;
    cupola_macchina.position.x = width / 2.0;
    cupola_macchina.position.y = height / 3.0;
    cupola_macchina.scale = vec3(120.0, 120.0, 1.0);
    INIT_CUPOLA_MACCHINA(&cupola_macchina);
    INIT_VAO_Curva(&cupola_macchina);

    // CORPO MACCHINA
    corpo_macchina.programId = programId;
    corpo_macchina.position.x = 0.0;
    corpo_macchina.position.y = 0.0;
    INIT_CORPO_MACCHINA(&corpo_macchina);
    INIT_VAO_Curva(&corpo_macchina);

    // RUOTA MACCHINA
    ruota_macchina.programId = programId;
    ruota_macchina.position.x = 0.0;
    ruota_macchina.position.y = 0.0;
    INIT_RUOTA_MACCHINA(&ruota_macchina);
    INIT_VAO_Curva(&ruota_macchina);

    // PROIETTILE
    proiettile.programId = programId;
    proiettile.position.x = 0.0;
    proiettile.position.y = 0.0;
    INIT_PROIETTILE(&proiettile);
    INIT_VAO_Curva(&proiettile);

    // BACKGROUND
    background.nTriangles = 2;
    background.programId = programIdS;
    background.scale = vec3(2.0*float(width),2.0*float(height), 1.0);
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);

    // BUCO STRADA
    buco_strada.programId = programId;
    buco_strada.position = randomPosition(width, height);
    INIT_BUCO_STRADA(&buco_strada);
    INIT_VAO_Curva(&buco_strada);

    // MACCHIA FANGO
    macchia_fango.programId = programId;
    macchia_fango.position = randomPosition(width, height);
    while (fabs(macchia_fango.position.x - buco_strada.position.x) < 100.0f) {
        macchia_fango.position = randomPosition(width, height);
    }
    INIT_MACCHIA_FANGO(&macchia_fango);
    INIT_VAO_Curva(&macchia_fango);
    
    // .......................................................................
   


    // ............. DEFINIZIONE DELLE MATRICI DI TRASFORMAZIONE .............

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
   
    MatProjS = glGetUniformLocation(programIdS, "Projection");
    MatModelS = glGetUniformLocation(programIdS, "Model");
    
    vec_resS = glGetUniformLocation(programIdS, "resolution");
    loc_time = glGetUniformLocation(programIdS, "time");
    loc_speed = glGetUniformLocation(programIdS, "speed");
    loc_resolution = glGetUniformLocation(programIdS, "resolution");
    loc_deltaTime = glGetUniformLocation(programIdS, "deltaTime");

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
        if (game_end) {
            displayEndGame();
        }
        else {
            my_interface();
            render(currentFrame, frame);
        }

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

 


 
 