#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"

#define PI 3.14159265358979323

//Variabili globali -------------------------------------------------------------------

unsigned int programId, MatProj, MatModel;
float r = 0.0, g = 0.4, b = 1.0;
double mousex,mousey;
int height=1150, width=1200;
Figura  butterfly = { }, heart = { };  //crea una nuova istanza della struttura Figura di nome   "butterfly" ed "heart"
extern float alpha=0.8;  // Permette di modificare l'opacità dei colori
int i,j;
int numRows = 6, numCols = 8;
float x, y;
float cx, cy;
float dx=0, dy=0;
float angolo = 0.0;

mat4 Projection;
mat4 Model;

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
     glfwSetMouseButtonCallback(window, mouse_button_callback);

    


    //per visualizzare le dimensioni della finestra ridimensionata

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    INIT_SHADER();
    
    //Costruisce i vertici del cuore: attributo posizione e color
    heart.nTriangles = 100;
    INIT_HEART(0.0,0.0,0.01,0.01, &heart);
    //Genera il VAO della struttura  heart
    INIT_VAO(&heart);
    //Aggiunge al vector Scena la struttura di tipo Figura heart
    Scena.push_back(heart);

    //Costruisce i vertici di butterfly: attributo posizione e color
    butterfly.nTriangles = 150;
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

  

    //per visualizzare le dimensioni della finestra ridimensionata

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Gestione della trasparenza:
    /*
    In OpenGL, la funzione glBlend serve a definire come combinare i colori di un pixel sorgente (che stiamo disegnabdo) e di un pixel destinazione (già presente nel framebuffer)
     quando si disegnano oggetti trasparenti.
    In questo caso specifico, glBlend(GL_SRC_ALPHA, GL_ONES_MINUS_SRC_ALPHA); indica che :
     GL_SRC_ALPHA: Il valore alfa del pixel sorgente(quello che stiamo disegnando) verrà utilizzato come fattore di miscelazione per il colore sorgente.
     GL_ONES_MINUS_SRC_ALPHA : Il valore alfa del pixel destinazione(quello già presente nel buffer) verrà sottratto da 1 e poi utilizzato come fattore di miscelazione 
     per il colore destinazione. (già presente nel framebuffer
*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    MatProj = glGetUniformLocation(programId, "Projection");
    MatModel = glGetUniformLocation(programId, "Model");

    Projection = ortho(0.0f, float(width), 0.0f, float(height));

    float horizontalStep = ((float)width) / (numCols);
    float verticalStep = ((float)height) / (numRows);

    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        angolo++;
        glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));

        // Ciclare sulle righe modifica la y:
        for (i = 0; i < numRows; i++) {
            y = height - i * verticalStep - verticalStep / 3.0;
            for (j = 0; j < numCols; j++) {
                x = j * horizontalStep + horizontalStep / 2.0;
                if (i % 2 == 0) {
                    // Creiamo il modello del primo oggetto della scena
                    Scena[0].Model = mat4(1.0);
                    Scena[0].Model = translate(Scena[0].Model, vec3(x, y, 0.0)); // Matrice di traslazione che porta la figura al centro
                    Scena[0].Model = scale(Scena[0].Model, vec3(200.0, 200.0, 1.0));
                    Scena[0].Model = rotate(Scena[0].Model, radians(angolo), vec3(0.0, 0.0, 1.0));

                    // Trasferiamo a MatModel e a MatProjection i valori che abbiamo calcolato
                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[0].Model));

                    glBindVertexArray(Scena[0].VAO);
                    //Fa il rendering della struttura 0
                    glDrawArrays(Scena[0].render, 0, Scena[0].nv);
                }
                else {
                    // Creiamo il modello del secondo oggetto della scena
                    Scena[1].Model = mat4(1.0);
                    Scena[1].Model = translate(Scena[1].Model, vec3(x, y, 0.0)); // Matrice di traslazione che porta la figura al centro
                    Scena[1].Model = scale(Scena[1].Model, vec3(100.0, 100.0, 1.0));
                    Scena[1].Model = rotate(Scena[1].Model, radians(angolo), vec3(0.0, 0.0, 1.0));

                    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[1].Model));

                    glBindVertexArray(Scena[1].VAO);
                    //Fa il rendering della struttura 1
                    glDrawArrays(Scena[1].render, 0, Scena[1].nv);
                }
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);
    for (i = 0; i < Scena.size(); i++)
    {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }

    glfwTerminate();


    return 0;
}

 


 
 