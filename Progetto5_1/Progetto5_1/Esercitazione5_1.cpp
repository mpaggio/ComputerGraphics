#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"
#include "Utilities.h"
#define PI 3.14159265358979323
//Variabili globali -------------------------------------------------------------------
unsigned int programId, programIdS;
float r = 0.0, g = 0.2, b = 1.0;
float alpha;
double mousex,mousey;
int height=1000, width=1000;
int numRows = 6, numCols=8;
float stepc, stepr;
Figura spezzata = {}, triangolo = {  }, cerchio = { }, butterfly = { }, heart = { }, background = {}; //crea una nuova istanza della struttura Figura di nome  "triangolo", "cerchio ", "buterfly" wd "heart"
vec2 resolution;

Figura player;
Figura proiettile;
int i,j;
mat4 Projection;
GLuint MatProj, MatModel, MatProjS, MatModelS, vec_resS,loc_time;
float x, y;
float cx, cy;
float dx=0, dy=0;
float angolo = 0.0;
  

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
    

    player.nTriangles = 2;
    player.progamId = programId;
    player.position.x = width / 2.0;
    player.position.y = height / 10.0;
    INIT_PIANO(&player);
    INIT_VAO(&player);
 
    proiettile.nTriangles = 30;
    proiettile.progamId = programId;
    proiettile.position.x = 0.0;
    proiettile.position.y = 0.0;
    INIT_CIRCLE(proiettile.position.x, proiettile.position.y,1.0,1.0,&proiettile);
    INIT_VAO(&proiettile);

    background.nTriangles = 2;
    background.progamId = programIdS;
    INIT_PIANO(&background);
    INIT_VAO(&background);
    Scena.push_back(background);

     
    //Costruisce i vertici del cerchio: attributo posizione e color
    heart.nTriangles = 30;
    heart.progamId = programId;
    heart.position.x = 300;
    heart.position.y = 600;
    heart.isalive = true;
    INIT_HEART(0.0,0.0,0.09,0.09, &heart);
    //Genera il VAO della struttura  cerchio
    INIT_VAO(&heart);
     
    //Aggiunge al vector Scena la struttura di tipo Figura cerchio
    Scena.push_back(heart);

    //Costruisce i vertici di butterfly: attributo posizione e color
    butterfly.nTriangles = 30;
    butterfly.progamId = programId;
    butterfly.position.x = 300;
    butterfly.position.y = 800;
    butterfly.isalive = true;
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
    
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        /* Render here */
        glClearColor(r,g,b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
         
        glUseProgram(Scena[0].progamId);

        Scena[0].Model = mat4(1.0);
        Scena[0].Model = scale(Scena[0].Model, vec3(float(width)*2.0, float(height)*2.0, 1.0));

        glUniformMatrix4fv(MatProjS, 1, GL_FALSE, value_ptr(Projection));
        glUniformMatrix4fv(MatModelS, 1, GL_FALSE, value_ptr(Scena[0].Model));
        glUniform2fv(vec_resS, 1, value_ptr(resolution));
        glUniform1f(loc_time, currentFrame);
        
        //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
        glBindVertexArray(Scena[0].VAO);
        //Fa il rendering della struttura i-esima
        glDrawArrays(Scena[0].render, 0, Scena[0].nv);
        
      
        //Disegna il player
        
        glUseProgram(Scena[1].progamId);
        //position = vec2(height / 2.0, width / 2.0);
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        player.Model = mat4(1.0);
        player.Model = translate(player.Model, vec3( player.position.x,player.position.y, 0.0));
        player.Model = rotate(player.Model, radians(angolo), vec3(0.0f, 0.0f, 1.0f));
       
       

        
        //Disegna il proiettile
        //position = vec2(height / 2.0, width / 2.0);
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        //La matrice di modellazione del proiettile si ottiene aggiornando la matrice che posizione ed orienta il giocatore,
        //poichè deve eseguire lo stesso movimento del giocatore.


        aggiornaProiettile(&proiettile);

        proiettile.Model = translate(player.Model, vec3(proiettile.position.x, proiettile.position.y, 0.0));
        proiettile.Model = scale(proiettile.Model, vec3(20.0, 20.0, 1.0));
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(proiettile.Model));
        glBindVertexArray(proiettile.VAO);
        //Fa il rendering della struttura i-esima
        glDrawArrays(proiettile.render, 0, proiettile.nv - 4);
        glDrawArrays(GL_LINE_LOOP, proiettile.nv - 4, 4);
        

        //Adesso scalo il giocatore e lo renderizzo
        player.Model = scale(player.Model, vec3(80.0, 80.0, 1.0));
        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(player.Model));
        glBindVertexArray(player.VAO);
        glDrawArrays(player.render, 0, player.nv);
         

        
        //Disegno farfalla e cuore in posizioni statiche
        //
        // 
        Scena[1].updateTimer += 0.1f;
        if (int(Scena[1].updateTimer) >= 5.0f) {
            Scena[1].position = randomPosition(width, height);
            Scena[1].updateTimer = 0.0f;
        }
        glUseProgram(Scena[1].progamId);
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        Scena[1].Model = mat4(1.0);
        Scena[1].Model = translate(Scena[1].Model, vec3(Scena[1].position.x, Scena[1].position.y, 0.0));
        Scena[1].Model = scale(Scena[1].Model, vec3(30.0, 30.0, 1.0));
         

        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[1].Model));
        glBindVertexArray(Scena[1].VAO);
        //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
        //Fa il rendering della struttura i-esima
        glDrawArrays(Scena[1].render, 0, Scena[1].nv - 4);
        glDrawArrays(GL_LINE_LOOP, Scena[1].nv - 4, 4);
        
        
        Scena[2].updateTimer += 0.1f;
        if (int(Scena[2].updateTimer) >= 5.0f) {
            Scena[2].position = randomPosition(width, height);
            Scena[2].updateTimer = 0.0f;
        }
        glUseProgram(Scena[2].progamId);
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
        
        Scena[2].Model = mat4(1.0);
        Scena[2].Model = translate(Scena[2].Model, vec3(Scena[2].position.x, Scena[2].position.y,1.0));
        Scena[2].Model = scale(Scena[2].Model, vec3(150.0,150.0,1.0));
         

        glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[2].Model));
        glBindVertexArray(Scena[2].VAO);
        //Questa istruzione "lega" o "attiva" il Vertex Array Object (VAO) di ogni struttura di tipo Figura memorizzata nel vector Scena .
        glDrawArrays(Scena[2].render, 0, Scena[2].nv - 4);
        glDrawArrays(GL_LINE_LOOP, Scena[2].nv - 4, 4);

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

 


 
 