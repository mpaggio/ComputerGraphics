
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "ShaderMaker.h"
#include "UserInterfaceHandler.h"
 
using namespace std;
using namespace glm;

//Prototipi funzioni 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void INIT_SHADER(void);
void INIT_VAO(void);

//Variabili globali
static unsigned int programId;
unsigned int VAO;
unsigned int VBO;
bool isMouseDown = false;
float r = 0, g = 0, b = 0;

typedef struct {
    GLuint VAO;
    GLuint VBO_vertices;
    GLuint VBO_colors;
    int nTriangles;
    
    //Vertices geometry:
    vector<vec3> vertices;  // Array dinamicamente aggiornabile (ognuno dei suoi elementi è un vec3)
    vector<vec4> colors;
    int nVertices; // Number of vertices
    int render; // Type of render: GL_POINTS(senza collegamento), GL_LINES(collegati con una retta), GL_LINES_STRIP(collegati con linea spezzata), ...
} Figura;

Figura triangle = {};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())   //se glfwInit() dà valore falso, return -1
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failde to create the window !" << std::endl;

        glfwTerminate(); //LIbera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window); //creal il context corrente e lo associa a wundow. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failde to load opengl function pointers !" << std::endl;
        glfwTerminate();
        return -1;
    }

    triangle.vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    triangle.vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    triangle.vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    triangle.colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    triangle.colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    triangle.colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

    triangle.nVertices = 3;
    triangle.nTriangles = 1;
    triangle.render = GL_TRIANGLES;

    INIT_SHADER();
    INIT_VAO(&triangle);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        /* Render here */
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Fa partire il processo di rendering meiante i dati che sono salvati nel VAO

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(programId);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();


    return 0;
}

 

void INIT_SHADER(void)
{
    GLenum ErrorCheckValue = glGetError();

    char* vertexShader = (char*)"vertex_shader_c.glsl";
    char* fragmentShader = (char*)"fragment_shader_c.glsl";

    programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
    glUseProgram(programId);



}

void INIT_VAO(Figura* fig)
{
    //Genero un VAO
    glGenVertexArrays(1, &fig->VAO);
    //Ne faccio il bind (lo collego, lo attivo)
    glBindVertexArray(fig->VAO);

    //AL suo interno genero un VBO
    glGenBuffers(1, &fig->VBO_vertices);
    //Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_vertices);
    //Carico i dati vertices sulla GPU
    glBufferData(GL_ARRAY_BUFFER, fig->vertices.size()*sizeof(vec3), fig->vertices.data(), GL_STATIC_DRAW);

    // Configurazione dell'attributo posizione: informo il vertex shader su: dove trova le informazioni sulle posizioni e come le deve leggere
    //dal buffer caricato sulla GPU
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // Perchè abbiamo 7 informazioni per vertice (x,y,z,r,g,b,a)
    //Abilitazione degli attributi : glEnableVertexAttribArray abilita gli attributi per l'utilizzo nella pipeline grafica.
    glEnableVertexAttribArray(0);

    // Faccio lo stesso per il buffer dei colors
    glGenBuffers(1, &fig->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, fig->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, fig->colors.size() * sizeof(vec4), fig->colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isMouseDown = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isMouseDown = false;
    }

    std::cout << "isMouseDown " << isMouseDown << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "window size is " << width << "x" << height << std::endl;
    glViewport(0.0, 0.0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Cambia il colore dello sfondo
        r = 1.0;
        g = 1.0;
        b = 1.0;
    }
    else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else {
        // Cambia il colore dello sfondo
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }

}