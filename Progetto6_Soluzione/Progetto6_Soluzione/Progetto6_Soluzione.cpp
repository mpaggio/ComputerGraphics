#include <fstream>
#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni_ese6.h"
#include "gestione_curve.h"
#include "gestione_interazioni_ese6.h"
 
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

 
#include "Gui.h"

#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId;
float r = 0.0, g = 0.2, b = 1.0;
float alpha;
double mousex,mousey;
int height=1000, width=1000;
int Mod;
bool modTg;
float* t;
Curva curva = {},assi = {};//crea una nuova istanza della struttura curva di nome  "curva" e degli assi
int selected_point=-1;
int i,j;
mat4 Projection;
GLuint MatProj, MatModel, loc_flagP;
bool visualizzaTg;
float clear_color[3] = { 0.0,1.0,0.0 };
float step_t;
float Tens=0.0, Bias=0.0, Cont=0.0;
//----------------------------------------------------------------------------------------

void crea_assi(void)
{
    assi.ncp = 4;
    assi.nv = 1;
    assi.ntg = 1;
    assi.CP.push_back(vec3(0.0f, 1.0f, 0.0f));
    assi.CP.push_back(vec3(0.0f, -1.0f, 0.0f));
    assi.CP.push_back(vec3(-1.0f, 0.0f, 0.0f));
    assi.CP.push_back(vec3(1.0f, 0.0f, 0.0f));
    assi.colCP.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    assi.colCP.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    assi.colCP.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    assi.colCP.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
    INIT_VAO_Curva(&assi);
}
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
    
    //Registrazione delle funzioni di callback che verranno chiamate quando si verificano
   //  determinati eventi

   //Implementa la chiusura dell'applicazione premendo il tasto Esc  e la modifica del colore dello sfondo con il tasto F2..
     glfwSetKeyCallback(window, key_callback);

   //Per visualizzare le coordinate del mouse che si muove sulla finestra grafica
    glfwSetCursorPosCallback(window, cursor_position_callback);



    //per visualizzare le dimensioni della finestra ridimensionata

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    INIT_SHADER();
    

 

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

    //Projection = ortho(0.0f, float(width), 0.0f, float(height));
    Projection = ortho(-1.0f, 1.0f, -1.0f, 1.0f);

  
    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");
    loc_flagP= glGetUniformLocation(programId, "flagP");  //flagP: flag per scegliere se visualizzare i punti di controllo CP, la curva valutata , le tangenti nei vertici di controllo

    /* Loop until the user closes the window */

    //Inizializzazione di un VAO per la curva, con un VBO inizializzato a NULL con un massimo di 100 posizioni, di tipi GL_DYNAMIC_DRAW

    curva.ncp = 100;
    curva.nv = 200;
    curva.ntg = 200;

    INIT_VAO_DYNAMIC_Curva(&curva);

    Initialize_IMGUI(window);   //Inizializza l'interfaccia

    while (!glfwWindowShouldClose(window))
    {
        
        
        glClearColor(clear_color[0],clear_color[1], clear_color[2],1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(programId);

        my_interface();  //Design dell'interfaccia
        
        //Assi nella finestra grafica
        crea_assi();
        assi.Model = mat4(1.0);
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        //Le coordinate dei vertici della psezzta sono già nelle coordinate del mondo, quindi  curva.Model = mat4(1.0);
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(curva.Model));
        glUniform1i(loc_flagP, 1);
        glPointSize(4.0);
        glLineWidth(2.0);
        
        glBindVertexArray(assi.VAO);
        glDrawArrays(GL_LINES, 0, assi.CP.size());  //curva con i vertici in ordine di inserimento
        glBindVertexArray(0);
        

        //Disegno vertici di controllo della curva (via via che vengono selezionati con il mouse)
        glPointSize(4.0); //Dimensione dei punti
        glLineWidth(2.0); //Spessori della linea

        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));  
        curva.Model = mat4(1.0);
        //Le coordinate dei vertici della spezzata sono già nelle coordinate del mondo, quindi  curva.Model = mat4(1.0);
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(curva.Model));
        glUniform1i(loc_flagP, 1);   //Se flagP=1, vengono disegnati i vertici di controllo della curva
         glBindVertexArray(curva.VAO);
        glDrawArrays(GL_LINE_STRIP, 0, curva.CP.size());  //Disegna i vertici di controllo della curva come punti isolati
        glDrawArrays(GL_POINTS, 0, curva.CP.size());
        //Visualizzazione dei vertici come punti
        glBindVertexArray(0);

      //Se il numero dei vertici di controllo (CP) è maggiore di 2, calcola la curva di Hermite che li interpola.
      if (curva.CP.size()>2)
      {
           //Valori del parametro t associati ai punti selezionati con il mouse sulla finestra grafica

            t = new float[curva.CP.size()];
            step_t = 1.0 / (curva.CP.size() - 1);
            for (i = 0; i < curva.CP.size(); i++)
                t[i] = (float)i * step_t;
          
            t[curva.CP.size()] = 1.0;
            //Calcola la curva di Hermite
            CostruisciHermite(&curva);
            //Aggiorna il VAO della curva
            UPDATE_VAO_Curva(&curva);

            glUniform1i(loc_flagP, 0);  //Se flagP=0, viene disegnata la curva valutata nei valori del parametro tg di graficazione
            glBindVertexArray(curva.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, curva.vertices.size());  //Modalità di rendering GL_LINE_STRIP: tutti i vertici vengono uniti da una spezzata
            glBindVertexArray(0);

            if (visualizzaTg == 1)
            {
                glUniform1i(loc_flagP, 2);
                glBindVertexArray(curva.VAO);
                glDrawArrays(GL_LINES, 0, curva.tg.size());  //cModalità di rendering GL_LINES: i vertici nel VAO a due a due vengono collegati con un segmento
            }
      }


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Renderizza i dati di disegno di ImGui

         
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    close_GUI();

    glDeleteProgram(programId);
    
     
    glDeleteBuffers(1, &curva.VBO_vertices);
    glDeleteBuffers(1, &curva.VBO_colors);
    glDeleteVertexArrays(1, &curva.VAO);
   

    glfwTerminate();


    return 0;
}

 


 
 