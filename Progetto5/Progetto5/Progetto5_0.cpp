#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId, programIdS;
float r = 0.0, g = 0.2, b = 1.0;
float alpha;
double mousex,mousey;
int height=1000, width=1000;
int numRows = 6, numCols=8;
float stepc, stepr;
Figura  triangolo = {  }, cerchio = { }, butterfly = { }, heart = { }, background = {}; //crea una nuova istanza della struttura Figura di nome  "triangolo", "cerchio ", "buterfly" wd "heart"
vec2 resolution;
 
int i,j;
mat4 Projection;
GLuint MatProj, MatModel, MatProjS, MatModelS, vec_res, loc_time;
float x, y;
float cx, cy;
float dx=0, dy=0;
float angolo = 0.0;
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
    
    //Costruisce la figura di backgroun 
    background.nTriangles = 2;
    background.progamId = programIdS;
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);
    cout << background.vertices[2].x << endl;

    //Costruisce i vertici del cerchio: attributo posizione e color
    heart.nTriangles = 30;
    heart.progamId = programId;
    INIT_HEART(0.0,0.0,0.09,0.09, &heart);
    //Genera il VAO della struttura  cerchio
    INIT_VAO(&heart);
    //Aggiunge al vector Scena la struttura di tipo Figura cerchio
    Scena.push_back(heart);

    //Costruisce i vertici di butterfly: attributo posizione e color
    butterfly.nTriangles = 300;
    butterfly.progamId = programId;
    INIT_BUTTERFLY(0.0,0.0, 0.1, 0.1, &butterfly);
    //Genera il VAO della struttura  butterfly
    INIT_VAO(&butterfly);
    //Aggiunge al vector Scena la struttura di tipo Figura butterfly
    Scena.push_back(butterfly);

    //Costruisce i vertici di heart: attributo posizione e color
    heart.nTriangles = 300;
    INIT_HEART(0.0, 0.1, 0.009, 0.009, &heart);
    //Genera il VAO della struttura  heart
    INIT_VAO(&heart);
    //Aggiunge al vector Scena la struttura di tipo Figura heart
    Scena.push_back(heart);
 

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
    vec_res = glGetUniformLocation(programIdS, "resolution");
    loc_time = glGetUniformLocation(programIdS, "currentTime");
 
    /* Loop until the user closes the window */

    float stepr = ((float)width) /(numCols);   //Passo sulle  riga
    float stepc = ((float)height) / (numRows); //Passo sulla colonna

    resolution= vec2(float(height), float(width));
    
    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        /* Render here */
        glClearColor(r,g,b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
         
        glUseProgram(Scena[0].progamId);

        Scena[0].Model = mat4(1.0);
        Scena[0].Model = scale(Scena[0].Model, vec3(float(width)*2.0, float(height)*2.0, 1.0));

        glUniformMatrix4fv(MatProjS, 1, GL_FALSE, value_ptr(Projection));
        glUniformMatrix4fv(MatModelS, 1, GL_FALSE, value_ptr(Scena[0].Model));
        glUniform2fv(vec_res, 1, value_ptr(resolution));
        glUniform1f(loc_time, currentTime);
       
        
        //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
        glBindVertexArray(Scena[0].VAO);
        //Fa il rendering della struttura i-esima
        glDrawArrays(Scena[0].render, 0, Scena[0].nv);
       
         

        
        for (i = 0; i < numRows; ++i) {  //Ciclando sulle righe cambio la y
            y = height - i * stepc - stepc / 2;
            
            for (j = 0; j <  numCols; ++j) {   //Ciclando sulle colonne cambio la x
              
                x = j * (stepr)+stepr/2;
                             
                 
                if (i % 2 ==0)
                {
                    glUseProgram(Scena[1].progamId);
                    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
                    Scena[1].Model = mat4(1.0);
                    Scena[1].Model = translate(Scena[1].Model, vec3(x, y, 0.0));
                    Scena[1].Model = scale(Scena[1].Model, vec3(30.0, 30.0, 1.0));

                     
                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[1].Model));
                    glBindVertexArray(Scena[1].VAO);
                    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .


                    glBindVertexArray(Scena[1].VAO);
                    //Fa il rendering della struttura i-esima
                    glDrawArrays(Scena[1].render, 0, Scena[1].nv);
                }
                else
                {
                    glUseProgram(Scena[2].progamId);
                    glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
                    angolo = angolo + 0.1;
                    Scena[2].Model = mat4(1.0);
                    Scena[2].Model = translate(Scena[2].Model, vec3(x, y, 0.0));
                    Scena[2].Model = scale(Scena[2].Model, vec3(150.0, 150.0, 1.0));
                                    
                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[2].Model));
                    glBindVertexArray(Scena[2].VAO);
                    //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
                    glDrawArrays(Scena[2].render, 0, Scena[2].nv);
                }
            }
         
          
        }  
       

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

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

 


 
 