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
//Variabili globali -------------------------------------------------------------------
unsigned int programId, programIdS, programId_text;
float r = 0.0, g = 0.2, b = 1.0;
float alpha;
double mousex,mousey;
int height=1000, width=1000;
int frame;
int i, j;
Figura cerchio = { }, butterfly = { }, heart = { }, background = {}; //crea una nuova istanza della struttura Figura di nome   "cerchio ", "butterfly" ed "heart"
vec2 resolution;
Curva  player = { };
Curva proiettile = { };
mat4 Projection;
GLuint MatProj, MatModel, MatProjS, MatModelS, vec_resS,loc_time;
GLuint loc_numberOfClouds, loc_cloudDensity;
unsigned int VAO_Text, VBO_Text;

bool show_bounding_boxes = false;
int nClouds;
float angolo = 0.0;
float w_update, h_update;

float deltaTime = 0.0f;
float lastFrame;

 
//----------------------------------------------------------------------------------------

vector<Figura> Scena;
 

int main(void)
{
    GLFWwindow* window;
    

    /* Initialize the library */
    if (!glfwInit())   //se glfwInit() dà valore falso, return -1
        return -1;

    //Imposta le proprietà del contesto e del profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Abilita il double buffering

    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(height,width, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea il context corrente e lo associa a window. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

    
    //verifica se la libreria GLAD è riuscita a caricare correttamente tutti i puntatori 
    // alle funzioni OpenGL necessarie.

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    //Registrazione delle funzioni di callback che verranno chiamate quando si verificano
   //  determinati eventi

   //Implementa la chiusura dell'applicazione premendo il tasto Esc  e la modifica del colore dello sfondo con il tasto F2..
     glfwSetKeyCallback(window, key_callback);

   //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    glfwSetCursorPosCallback(window, cursor_position_callback);



    //per visualizzare le dimensioni della finestra ridimensionata

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    INIT_SHADER();
    
    //Init VAO per la gestione del disegno

 

    // PLAYER (BARCA)
    player.programId = programId;
    player.position.x = width / 2.0;
    player.position.y = height / 3.0;
    player.scale = vec3(180.0, 180.0, 1.0);
    INIT_FORMA(&player);
    INIT_VAO_Curva(&player);
 
    // PROIETTILE COME CURVA
    proiettile.programId = programId;
    proiettile.position.x = 0.0;
    proiettile.position.y = 0.0;
    INIT_PROIETTILE(&proiettile);
    INIT_VAO_Curva(&proiettile);

    background.nTriangles = 2;
    background.progamId = programIdS;
    background.scale = vec3(2.0*float(width),2.0*float(height), 1.0);
  
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);
    

     
    //Costruisce i vertici del cerchio: attributo posizione e color
    heart.nTriangles = 30;
    heart.progamId = programId;
    heart.isalive = true;
    heart.scale = vec3(30.0, 30.0, 1.0);
     
    INIT_HEART(0.0,0.0,0.09,0.09, &heart);
    heart.timerFig = 0.0;
    //Genera il VAO della struttura  cerchio
    INIT_VAO(&heart);
     
    //Aggiunge al vector Scena la struttura di tipo Figura cerchio
    Scena.push_back(heart);
    
    //Costruisce i vertici di butterfly: attributo posizione e color
    butterfly.nTriangles = 30;
    butterfly.progamId = programId;
    butterfly.isalive = true;
    butterfly.scale = vec3(150.0, 150.0, 1.0);
    butterfly.timerFig = 0.0;
    INIT_BUTTERFLY(0.0,0.0, 0.1, 0.1, &butterfly);
   
    //Genera il VAO della struttura  butterfly
    INIT_VAO(&butterfly);

    //Aggiunge al vector Scena la struttura di tipo Figura butterfly
    
    Scena.push_back(butterfly);
   
   

    //Registrazione delle funzioni di callback che verranno chiamate quando si verificano
    //  determinati eventi

    //Implementa la chiusura dell'applicazione premendo il tasto Esc  e la modifica del colore dello sfondo con il tasto F2..
    glfwSetKeyCallback(window, key_callback);

    //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    glfwSetCursorPosCallback(window, cursor_position_callback);

    //Per visualizzare le coordinate individuate dal tasto sinistro premuto
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    //per visualizzare le dimensioni della finestra ridimensionata

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
   
    MatProjS = glGetUniformLocation(programIdS, "Projection");
    MatModelS = glGetUniformLocation(programIdS, "Model");
    vec_resS = glGetUniformLocation(programIdS, "resolution");
    loc_time = glGetUniformLocation(programIdS, "time");
    loc_numberOfClouds = glGetUniformLocation(programIdS, "numberOfClouds");
    /* Loop until the user closes the window */

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
    
     Initialize_IMGUI(window);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        frame++;
        /* Render here */
        my_interface();
        render(currentFrame, frame);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Renderizza i dati di disegno di ImGui

       /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //close_GUI();

    glDeleteProgram(programId);
    glDeleteProgram(programIdS);
    for (i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }

    glfwTerminate();


    return 0;
}

 


 
 