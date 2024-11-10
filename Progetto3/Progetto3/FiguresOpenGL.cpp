#include "lib.h"
#include "ShaderMaker.h"
#include "strutture.h" 
#include "inizializzazioni.h"
#include "init_geometrie.h"
#include "gestione_interazioni.h"

#define PI 3.1415926535879323

// Ricordarsi di fare il comando "install-package glm"

//Variabili globali -------------------------------------------------------------------
unsigned int programId;
int i;
int width = 1000, heigth = 1000;
float r = 1.0, g = 0.6, b = 1.0;
float centroCerchioX = -0.2, centroCerchioY = -0.3, raggioX = 0.1, raggioY = 0.1;
float centroCuoreX = 0.0, centroCuoreY = 0.15, raggioCuoreX = 0.007, raggioCuoreY = 0.007;
float centroFarfallaX = 0.2, centroFarfallaY = -0.33, raggioFarfallaX = 0.04, raggioFarfallaY = 0.04;
double xPos, yPos;
extern bool areCentersToBeChanged;
vector<Figura> Scena;
Figura triangolo = {  }, cerchio = {  }, cuore = {  }, farfalla = {  };  //crea una nuova istanza della struttura Figura di nome  "triangolo".
//----------------------------------------------------------------------------------------

 

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
    window = glfwCreateWindow(width, heigth, "Hello World", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create the window !" << std::endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //crea il context corrente e lo associa a window. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

    /* Nasconde il cursore */
    // ******  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    

    //verifica se la libreria GLAD è riuscita a caricare correttamente tutti i puntatori 
    // alle funzioni OpenGL necessarie.

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    INIT_SHADER();
    //Costruisce i vertici del triangolo: attributo posizione e colore
    INIT_TRIANGLE(&triangolo);  // Viene passato l'indirizzo di memoria della struttura triangolo.
    //Genera il VAO della struttura  triangolo
    INIT_VAO(&triangolo);  // Viene passato l'indirizzo di memoria della struttura triangolo.
    Scena.push_back(triangolo);


    // Cerchio
    cerchio.nTriangles = 30;
    INIT_CIRCLE_WITH_SPIKES(centroCerchioX, centroCerchioY, 0.05, 10, &cerchio);
    INIT_VAO(&cerchio);
    Scena.push_back(cerchio);

    // Cuore
    cuore.nTriangles = 30;
    INIT_HEART(centroCuoreX, centroCuoreY, raggioCuoreX, raggioCuoreY, &cuore);
    INIT_DYNAMIC_VAO(&cuore);
    Scena.push_back(cuore);

    // Farfalla
    farfalla.nTriangles = 30;
    INIT_BUTTERFLY(centroFarfallaX, centroFarfallaY, raggioFarfallaX, raggioFarfallaY, &farfalla);
    INIT_DYNAMIC_VAO(&farfalla);
    Scena.push_back(farfalla);




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


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClearColor(r,g,b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Gestione della pulsazione nel tempo
        float currentTime = glfwGetTime();
        raggioX = sin(currentTime * 2.0 * PI) * 0.01 + 0.1;
        raggioY = sin(currentTime * 2.0 * PI) * 0.01 + 0.1;
        raggioCuoreX = sin(currentTime * 2.0 * PI) * 0.005 + 0.01;
        raggioCuoreY = sin(currentTime * 2.0 * PI) * 0.005 + 0.01;
        raggioFarfallaX = sin(currentTime * 2.0 * PI) * 0.01 + 0.03;
        raggioFarfallaY = sin(currentTime * 2.0 * PI) * 0.01 + 0.03;

        // Gestione della posizione del cursore per le coordinate del cerchio
        /*
            [height, 0] --> [-1, 1]  -->    heigth = -2
            [0, width]  --> [-1, 1]  -->    width  = +2
            x' = x * 2 / width - 1;
            y' = 1 - y * 2 / height; --> perchè height vale -2 
        */
        if (areCentersToBeChanged) {
            centroCerchioX = (xPos / width) * 2 - 1;
            centroCerchioY = 1 - (yPos / heigth) * 2;
        }

        cout << "/// ECCO IL CENTRO DEL CERCHIO --> " << centroCerchioX << ", " << centroCerchioY << endl;
        INIT_CIRCLE(centroCerchioX, centroCerchioY, raggioX, raggioY, &Scena[1]);
        INIT_HEART(centroCuoreX, centroCuoreY, raggioCuoreX, raggioCuoreY, &Scena[2]);
        INIT_BUTTERFLY(centroFarfallaX, centroFarfallaY, raggioFarfallaX, raggioFarfallaY, &Scena[3]);

        
        
        for (i = 0; i < Scena.size(); i++) {
            glBindBuffer(GL_ARRAY_BUFFER, Scena[i].VBO_vertices);
            glBufferSubData(GL_ARRAY_BUFFER, 0, Scena[i].vertices.size() * sizeof(vec3), Scena[i].vertices.data());
            glBindVertexArray(Scena[i].VAO);
            glDrawArrays(Scena[i].render, 0, Scena[i].nv);
        }

        for (i = 1; i < Scena.size(); i++) {
            Scena[i].vertices.clear();
            Scena[i].colors.clear();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);

    for (i = 0; i < Scena.size(); i++) {
        glDeleteBuffers(1, &Scena[i].VBO_vertices);
        glDeleteBuffers(1, &Scena[i].VBO_colors);
        glDeleteVertexArrays(1, &Scena[i].VAO);
    }

    glfwTerminate();


    return 0;
}

 


 
 