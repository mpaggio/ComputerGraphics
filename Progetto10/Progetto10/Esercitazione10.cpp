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
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Gui.h"
#include <math.h>
#define PI 3.14159265358979323
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//Gestion Variabili uniform
unsigned int programId;
unsigned int MatProj, MatModel, MatView;
unsigned int loc_sceltaShader, loc_view_pos;

float clear_color[3] = { 0.0,0.0,0.0 };
int sceltaFs = 0;
 
int height =  800, width =  800;

//Gestione Telecamera e Prospettiva
mat4 Projection, View;

ViewSetup SetupTelecamera;
PerspectiveSetup SetupProspettiva;


//geometria della scena
Mesh cubo = {}, piano = {}, cono = {}, sfera = {}, toro = {};
vector<Mesh> Scena;
//Un modello di tipo Obj è formato da diversi obj
vector<MeshObj> Model3D;
 
//
vector<vector<MeshObj>> ScenaObj; //ScenaObj è una variabile che contiene una collezione di vettori
//dove ogni vettore contiene oggetti di tipo MeshObj

point_light light;
vector<MaterialObj> materials;
vector<Shader> shaders;
LightShaderUniform light_unif = {};


string Meshdir = "Meshes/";

//Interfaccia
bool flagWf = false;
bool flagAncora = false;
 
 
float w_up, h_up;  //Larghezza ed altezza della finestra dopo l'aggiornamento da parte dell'utente

//Per la gestione dell'animazione
float frame = 0.0;
float cameraSpeed = 0.05;


int selected_obj = -1;  //Variabile che contiene l'indice dell'oggetto selezionato nella scena
 




int main(void)
{
    GLFWwindow* window;
    int i;

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
    window = glfwCreateWindow(height, width, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create the window !" << std::endl;
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

    
    
    INIT_SHADER();
    INIT_CAMERA_PROJECTION();
    INIT_Illuminazione();

    //Inizializza la geometria del cubo e la sua matrice di modellazione
    crea_cubo(&cubo);
    cubo.Model = mat4(1.0);
    cubo.Model = translate(cubo.Model, vec3(3.5, 2.0, 2.5));
    cubo.Model = scale(cubo.Model, vec3(2.0f, 2.0f, 2.0f));
    cubo.Model = rotate(cubo.Model, radians(10.0f), vec3(0.0, 1.0, 0.0));
    cubo.nome = "Cubo";
    cubo.sceltaShader = 1;
    cubo.material = MaterialType::EMERALD;
     
    //Genera il VAO del cubo
    INIT_VAO(&cubo);
    Scena.push_back(cubo);
    
    //Inizializza la geometria del piano e la sua matrice di modellazione
    crea_piano_suddiviso(&piano,vec4(1.0,1.0,0.0,1.0));
    piano.Model = mat4(1.0);
    piano.Model = rotate(piano.Model, radians(1.5f), vec3(1.0, 0.0, 0.0));
    piano.Model = scale(piano.Model, vec3(100.0f, 1.0f, 100.0f));
    piano.nome = "Piano";
    piano.sceltaShader = 1;
    piano.material = MaterialType::BROWN;
    
    //Genera il VAO del piano
    INIT_VAO(&piano);
    Scena.push_back(piano);

    //Inizializza la geometria della piramide e la sua matrice di modellazione
  
    crea_cono(&cono,vec4(0.0,1.0,0.0,1.0));
    cono.Model = mat4(1.0);
    cono.Model = translate(cono.Model, vec3(-2.5, 1.2, 12.0));
    cono.Model = scale(cono.Model, vec3(1.2, 1.5, 1.2));
    cono.Model = rotate(cono.Model, radians(180.0f), vec3(1.0, 0.0, 0.0));
    cono.nome = "Cono";
    cono.sceltaShader = 1;
    cono.material = MaterialType::RED_PLASTIC;
    
    //Genera il VAO del cono
    INIT_VAO(&cono);
    Scena.push_back(cono);
    
    //Inizializza la geometria della sfera e la sua matrice di modellazione
    crea_sfera(&sfera,vec4(0.6,1.0,0.5,1.0));
    sfera.Model = mat4(1.0);
    sfera.Model = translate(sfera.Model, vec3(3.5, 5.5, 2.5));
    sfera.Model = scale(sfera.Model, vec3(1.5, 1.5, 1.5));
    sfera.nome = "Sfera";
    sfera.sceltaShader = 1;
    sfera.material = MaterialType::SNOW_WHITE;

    //Genera il VAO della sfera
    INIT_VAO(&sfera);
    Scena.push_back(sfera);


    //Inizializza la geometria del toro e la sua matrice di modellazione
    crea_toro(&toro,vec4(0.0,0.0,1.0,0.8));
    toro.Model = mat4(1.0);
    toro.Model = translate(toro.Model, vec3(-2.0, 2.0, 2.5));
    toro.Model = rotate(toro.Model, radians(90.0f), vec3(1.0, 0.0, 0.0));
    toro.Model = scale(toro.Model, vec3(1.5, 0.5, 1.5));
    toro.nome = "Toro";
    toro.sceltaShader = 1;
    toro.material = MaterialType::PINK;

    //Genera il VAO del toro
    INIT_VAO(&toro);
    Scena.push_back(toro);


    
    // PIPER
    add_obj("piper_pa18.obj", vec3(-2.0, 12.0, 0.0), vec3(6.0, 6.0, 6.0),180.0f,vec3(0.0,1.0,0.0));
    ScenaObj.push_back(Model3D);
    clear_objModel(&Model3D);

    // CHARIZARD
    add_obj("Shelby.obj", vec3(8.0, 2.0, 0.0), vec3(2.0, 2.0, 2.0), 0.0f, vec3(0.0, 1.0, 0.0));
    ScenaObj.push_back(Model3D);
    clear_objModel(&Model3D);


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

    // Imposta la callback per gli eventi della rotellina
    glfwSetScrollCallback(window, scroll_callback);

    //Ricava dal program shader (identificato da programId) le locations delle variabili uniform

    Projection = ortho(0.0f, float(width), 0.0f, float(height));
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
    MatView= glGetUniformLocation(programId, "View");
    loc_sceltaShader = glGetUniformLocation(programId, "sceltaShader");
    loc_view_pos = glGetUniformLocation(programId, "ViewPos");

    //location delle variabili uniformi per la gestione della luce
    light_unif.light_position_pointer = glGetUniformLocation(programId, "light.position");
    light_unif.light_color_pointer = glGetUniformLocation(programId, "light.color");
    light_unif.light_power_pointer = glGetUniformLocation(programId, "light.power");

    //location delle variabili uniformi per la gestione dei materiali
    light_unif.material_ambient = glGetUniformLocation(programId, "material.ambient");
    light_unif.material_diffuse = glGetUniformLocation(programId, "material.diffuse");
    light_unif.material_specular = glGetUniformLocation(programId, "material.specular");
    light_unif.material_shininess = glGetUniformLocation(programId, "material.shininess");

    //Abilita il test di profondità.

    glEnable(GL_DEPTH_TEST);


    /* Loop until the user closes the window */

    // Imposta la posizione iniziale del mouse
    int oX = int(float(width) / 2.0);
    int oY = int(float(height) / 2.0);

    // Imposta il cursore in posizione (0,0) e disabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, oX, oY);
    //Riabilita il movimento naturale
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    glfwSetCursorPosCallback(window, cursor_position_callback);

    //Per impostare la trasparenza ed il blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Inizializza IMGUI

    Initialize_IMGUI(window);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        frame+=1.0;
        /* Render here */
        my_interface(window);
        
        glClearColor(clear_color[0],clear_color[1],clear_color[2], 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        //Imposto la matrice di proiezione per la scena da disegnare
        Projection = perspective(radians(SetupProspettiva.fovY), SetupProspettiva.aspect, SetupProspettiva.near_plane, SetupProspettiva.far_plane);
        
        //Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
        View = lookAt(vec3(SetupTelecamera.position), vec3(SetupTelecamera.target), vec3(SetupTelecamera.upVector));

        //Passo al Vertex Shader il puntatore alla matrice View, che sarà associata alla variabile Uniform mat4 Projection
       //all'interno del Vertex shader. Uso l'identificatio MatView
        glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));
        //La matrice di proiezione che mappa il volume di vista in coordinate NDC
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
    
        //flagWf: se true viene fatta la visualizzazione wireframe
        if (flagWf == true)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        //To DO
        //Passa allo shader il puntatore alle informazioni sulla luce
        glUniform3f(light_unif.light_position_pointer, light.position.x, light.position.y, light.position.z);
        glUniform3f(light_unif.light_color_pointer, light.color.x, light.color.y, light.color.z);
        glUniform1f(light_unif.light_power_pointer, light.power);

        //Passa allo shader il puntatore alla posizione della camera
        glUniform3f(loc_view_pos, SetupTelecamera.position.x, SetupTelecamera.position.y, SetupTelecamera.position.z);
        
        for (i=0; i<Scena.size();i++)
        {
            glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
            glBindVertexArray(Scena[i].VAO);

            update_ancora(&Scena[i]);
            ///La funzione glDrawElements è uno strumento fondamentale in OpenGL per rendere primitive grafiche (come triangoli, linee o punti) 
            // utilizzando dati di vertici memorizzati in buffer di vertici (VBO) e indicizzati da un buffer di elementi (EBO).
            //Utilizzando gli indici, possiamo ottimizzare il processo di rendering e creare geometrie complesse con meno dati di vertici.
            //GL_TRIANGLES: Questo parametro specifica il tipo di primitiva da rendere.In questo caso, stiamo rendendo dei triangoli.
            //(cubo.indices.size() - 1) * sizeof(GLuint) : Questo calcola il numero di indici da disegnare.Il termine cubo.indices.size() indica il numero totale di indici, ma sottraiamo 1 perché gli indici sono spesso memorizzati a coppie o triple per definire i triangoli.Moltiplicando per sizeof(GLuint) otteniamo la dimensione in byte.
            //GL_UNSIGNED_INT : Questo specifica il tipo di dato degli indici nel buffer di elementi.In questo caso, sono interi senza segno.
            //0 : Questo è l'offset in byte all'interno del buffer di elementi.In questo caso, iniziamo dall'inizio.
            //Utilizzando gli indici, possiamo ottimizzare il processo di rendering e creare geometrie complesse con meno dati di vertici
        

            glUniform1i(loc_sceltaShader, Scena[i].sceltaShader);

            //Assegnare i valori alle varibili uniformi
            glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(materials[Scena[i].material].ambient));
            glUniform3fv(light_unif.material_diffuse, 1, glm::value_ptr(materials[Scena[i].material].diffuse));
            glUniform3fv(light_unif.material_specular, 1, glm::value_ptr(materials[Scena[i].material].specular));
            glUniform1f(light_unif.material_shininess, materials[Scena[i].material].shininess);

            glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[i].Model));
            glBindVertexArray(Scena[i].VAO);
            glDrawElements(GL_TRIANGLES, (Scena[i].indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
            if (flagAncora)
            {
                glPointSize(15.0);
                int ind = Scena[i].indices.size() -1;
                glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));
            }
            glBindVertexArray(0);
        }
         
        // Disegna la scena formata da Mesh obj
        for (i = 0; i < ScenaObj.size(); i++) {

            for (int k = 0; k < ScenaObj[i].size(); k++)
            {

                glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(ScenaObj[i][k].Model));
                glUniform1i(loc_sceltaShader, 1);
                
                //To DO
                //Passo allo shader il puntatore ai materiali
                glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(ScenaObj[i][k].materiale.ambient));
                glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(ScenaObj[i][k].materiale.diffuse));
                glUniform3fv(light_unif.material_ambient, 1, glm::value_ptr(ScenaObj[i][k].materiale.specular));
                glUniform1f(light_unif.material_shininess, ScenaObj[i][k].materiale.shininess);

                glBindVertexArray(ScenaObj[i][k].VAO);

            
                glDrawElements(GL_TRIANGLES, (ScenaObj[i][k].indices.size()) * sizeof(GLuint), GL_UNSIGNED_INT, 0);


                glBindVertexArray(0);
            }
        }
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Renderizza i dati di disegno di ImGui

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

     close_GUI();

    glfwTerminate();


    return 0;
}





